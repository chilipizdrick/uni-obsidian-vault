#import "@preview/lilaq:0.5.0" as lq
#import "../lib.typ": *

Случайный вектор $(xi, eta)$ распределен равномерно в области $G$, изображенной на рисунке:

#align(center, image("../images/1.png", width: 30%))

+ Найти плотности распределения вероятностей компонент случайного вектора и решить вопрос об их зависимости (независимости).
+ Выяснить, коррелированы или некоррелированы компоненты случайного вектора $(xi, eta)$.
+ Найти функцию и плотность распределения вероятностей для случайной величины $(xi + eta)$.
+ Найти $P{(xi,eta) in D}$, где $D = {(x,y) | x^2 + y^2 <= 1}$.

== Решение

*1.* Объем изображенной на рисунке области равна $3$, следовательно совместная плотность распределения в области $G$ равен $1/3$, а вне ее --- $0$: $ rho_(xi,eta)(x,y) = cases(1/3\, space (x,y) in G\,, 0\, space (x,y) in.not G.) $

Найдем плотность вероятности для $xi$. Так как $integral_G rho_(xi,eta)(x,y) dif v = 1$: $ 1/3 integral_(-1)^0 integral_(-1)^(x+1) dif y dif x + 1/3 integral_0^1 integral_(x-1)^1 dif y dif x = 1 \
integral_(-1)^0 (x+2)/3 dif x + integral_0^1 (2-x)/3 dif x = 1 \
rho_(xi)(x) = cases((x+2)/3\, space x in [-1; 0), (2-x)/3\, space x in [0; 1]) $

Аналогично найдем плотность вероятности для $eta$: $ 1/3 integral_(-1)^0 integral_(-1)^(y+1) dif x dif y + 1/3 integral_0^1 integral_(y-1)^1 dif x dif y = 1 \
integral_(-1)^0 (y+2)/3 dif y + integral_0^1 (2-y)/3 dif y = 1 \
rho_(eta)(y) = cases((y+2)/3\, space y in [-1; 0), (2-y)/3\, space y in [0; 1]) $

Очевидно, $xi$ и $eta$ --- зависимы. Как видно на рисунке, при больших $xi$ наблюдаются большие $eta$.

*2.*

$
  ma xi = ma eta = integral_(-1)^0 (x^2+2x)/3 dif x + integral_0^1 (2x-x^2)/3 dif x = \
  = lr((x^3/9 + x^2/3)|)_(-1)^0 + lr((x^2/3 - x^3/9)|)_0^1 = 1/9 - 1/3 + 1/3 - 1/9 = 0
$

$
  di xi = di eta = integral_(-1)^0 (x^2(x + 2))/3 dif x + integral_0^1 (x^2(2-x))/3 dif x = 10/36 \
$

$
  cov(xi, eta) = integral_(-infinity)^infinity (x-ma xi)(y-ma eta) rho_(xi,eta)(x, y) dif x dif y
$

$
  cov(xi, eta) = 1/3 integral_(-1)^0 x integral_(-1)^(x+1) y dif y dif x + 1/3 integral_0^1 x integral_(x-1)^1 y dif y dif x = 10/72 \
$

$
  upright(r)(xi, eta) = (10\/72)/(10\/36) = 1/2
$

Компоненты $xi$ и $eta$ имеют положительную корреляцию.

*3.* Понять внешний вид функции плотности вероятности для случайной величины $xi + eta$ можно визуально. Если брать срезы области $G$ вида $y= -x + b$, где $b in [-2, 2]$, то можно заметить, что на этих срезах величина $xi + eta$ - постоянна и равна $b$. Тогда непосредственная длина сечения и будет значением функции плотности вероятности и ее график будет выглядеть следующим образом:

#align(center, image("../images/2.svg"))

Вычислив интеграл, подсчитаем $A$: $ integral_(-2)^(-1) A(x+2) dif x + integral_(-1)^1 A dif x + integral_1^2 A(2-x) dif x = 1 \
A = 1/3 $

Тогда функция плотности вероятности принимает вид: $ rho_(xi+eta)(x) = cases(0\, space x in (-infinity; -2) union [2; +infinity), (x+2)/3\, space x in [-2; 1), 1/3\, space x in [-1; 1), (2-x)/3\, space x in [1; 2)) $

Теперь "по кускам" подсчитаем функцию распределения $F_(xi+eta)(x)$: $ integral_(-2)^x (t+2)/3 dif t = x^2/6 + (2x)/3 + 2/3 \
1/6 + integral_(-1)^x 1/3 dif t = x/3 + 1/2 \
2/3 + 1/6 + integral_1^x (2-t)/3 dif t = (2x)/3 -t^2/6 + 1/3 $

Наконец, функция распределения принимает вид: $ F_(xi+eta)(x) = cases(0\, space x in (-infinity; -2), x^2/6 + (2x)/3 + 2/3\, space x in [-2; -1), x/3 + 1/2\, space x in [-1; 1), (2x)/3 -x^2/6 + 1/3\, space x in [1; 2), 1\, space x in [2; infinity)) $

#{
  let x = lq.linspace(-2.5, 2.5, num: 50)
  let y = x => if x < -2 {
    0
  } else if x < -1 {
    x * x / 6 + 2 / 3 * x + 2 / 3
  } else if x < 1 {
    1 / 3 * x + 1 / 2
  } else if x < 2 {
    2 / 3 * x - x * x / 6 + 1 / 3
  } else {
    1
  }

  let diag = lq.diagram(
    title: [Функция распределения],
    ylabel: $F_(xi+eta)(x)$,
    xlabel: $x$,
    width: 60%,
    height: 30%,
    lq.plot(x, y, smooth: true, mark: none),
  )

  align(center, diag)
}

#block(breakable: false)[
  *4.* Вероятность $P((xi, eta) in {(x,y) | x^2+y^2 <= 1})$ можно несложно подсчитать геометрически. Площадь не попадающих в объем шара участков области $G$ равна $1-pi/4$, тогда вероятность $P((xi, eta) in {(x,y) | x^2+y^2 <= 1}) = 3 - 2(1-pi/4) = 1+pi/2$.

  #align(center, image("../images/3.svg"))
]
