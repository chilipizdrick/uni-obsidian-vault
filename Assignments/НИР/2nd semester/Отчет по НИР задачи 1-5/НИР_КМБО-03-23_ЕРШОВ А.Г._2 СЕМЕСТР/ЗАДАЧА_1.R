# ВАРИАНТ 4

library("lmtest")

mean(swiss$Agriculture) # Ср. арифм. Agriculture = 50.65957
var(swiss$Agriculture) # Дисперсия Agriculture = 515.7994
sd(swiss$Agriculture) # СКО Agriculture = 22.71122

mean(swiss$Education) # Ср. арифм. Education = 10.97872
var(swiss$Education) # Дисперсия Education = 92.45606
sd(swiss$Education) # СКО Education = 9.615407

mean(swiss$Examination) # Ср. арифм. Examination = 16.48936
var(swiss$Examination) # Дисперсия Examination = 63.64662
sd(swiss$Examination) # СКО Examination = 7.977883

# --- Построение линейной регресси Agriculture~Examination ---
# Как видно из построенной модели, p-value < 0.05 => есть сильная 
# причинно-следственная связь между регрессором и объясняемой переменной;
# константное значение (Intercept) и регрессор Education были оценены в "***",
# что значит, что они сильно статистически связаны. К тому же коэфф. k
# зависимости Agriculture от Education отрицательный (k = -1.5105), откуда следует,
# что Agriculture и Education находятся в сильной обратной зависимости.
# Коэффициент детерминации R-squared оказался равным 0.409, что значит, что модель
# неплоха для парной регрессии, но плоха в общем случае, ее нужно значительно 
# улучшать, добавляя в модель дополнительные регрессоры.
model1 = lm(formula=Agriculture~Education, data=swiss)
summary(model1)

# --- Построение линейной регресси Agriculture~Examination ---
# Аналогично ранее построенной модели p-value < 0.05 => есть сильная
# причинно-следственная связь между регрессором и объясняемой переменной;
# константное значение (Intercept) и регрессор Examination были оценены в "***",
# что значит, что они сильно статистически связаны. К тому же коэфф. k
# зависимости Agriculture от Examination отрицательный (k = -1.9544), откуда следует,
# что Agriculture и Examination находятся в сильной обратной зависимости.
# Коэффициент детерминации R-squared оказался равным 0.4713 (выше предыдущей модели),
# что значит, что модель неплоха для парной регрессии, но плоха в общем случае,
# ее нужно значительно улучшать, добавляя в модель дополнительные регрессоры.
model2 = lm(formula=Agriculture~Examination, data=swiss)
summary(model2)
