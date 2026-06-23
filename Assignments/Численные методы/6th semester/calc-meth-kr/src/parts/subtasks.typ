= Подзадачи и связь между ними

Для достижения итоговой цели (нахождения площади $S$) задача была разбита на три последовательно выполняемые подзадачи:
1. *Решение СЛАУ*. На основе исходной матрицы и вектора правой части вычисляются координаты $(x_i, y_i)$.
2. *Интерполяция*. Полученные на предыдущем шаге узлы $(x_i, y_i)$ используются для построения функции $y = P_4(x)$.
3. *Численное интегрирование*. Построенный интерполянт интегрируется на заданном отрезке $[2, 10]$ с требуемой точностью.

Визуально взаимосвязь выделенных подзадач представлена на схеме (@subtask-relations).

#import "@preview/fletcher:0.5.5" as fletcher: diagram, edge, node

#let task-style = (stroke: 1pt + black, fill: rgb("fce9c0"), inset: 10pt)
#let data-style = (stroke: 1pt + black, inset: 8pt, fill: rgb("c0d7fc"))

#figure(
  diagram(
    spacing: (1.5em, 1cm),

    node(
      (0, 0),
      [СЛАУ ($A, arrow(x)$)],
      ..data-style,
      name: <start>,
    ),
    node(
      (0, 1),
      [1. Решение СЛАУ],
      ..task-style,
      name: <slae>,
    ),
    node(
      (0, 2),
      [Интерполяционные узлы $(x_i, y_i)$],
      ..data-style,
      name: <nodes>,
    ),
    node(
      (0, 3),
      [2. Построение интерполяционного многочлена $P_4(x)$],
      ..task-style,
      name: <interp>,
    ),
    node(
      (0, 4),
      [Значения $P_4(x)$ для вычисления интеграла],
      ..data-style,
      name: <poly>,
    ),
    node(
      (0, 5),
      [3. Вычисление интеграла $integral_2^10 P_4(x) dif x$],
      ..task-style,
      name: <integral>,
    ),
    node(
      (0, 6),
      [Значение $S$ интеграла],
      ..data-style,
      name: <s-value>,
    ),

    edge(<start>, <slae>, "->"),
    edge(<slae>, <nodes>, "->", [Значения $y_i$]),
    edge(<nodes>, <interp>, "->"),
    edge(<interp>, <poly>, "->"),
    edge(<poly>, <integral>, "->"),
    edge(<integral>, <s-value>, "->"),

    edge(
      <start>,
      <nodes>,
      "->",
      bend: -80deg,
      [Значения $x_i$],
    ),
  ),
  caption: "Схема взаимосвязи выделенных подзадач",
) <subtask-relations>

#include "subtasks/subtask_1.typ"
#include "subtasks/subtask_2.typ"
#include "subtasks/subtask_3.typ"
