# ВАРИАНТ 4

# ЧАСТЬ 2.1

# swiss : Education ~ Fertility + Agriculture + Infant.Mortality

library("lmtest")
library("GGally")
library("car")

data = swiss

# Прослеживается низкая зависимость (R^2 = 0.12), оставим регрессор
summary(lm(Fertility~Agriculture, data))
# Прослеживается низкая зависимость (R^2 = 0.17), оставим регрессор
summary(lm(Fertility~Infant.Mortality, data))
# Прослеживается очень низкая зависимость (R^2 = 0.003), оставим регрессор
summary(lm(Agriculture~Infant.Mortality, data))

# Все проверенные регрессоры не имеют взаимной значимой линейной зависимости

# Полученная сырая модель имеет R^2 = 0.63, что говорит о том, что зависимость 
# определенно прослеживается, но она не очень сильна. В то же время регрессоры
# Fertility и Agriculture имеют оценку в "***", что говорит о сильной статистической 
# связанности этих регрессоров и объясняемой переменной. Регрессор Infant.Mortality
# же имеет ноль "*", => им можно пренебречь.
summary(lm(Education ~ Fertility + Agriculture + Infant.Mortality, data))

lm(Education ~ Fertility + Agriculture, data) # R^2 = 0.6281
lm(Education ~ log(Fertility) + Agriculture, data) # R^2 = 0.6875
lm(Education ~ Fertility + log(Agriculture), data) # R^2 = 0.6994
lm(Education ~ log(Fertility) + log(Agriculture), data) # R^2 = 0.7301

# Введем логарифмы регрессоров

# Модель лучше изначальной: R^2 = 0,7
summary(lm(Education ~ log(Fertility) + Agriculture + Infant.Mortality, data))
# Модель еще лучше изначальной: R^2 = 0,756
summary(lm(Education ~ log(Fertility) + log(Agriculture) + Infant.Mortality, data))
# Модель стала чуть хуже: R^2 = 0,755
summary(lm(Education ~ log(Fertility) + log(Agriculture) + log(Infant.Mortality), data))

# Наилучшей вышла вторая модель (R^2 = 0.746)
summary(lm(Education ~ log(Fertility) + log(Agriculture) + Infant.Mortality, data))
# При этом Infant.Mortality очень малозначим по p-метрике, 
# поэтому выкинем его, потеряв 1% в R^2 (R^2 = 0.73)
summary(lm(Education ~ log(Fertility) + log(Agriculture), data))

summary(lm(Education ~ log(Fertility) + log(Agriculture), data)) # R^2 = 0.7301
summary(lm(Education ~ I(log(Fertility)*log(Agriculture)), data)) # R^2 = 0.6405
summary(lm(Education ~ I(log(Fertility)^2) + log(Agriculture), data)) # R^2 = 0.7227
summary(lm(Education ~ log(Fertility) + I(log(Agriculture)^2), data)) # R^2 = 0.7098
summary(lm(Education ~ I(log(Fertility)^2) + I(log(Agriculture)^2), data)) # R^2 = 0.6983

# Введем произведения и квараты регрессоров

# Модель хуже изналальной R^2 = 0.723
summary(lm(Education ~ I(log(Fertility)^2) + log(Agriculture), data))
# Модель хуже изналальной R^2 = 0.71
summary(lm(Education ~ log(Fertility) + I(log(Agriculture)^2), data))
# Модель хуже изналальной R^2 = 0.641
summary(lm(Education ~ I(log(Fertility)*log(Agriculture)), data))

# Наилучшей вышла модель без квадратов и произведений регрессоров (R^2 = 0.73)
summary(lm(Education ~ log(Fertility) + log(Agriculture), data))

best_model = lm(Education ~ log(Fertility) + log(Agriculture), data)

# Рассмотрим индивидуальные лин. регрессии, построенные на основе каждого из регрессоров

# Регрессор log(Fertility) - значим; взаимосвязь между объясняемой и объясняющей переменной - отрицательная (k = -35)
summary(lm(Education ~ log(Fertility), data))
# Регрессор log(Agriculture) - значим; взаимосвязь между объясняемой и объясняющей переменной - отрицательная (k = -9.4)
summary(lm(Education ~ log(Agriculture), data))

# ЧАСТЬ 2.2

# Std. err:
#   log(Fertility) : 4.479
#   log(Agriculture) : 1.146
summary(best_model)

# t_criterion = 2.015 (p = 95%, 42 степени свободы)
t_crit = qt(0.975, df=44)
t_crit

# Доверительные интервалы для соотв. регрессоров:

# log(Fertility)
  c(-22.874 - t_crit*4.479, -22.874 + t_crit*4.479)
# log(Agriculture)
c(-6.461 - t_crit*1.146, -6.461 + t_crit*1.146)

# Ни в один из интервалов не попадает "0" => гипотеза о равенстве
# коэффициента нулю опровергнута

# Доверительный интервал для одного прогноза:
# Fertility = 80, Agriculture = 25
best_model = lm(Education ~ log(Fertility) + log(Agriculture), data)
new.data = data.frame(Fertility = 80, Agriculture = 25)
predict(best_model, new.data, interval="confidence")

# Построим модели для индивидуальных регрессоров лучшей модели

# Education~log(Fertility)
summary(lm(Education~log(Fertility), data))
# t_criterion = 2.014 (p = 95%, 45 степеней свободы)
t_crit2 = qt(0.975, df=45)
t_crit2

# Полученный дов. интервал - полностью отрицательный => выявленная связь между 
# объясняемой переменной и регрессором - отрицательная
c(-35.87 - t_crit2*4.984, -35.87 + t_crit2*4.984)


# Education~log(Agriculture)
summary(lm(Education~log(Agriculture), data))
# t_criterion = 2.014 (p = 95%, 45 степеней свободы)
t_crit2 = qt(0.975, df=45)
t_crit2

# Полученный дов. интервал - полностью отрицательный => выявленная связь между 
# объясняемой переменной и регрессором - отрицательная
c(-9.472 - t_crit2*1.226, -9.472 + t_crit2*1.226)


# Тепрерь мультиколлинеарность отсутствует
vif(best_model)
