import pandas as pd
from scipy import stats
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
import numpy as np
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt
from sklearn.manifold import TSNE
from sklearn.utils import shuffle
import seaborn as sns


data = pd.read_csv('./crime.csv', encoding='unicode_escape')
features = ['offense_code', 'offense_code_extension', 'first_occurrence_date',
            'last_occurrence_date', 'reported_date', 'incident_address',
            'geo_x', 'geo_y', 'geo_lon', 'geo_lat', 'district_id',
            'precinct_id', 'neighborhood_id', 'is_crime', 'is_traffic',
            'victim_count']
data = data.loc[:, data.columns.isin(features)]
criterial_features = ['offense_code', 'offense_code_extension',
                     'incident_address', 'district_id', 'precinct_id',
                     'neighborhood_id']
criterial_data = data.loc[:, data.columns.isin(criterial_features)]
print(f'Number of rows: {len(data)}')
criterial_data.nunique().sort_values(ascending=False)

print(f'Total number of objects: {len(data)}')
print(f'Number of objects with NA values: {len(data) - len(data.dropna())}')
print(f'Number of \'clean\' objects: {len(data.dropna())}')

print('Number of NA values per column:')
for col in sorted(data.columns, 
                  key=lambda x: data[x].isna().sum(), 
                  reverse=True):
    print(f'{col}: {data[col].isna().sum()}')

numerical_features = ['first_occurrence_date', 'last_occurrence_date',
                      'reported_date', 'geo_x', 'geo_y', 'geo_lat', 'geo_lon',
                      'victim_count', 'reported_time', 'reported_time_utc']
numerical_data = pd.DataFrame(index=data.index, columns=numerical_features)
numerical_data.loc[:, numerical_features] = data.loc[:,
    data.columns.isin(numerical_features)]

time_features = ['first_occurrence_date',
                 'last_occurrence_date', 'reported_date']

for col in time_features:
    numerical_data.loc[:, col] = numerical_data[col].apply(
        lambda timestr: pd.to_datetime(timestr, format='%m/%d/%Y %I:%M:%S %p'))

numerical_data['reported_time'] = \
    numerical_data['reported_date'].apply(lambda x: pd.to_datetime(
        x.strftime('%H:%M:%S')))

numerical_data.loc[:, 'reported_time_utc'] = \
    numerical_data['reported_time'].dt.hour * 60 * 60 + \
    numerical_data['reported_time'].dt.minute * 60 + \
    numerical_data['reported_time'].dt.second
numerical_data = numerical_data.astype('float64', errors='ignore')

# Отбросим значения даты и времени в формате Timestamp для нормализации
normalizible_features = ['geo_x', 'geo_y', 'geo_lat',
                         'geo_lon', 'victim_count', 'reported_time_utc']
normalizible_data = numerical_data.loc[:, numerical_data.columns.isin(
    normalizible_features)]

outliers = []
for col in normalizible_features:
    z_scores = stats.zscore(normalizible_data[col])
    outliers.extend([i for i, z in enumerate(z_scores) if abs(z) > 3])
print(f"Number of outliers: {len(outliers)}")
print(f'Number of \'clean\' objects: {len(data)}')

std_scaler = preprocessing.StandardScaler()
normalized_numerical_data = pd.DataFrame(
    std_scaler.fit_transform(normalizible_data.dropna()),
    columns=normalizible_data.dropna().columns,
    index=normalizible_data.dropna().index)
print("Mean values:")
for col in normalizible_features:
    print(f'{col}: {normalized_numerical_data[col].mean()}')
normalized_numerical_data.head()

binary_features = ['is_crime', 'is_traffic']
features = criterial_features + numerical_features + binary_features
x_features = features.copy()
x_features.remove('offense_code')
x_features.remove('offense_code_extension')
target = data['offense_code']
x = data.loc[:, data.columns.isin(x_features)]

x_tr, x_val, target_tr, target_val = train_test_split(
    x, target, test_size=0.3, random_state=42)
print(f'Training split size: {len(x_tr)}')
print(f'Validation split size: {len(x_val)}')

for col in normalizible_features:
    print(normalized_numerical_data.loc[:].corr()[col][:], "\n")

clean_features = ['offence_code+extension', 'reported_time_utc',
                  'geo_x', 'geo_y', 'district_id', 'is_crime',
                  'is_traffic', 'victim_count']
clean_data = pd.DataFrame(columns=clean_features, index=data.index)

clean_data['offence_code+extension'] = data['offense_code'] * \
    10 + data['offense_code_extension']
clean_data['reported_time_utc'] = numerical_data['reported_time_utc']
clean_data['geo_x'] = numerical_data['geo_x']
clean_data['geo_y'] = numerical_data['geo_y']
clean_data['district_id'] = data['district_id']
clean_data['is_crime'] = data['is_crime']
clean_data['is_traffic'] = data['is_traffic']
clean_data['victim_count'] = data['victim_count']
clean_data = clean_data.dropna()
# print(f'Number of objects in cleaned dataset: {len(clean_data.index)}')

normalizible_clean_features = ['reported_time_utc', 'geo_x', 'geo_y',
                               'victim_count']
normalizible_clean_data = clean_data.loc[:, clean_data.columns.isin(
    normalizible_clean_features)]
std_scaler = preprocessing.StandardScaler()
normalized_clean_data = pd.DataFrame(
    std_scaler.fit_transform(normalizible_clean_data),
    columns=normalizible_clean_data.columns,
    index=normalizible_clean_data.index)

for col in normalizible_clean_features:
    clean_data[col] = normalized_clean_data.loc[:, col]
clean_data = clean_data.apply(
    lambda x: pd.to_numeric(x, errors='coerce')).dropna()

clean_data.to_csv('./clean_crime.csv')

pca_data = clean_data.drop(columns=['offence_code+extension'])

pca = PCA()
x_pca = pca.fit(pca_data.values)
explained_variance_ratio = pca.explained_variance_ratio_
cumulative_variance = np.cumsum(explained_variance_ratio)
n_components = np.argmax(cumulative_variance >= 0.9) + 1

plt.barh(pca.get_feature_names_out(), explained_variance_ratio)
plt.xlabel('Feature importances')
plt.show()

plt.bar(range(1, len(cumulative_variance) + 1), cumulative_variance)
# plt.plot(range(1, len(cumulative_variance) + 1), cumulative_variance)
plt.xlabel('Cummulative variance by number of features')
plt.show()

print(f'{n_components} features are sufficient to explain 90% of the variance.')

loadings = pca.components_[0]
feature_importances = pd.Series(
    loadings, index=pca_data.columns)
print('Feature contributions to the first component (pca0):')
print(feature_importances.abs().sort_values(ascending=False))

shuffled_data = shuffle(clean_data, random_state=0).head(20000)

x = shuffled_data.drop(columns=['offence_code+extension',])
y = shuffled_data.loc[:, clean_data.columns.isin(['offence_code+extension'])]

z = TSNE(n_components=2, learning_rate='auto', random_state=0,
         init='pca', perplexity=50).fit_transform(x)

x_features = clean_features.copy()
x_features.remove('offence_code+extension')

df = pd.DataFrame()
df['y'] = y
df['Component 1'] = z[:, 0]
df['Component 2'] = z[:, 1]

sns.scatterplot(x='Component 1', y='Component 2',
                hue=shuffled_data['district_id'],
                data=df).set(title='t-SNE Visualization (district_id)')
plt.show()
sns.scatterplot(x='Component 1', y='Component 2',
                hue=shuffled_data['victim_count'],
                data=df).set(title='t-SNE Visualization (victim_count)')
plt.show()
sns.scatterplot(x='Component 1', y='Component 2',
                hue=shuffled_data['offence_code+extension'],
                data=df).set(
                    title='t-SNE Visualization (offence_code+extension)')
plt.show()

clean_data.sort_values(by=['victim_count'],
                       ascending=False).loc[:,
                        clean_data.columns.isin(['offence_code+extension',
                                                 'victim_count'])].head(10)