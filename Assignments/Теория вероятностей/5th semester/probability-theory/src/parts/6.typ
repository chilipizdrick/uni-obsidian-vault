#import "@preview/lilaq:0.5.0" as lq
#import "../lib.typ": *

Найти параметр $A$, математическое ожидание и дисперсию случайной величины $xi$, плотность вероятности которой $ f(x) = cases(A/sqrt(1 - x^2)\, space x in (-1, 1)\,, 0 \, space abs(x) >= a.) $

Найти $P{0 < xi < 1/2}$. Построить график плотности распределения вероятности случайной величины $xi$.

== Решение

$
  integral_(-1)^(+1) A/sqrt(1 - x^2) dif x = 1 \
  A integral_(-1)^(1) 1/sqrt(1 - x^2) dif x = 1 \
  arcsin x |_(-1)^1 = 1/A \
  A = 1/(2 arcsin 1) = 1/pi
$

Так как $arcsin x$ - четная функция, $integral_(-1)^1 x/sqrt(1-x^2) dif x = 0$, тогда $ma xi = 0$.

$
  di xi =1/pi integral_(-1)^1 x^2/sqrt(1-x^2) dif x = 1/2.
$

Найдем вероятность $P{0 < xi < 1/2}$: $ 1/pi integral_0^(1/2) 1/sqrt(1-x^2) dif x = 1/pi (arcsin 1/2 - 0) = 1/6. $

#{
  let x = lq.linspace(-0.95, 0.95, num: 100)
  let y = x => 1 / calc.pi / calc.sqrt(1 - calc.pow(x, 2))

  let diag = lq.diagram(
    title: [Плотность распределения вероятности],
    ylabel: $f(x) = 1/pi dot 1/sqrt(1-x^2)$,
    xlabel: $x$,
    width: 60%,
    height: 30%,
    lq.plot(x, y, smooth: true, mark: none),
  )

  align(center, diag)
}
