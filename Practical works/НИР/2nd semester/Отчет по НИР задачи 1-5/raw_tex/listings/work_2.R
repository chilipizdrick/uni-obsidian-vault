library("lmtest")
library("GGally")
library("car")

data = swiss

# Все проверенные регрессоры не имеют значимой взаимной линейной зависимости
summary(lm(Fertility~Agriculture, data)) # R^2 = 0.12
summary(lm(Fertility~Infant.Mortality, data)) # R^2 = 0.17
summary(lm(Agriculture~Infant.Mortality, data)) # R^2 = 0.003

# R^2 = 0.63, исключим регрессор Infant.Mortality в силу высокого k-коэф.
summary(lm(Education ~ Fertility + Agriculture + Infant.Mortality, data))

# Введем логарифмы регрессоров:
lm(Education ~ Fertility + Agriculture, data) # R^2 = 0.6281
lm(Education ~ log(Fertility) + Agriculture, data) # R^2 = 0.6875
lm(Education ~ Fertility + log(Agriculture), data) # R^2 = 0.6994
lm(Education ~ log(Fertility) + log(Agriculture), data) # R^2 = 0.7301

# Наилучшей вышла модель:
summary(lm(Education ~ log(Fertility) + log(Agriculture), data)) # R^2 = 0.7301

# Введем квадраты и произведения регрессоров:
summary(lm(Education ~ log(Fertility) + log(Agriculture), data)) # R^2 = 0.7301
summary(lm(Education ~ I(log(Fertility)*log(Agriculture)), data)) # R^2 = 0.6405
summary(lm(Education ~ I(log(Fertility)^2) + log(Agriculture), data)) # R^2 = 0.7227
summary(lm(Education ~ log(Fertility) + I(log(Agriculture)^2), data)) # R^2 = 0.7098
summary(lm(Education ~ I(log(Fertility)^2) + I(log(Agriculture)^2), data)) # R^2 = 0.6983

# Наилучшей вышла изначальная модель с логарифмами:
summary(lm(Education ~ log(Fertility) + log(Agriculture), data)) # R^2 = 0.7301
best_model = lm(Education ~ log(Fertility) + log(Agriculture), data)

# Рассмотрим индивидуальные лин. регрессии, построенные на основе каждого из регрессоров:
# Регрессор log(Fertility) - значим; взаимосвязь между объясняемой и объясняющей переменной - отрицательная (k = -35)
summary(lm(Education ~ log(Fertility), data))
# Регрессор log(Agriculture) - значим; взаимосвязь между объясняемой и объясняющей переменной - отрицательная (k = -9.4)
summary(lm(Education ~ log(Agriculture), data))

# Построим доверительные интервалы для коэффициетов регрессоров полученной модели:
# Std. err:
#   log(Fertility) : 4.479
#   log(Agriculture) : 1.146
summary(best_model)
t_crit = qt(0.975, df=44) # t_crit = 2.015 (p = 95%, 42 степени свободы)
# Ни в один из интервалов не попадает "0" => гипотеза о равенстве
# коэффициента нулю опровергнута
# log(Fertility)
c(-22.874 - t_crit*4.479, -22.874 + t_crit*4.479) # (-31.90083; -13.84717)
# log(Agriculture)
c(-6.461 - t_crit*1.146, -6.461 + t_crit*1.146) # (-8.770611; -4.151389)

# Доверительный интервал для одного прогноза: Fertility = 80, Agriculture = 25
best_model = lm(Education ~ log(Fertility) + log(Agriculture), data)
new.data = data.frame(Fertility = 80, Agriculture = 25)
predict(best_model, new.data, interval="confidence")
#      fit      lwr      upr
# 10.97556 8.287011 13.66411

# Построим модели для индивидуальных регрессоров лучшей модели
# Education ~ log(Fertility)
summary(lm(Education~log(Fertility), data))
t_crit2 = qt(0.975, df=45)# t_crit2 = 2.014 (p = 95%, 45 степеней свободы)
# Полученный дов. интервал - полностью отрицательный => выявленная связь между 
# объясняемой переменной и регрессором - отрицательная
c(-35.87 - t_crit2*4.984, -35.87 + t_crit2*4.984) # (-45.90829; -25.83171)

# Education ~ log(Agriculture)
summary(lm(Education~log(Agriculture), data))
t_crit2 = qt(0.975, df=45) # t_crit2 = 2.014 (p = 95%, 45 степеней свободы)
# Полученный дов. интервал - полностью отрицательный => выявленная связь между 
# объясняемой переменной и регрессором - отрицательная
c(-9.472 - t_crit2*1.226, -9.472 + t_crit2*1.226) # (-11.941291; -7.002709)
