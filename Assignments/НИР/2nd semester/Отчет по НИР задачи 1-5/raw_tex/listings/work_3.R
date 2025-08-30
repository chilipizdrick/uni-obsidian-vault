library("purrr")
library("lmtest")
library("dplyr")
library("car")
library("haven")
library("naniar")

# --- Чистка датасета от мусора ---

data <- read_sav("./r20i_os26c.sav")
View(data)
data1 <-
  select(data,
         pj13.2,
         ph5,
         p_marst,
         p_diplom,
         p_age,
         status,
         pj6.2,
         pj1.1.3,
         pj29,
         pj6,
         pj21b)

# Избавимся от зарезервированных значений по типу ЗАТРУДНЯЮСЬ ОТВЕТИТЬ
data1 = data1 %>% replace_with_na_all(condition = ~.x > 99999990)
# Проигнорируем значения NA
data1 = na.omit(data1)

write_sav(data1, "./r20i_os26c(stripped_of_NA).sav")

# --- One-hot-encoding и нормализация ---

data1 = read_sav("./r20i_os26c(stripped_of_NA).sav")

# Обработаем и нормализуем столбцы

clean_data = select(data1)

sex = as.numeric(map(data1$ph5, function(x) if(x == 1) 1 else 0))
clean_data["sex"] = sex
wed1 = as.numeric(map(data1$p_marst, function(x) if(x == 2 || x == 6) 1 else 0))
clean_data["wed1"] = wed1
wed2 = as.numeric(map(data1$p_marst, function(x) if(x == 4 || x == 5) 1 else 0))
clean_data["wed2"] = wed2
wed3 = as.numeric(map(data1$p_marst, function(x) if(x == 1 || x == 3) 1 else 0))
clean_data["wed3"] = wed3
city_status = as.numeric(map(data1$status, function(x) if(x == 1 || x == 2) 1 else 0))
clean_data["city_status"] = city_status
higher_educ = as.numeric(map(data1$p_diplom, function(x) if(x >= 6) 1 else 0))
clean_data["higher_educ"] = higher_educ
salary_satisfaction = as.numeric(map(data1$pj1.1.3, function(x) if(x < 3) 1 else 0))
clean_data["salary_satisfaction"] = salary_satisfaction
is_entrepreneur = as.numeric(map(data1$pj29, function(x) if(x == 1) 1 else 0))
clean_data["is_entrepreneur"] = is_entrepreneur
if_subordinates = as.numeric(map(data1$pj6, function(x) if(x == 1) 1 else 0))
clean_data["if_subordinates"] = if_subordinates

sal = as.numeric(data1$pj13.2)
sal = (sal - mean(sal)) / sd(sal)
clean_data["salary"] = sal
age = as.numeric(data1$p_age)
age = (age - mean(age)) / sd(age)
clean_data["age"] = age
week_duration = as.numeric(data1$pj6.2)
week_duration = (week_duration - mean(week_duration)) / sd(week_duration)
clean_data["week_duration"] = week_duration
last_vacation = as.numeric(data1$pj21b)
last_vacation = (last_vacation - mean(last_vacation)) / sd(last_vacation)
clean_data["last_vacation"] = last_vacation

write_sav(clean_data, "./r20i_os26c(clean).sav")

# --- Построение модели ---

clean_data = read_sav("./r20i_os26c(clean).sav")

# Денормализуем week_duration, age и last_vacation для логарифмирования

min_age = min(clean_data$age)
clean_data["age"] = as.numeric(map(clean_data$age, function(x)
  x - min_age + 1e-8))
min_week_duration = min(clean_data$week_duration)
clean_data["week_duration"] = as.numeric(map(clean_data$week_duration, function(x)
  x - min_week_duration + 1e-8))
min_last_vacation = min(clean_data$last_vacation)
clean_data["last_vacation"] = as.numeric(map(clean_data$last_vacation, function(x)
  x - min_last_vacation + 1e-8))

# Регрессор wed3 напрямую линейно зависим с регрессорами wed1, wed2; исключим его из модели
model1 = lm(
  salary ~ sex + wed1 + wed2 + wed3 + city_status + higher_educ + salary_satisfaction +
    is_entrepreneur + if_subordinates + age + week_duration + last_vacation,
  data = clean_data
)
summary(model1)

# Регрессоры wed2, last_vacation - не значимы; исключим их из модели
model2 = lm(
  salary ~ sex + wed1 + wed2 + city_status + higher_educ + salary_satisfaction +
    is_entrepreneur + if_subordinates + age + week_duration + last_vacation,
  data = clean_data
)
summary(model2)
vif(model2)

model2_1 = lm(
  salary ~ sex + wed1 + city_status + higher_educ + salary_satisfaction +
    is_entrepreneur + if_subordinates + age + week_duration,
  data = clean_data
)
summary(model2_1)
vif(model2_1)

# Напишем функции для нахождения оптимального основания логарифма и степенной функции

best_log_base <- function(var, regressor) {
  best_base <- 0.1
  best_r_squared <- 0.0
  
  for (base in seq(from=0.1, to=5.0, by=0.1)) {
    if (base != 1.0) {
      predictor <- log(regressor, base)
      model = lm(var ~ predictor)
      r_squared <- summary(model)$r.squared
      if (r_squared > best_r_squared) {
        best_r_squared <- r_squared
        best_base <- base
      }
    }
  }
  print("R^2: ")
  print(best_r_squared)
  best_base
}

best_exp_base <- function(var, regressor) {
  best_base <- 0.1
  best_r_squared <- 0.0
  
  for (base in seq(from=0.1, to=3.0, by=0.1)) {
    predictor <- base^regressor
    model = lm(var ~ predictor)
    r_squared <- summary(model)$r.squared
    if (r_squared > best_r_squared) {
      best_r_squared <- r_squared
      best_base <- base
    }
  }
  print("R^2: ")
  print(best_r_squared)
  best_base
}

# Найдем с их помощью лучшие основания для логарифма и степенной функции для регрессоров age и week duration
# log_base for age
best_log_base(clean_data$salary, clean_data$age)
# log_base for week_duration
best_log_base(clean_data$salary, clean_data$week_duration)
# exp_base for age
best_exp_base(clean_data$salary, clean_data$age)
# exp_base for week_duration
best_exp_base(clean_data$salary, clean_data$week_duration)

# Видим, что лучшие показатели по R^2 дадут регресоры - I(2.3^age), I(0.7^week_duration)

# Использовав полученные регрессоры в модели, увидим, что R^2(adj) - увеличился (R^2(adj) = 0.2798)
model3 = lm(
  salary ~ sex + wed1 + city_status + higher_educ + salary_satisfaction +
    is_entrepreneur + if_subordinates + I(2.3 ^ age) + I(0.7 ^ week_duration),
  data = clean_data
)
summary(model3)

# Рассмотрим произведения и квадраты регрессоров
# R^2(adj) = 0.2718
summary(
  lm(
    salary ~ sex + wed1 + city_status + higher_educ + salary_satisfaction +
      is_entrepreneur + if_subordinates + I(2.3 ^ age * 0.7 ^ week_duration),
    data = clean_data
  )
)
# R^2(adj) = 0.2734
summary(
  lm(
    salary ~ sex + wed1 + city_status + higher_educ + salary_satisfaction +
      is_entrepreneur + if_subordinates + I((2.3 ^ age) ^ 2) + I(0.7 ^ week_duration),
    data = clean_data
  )
)
# R^2(adj) = 0.277
summary(
  lm(
    salary ~ sex + wed1 + city_status + higher_educ + salary_satisfaction +
      is_entrepreneur + if_subordinates + I(2.3 ^ age) + I((0.7 ^ week_duration)^2),
    data = clean_data
  )
)

# Лучшей моделью оказалась изначальная модель; регрессор wed1 в ней окончательно потерял значимость, поэтому исключим его
summary(model3)

# У итоговой модели R^2(adj) = 0.2797
model4 = lm(
  salary ~ sex + city_status + higher_educ + salary_satisfaction + is_entrepreneur +
    if_subordinates + I(2.3 ^ age) + I(0.7 ^ week_duration),
  data = clean_data
)
summary(model4)

# Лучшая построенная модель - model3

# Нахождение доверительного интервала
interval <- function(model){
  df <- df.residual(model)
  t_crit <- qt(0.975, df)
  out = summary(model)
  std_err <- out$coefficients[2, 2]
  koef <- out$coefficients[2, 1]
  c(koef - std_err*t_crit, koef + std_err*t_crit)
}

# Построим парные регрессии для полученной модели и найдем доверительные интервалы соотв. коэффициентов:

# salary~sex: Связь - положительная (0 не попал в интервал => взаимосвязь присутствует)
# Model
# summary(lm(salary~sex, data=clean_data))
# Interval
interval(lm(salary~sex, data=clean_data))

# salary~city_status: Связь - положительная (0 не попал в интервал => взаимосвязь присутствует)
# Model
# summary(lm(salary~city_status, data=clean_data))
# Interval
interval(lm(salary~city_status, data=clean_data))

# salary~higher_educ: Связь - положительная (0 не попал в интервал => взаимосвязь присутствует)
# Model
# summary(lm(salary~higher_educ, data=clean_data))
# Interval
interval(lm(salary~higher_educ, data=clean_data))

# salary~salary_satisfaction: Связь - положительная (0 не попал в интервал => взаимосвязь присутствует)
# Model
# summary(lm(salary~salary_satisfaction, data=clean_data))
# Interval
interval(lm(salary~salary_satisfaction, data=clean_data))

# salary~is_entrepreneur: Связь - положительная (0 не попал в интервал => взаимосвязь присутствует)
# Model
# summary(lm(salary~is_entrepreneur, data=clean_data))
# Interval
interval(lm(salary~is_entrepreneur, data=clean_data))

# salary~if_subordinates: Связь - положительная (0 не попал в интервал => взаимосвязь присутствует)
# Model
# summary(lm(salary~if_subordinates, data=clean_data))
# Interval
interval(lm(salary~if_subordinates, data=clean_data))

# salary~age: Связь - отрицательная (0 не попал в интервал => взаимосвязь присутствует)
# Model
# summary(lm(salary~age, data=clean_data))
# Interval
interval(lm(salary~age, data=clean_data))

# salary~week_duration: Связь - положительная (0 не попал в интервал => взаимосвязь присутствует)
# Model
# summary(lm(salary~week_duration, data=clean_data))
# Interval
interval(lm(salary~week_duration, data=clean_data))

# --- Вывод ---
# Таким образом, наибольшую зарплату получают молодые мужчины, проживающие в городе, с высшим образованием,
# удовлетворенные своей зарплатой, предприниматели, имеющие подчиненных, а также имеющие длинную рабочую неделю 

# Проверим наилучшую построенную модель на подмножестве не женатых мужчин с высшим образованием (1)

subset1 = subset(clean_data, sex == 1)
subset1 = subset(subset1, wed1 == 0)
subset1 = subset(subset1, higher_educ == 1)
# View(subset1)

# Полученная модель дает неточные прогнозы на подмножестве (1) (R^2(adj) = 0.07123)
summary(
  lm(
    salary ~ city_status + salary_satisfaction + is_entrepreneur + if_subordinates +
      I(2.3 ^ age) + I(0.7 ^ week_duration),
    data = subset1
  )
)

# Проверим наилучшую построенную модель на подмножестве городских жителей, состоящих в браке (2)

subset2 = subset(clean_data, city_status == 1)
subset2 = subset(subset2, wed1 == 1)
# View(subset2)

# Полученная модель дает достаточно точные (в контексте данной задачи) прогнозы на подмножестве (2) (R^2(adj) = 0.2708)
summary(
  lm(
    salary ~ sex + higher_educ + salary_satisfaction + is_entrepreneur + if_subordinates +
      I(2.3 ^ age) + I(0.7 ^ week_duration),
    data = subset2
  )
)

# Проверим оставшиеся в модели коэффициенты
interval(lm(salary~age, data=clean_data))
interval(lm(salary~week_duration, data=clean_data))
# Ни в один из доверительных интервалов не попал 0 => взаимосвязь между
# регрессорами и объясняемой переменной - присутствует
