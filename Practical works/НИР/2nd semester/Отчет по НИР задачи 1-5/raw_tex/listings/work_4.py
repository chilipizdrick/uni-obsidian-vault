import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, accuracy_score
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import GridSearchCV


data = pd.read_csv('./vgsales.csv')
data['Platform'] = np.where(data['Platform'] == 'DS', 0, 1)
data = data.dropna()

platform = data.loc[:, data.columns.isin(['Platform'])]
features = ['Rank', 'Year', 'NA_Sales', 'EU_Sales',
            'JP_Sales', 'Other_Sales', 'Global_Sales']
x = data.loc[:, data.columns.isin(features)]

x_tr, x_val, y_tr, y_val = train_test_split(x, platform,
                                            test_size=0.25, random_state=8)

best_tree = DecisionTreeClassifier(random_state=6679, max_depth=1)
best_tree = best_tree.fit(x_tr, y_tr)

for i in range(2,10):
    tree = DecisionTreeClassifier(random_state=6679, max_depth=i)
    tree = tree.fit(x_tr, y_tr)
    if tree.score(x_val, y_val) > best_tree.score(x_val, y_val):
        best_tree = tree


report = classification_report(y_val, best_tree.predict(x_val))
print(report)

accuracy = accuracy_score(y_val, best_tree.predict(x_val))
print(f'Accuracy: {accuracy}')

feature_importances = (best_tree.feature_importances_ /
                       sum(best_tree.feature_importances_))

results = pd.DataFrame({'Features': features,
                        'Importances': feature_importances})
results.sort_values(by='Importances', inplace=True)

ax = plt.barh(results['Features'], results['Importances'])
plt.xlabel('Feature importances')
plt.show()

from sklearn import tree


fig = plt.figure(figsize=(10,7))
_ = tree.plot_tree(best_tree,
                   feature_names=features,
                   impurity=False,
                   proportion=True,
                   max_depth=2,
                   fontsize=12,
                   filled=True)
plt.show()


forest = RandomForestClassifier(random_state=6679)
forest = forest.fit(x_tr, np.ravel(y_tr))


report = classification_report(y_val, forest.predict(x_val))
print(report)

accuracy = accuracy_score(y_val, forest.predict(x_val))
print(f'Accuracy: {accuracy}')

feature_importances = (forest.feature_importances_ /
                       sum(forest.feature_importances_))

results = pd.DataFrame({'Features': features,
                        'Importances': feature_importances})
results.sort_values(by='Importances', inplace=True)

ax = plt.barh(results['Features'], results['Importances'])
plt.xlabel('Feature importances')
plt.show()


param_grid = {
    'n_estimators': [50, 100, 200, 400],
    'max_depth': list(range(1, 10)),
    'criterion': ['gini']
}
tuned_forest = GridSearchCV(estimator=RandomForestClassifier(), 
                            param_grid=param_grid, cv=5, refit=True)
tuned_forest.fit(x_tr, np.ravel(y_tr))

print('Итерация 1')
 # n_estimators: значения варьируются от 50 до 400, выберем стандартные 100
print(f'n_estimators: {tuned_forest.best_estimator_.n_estimators}')
print(f'max_depth: {tuned_forest.best_estimator_.max_depth}') # max_depth: 9

# Теперь cдвинем диапазон max_depth

param_grid = {
    'n_estimators': [100],
    'max_depth': list(range(5, 15)),
    'criterion': ['gini']
}
tuned_forest = GridSearchCV(estimator=RandomForestClassifier(), 
                            param_grid=param_grid, cv=5, refit=True)
tuned_forest.fit(x_tr, np.ravel(y_tr))

print('Итерация 2')
print(f'max_depth: {tuned_forest.best_estimator_.max_depth}') # max_depth: 10

# Проанализируем полученный классификатор

report = classification_report(y_val,
                               tuned_forest.best_estimator_.predict(x_val))
print(report)

accuracy = accuracy_score(y_val, tuned_forest.best_estimator_.predict(x_val))
print(f'Accuracy: {accuracy}')

feature_importances = (tuned_forest.best_estimator_.feature_importances_ /
                       sum(tuned_forest.best_estimator_.feature_importances_))

results = pd.DataFrame({'Features': features,
                        'Importances': feature_importances})
results.sort_values(by='Importances', inplace=True)

ax = plt.barh(results['Features'], results['Importances'])
plt.xlabel('Feature importances')
plt.show()