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

# k = -1.5105, R^2 = 0.409
model1 = lm(formula=Agriculture~Education, data=swiss)
summary(model1)

# k = -1.9544, R^2 = 0.4713
model2 = lm(formula=Agriculture~Examination, data=swiss)
summary(model2)
