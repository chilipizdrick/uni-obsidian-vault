#show heading.where(level: 2): set heading(outlined: false)
#show heading.where(level: 3): set heading(outlined: false)

#set heading(numbering: "Приложение 1.", supplement: [Приложение])
#counter(heading).update(0)

= Реализация и тестирование алгоритма исключения Гаусса <gaussian-elimination-code>

#let code = read("../assets/code/src/gaussian_elimination.rs");
#raw(code, block: true, lang: "rust")

= Реализация и тестирование алгоритма вычисления интерполяционного полинома Лагранжа <lagrange-poly-code>

#let code = read("../assets/code/src/lagrange_poly.rs");
#raw(code, block: true, lang: "rust")

= Реализация и тестирование алгоритма Симпсона численного интегрирования <simpson-integral-code>

#let code = read("../assets/code/src/simpson_integral.rs");
#raw(code, block: true, lang: "rust")
