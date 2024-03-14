---
tags:
  - типовой-рассчет
  - 2nd-semester
  - 11-03-2024
  - линал
---

## Алгебра и геометрия ТР 4

### Ершов Алексей Геннадьевич КМБО-03-23

### Вариант 4

$$\begin{gather}
\hat{A}: P_{3} \to P_{3} \\
\text{проектирование на плоскость} \ x+y+z = 0
\end{gather}$$

Из задачи 3 получаем матрицу $\hat{A}_{\{ E \}}$:

$$\hat{A} = \frac{1}{3}\begin{pmatrix}
2 & -1 & -1 \\
-1 & 2 & -1 \\
-1 & -1 & 2
\end{pmatrix}$$

### а) Нахождение собственных значений и векторов

Согласно преобразованию

$$\hat{A} \vec{x} = \lambda \vec{x} \implies | A - \lambda I | = 0$$

Находим собственные значения матрицы $\hat{A}$:

$$\begin{vmatrix}
\frac{2}{3} - \lambda & -\frac{1}{3} & -\frac{1}{3} \\
-\frac{1}{3} & \frac{2}{3} - \lambda & -\frac{1}{3} \\
-\frac{1}{3} & -\frac{1}{3} & \frac{2}{3} - \lambda
\end{vmatrix} = 0$$

принимая $3\lambda = k$, можем вынести $-\frac{1}{3}$:

$$\begin{gather}
\cancel{ -\frac{1}{3} } \begin{vmatrix}
k - 2 & 1 & 1 \\
1 & k - 2 & 1 \\
1 & 1 & k - 2
\end{vmatrix} = 0 \\
(k-2)^{3} + 2 - 3(k-2)^{3} = 0 \\
\cancel{ -2 }(k-3)(k^{2} - 3k + 3) = 0
\end{gather}$$

$$\begin{gather}
\begin{vmatrix}
k - 2 & 1 & 1 \\
1 & k - 2 & 1 \\
1 & 1 & k - 2
\end{vmatrix} = \\
(k-2)\begin{vmatrix}
k-2 & 1 \\
1  & k-2
\end{vmatrix} - \begin{vmatrix}
1 & 1 \\
1 & k-2
\end{vmatrix} + \begin{vmatrix}
1 & k-2 \\
1 & 1
\end{vmatrix} = \\
= (k-2)[(k-2)^{2} - 1] - ([k-2] - 1) + (1 - [k-2]) = \\
= (k-2)^{3} - (k-2) - (k-2) + 1 + 1 - (k-2) = \\
= (k-2)^{3} - 3(k-2) + 2 = (k-3)([k-2]^{2} + [k-2] - 2) = \\
= (k-3)(k^{2} - 3k) = k(k-3)^{2} \implies \\
\implies k(k-3)^{2} = 0
\end{gather}$$

Из полученного уравнения получаем три действительных корня:

$$\left[\begin{align}
&k_{1} = 0 \\
&k_{2,3} = 3
\end{align}\right. \implies$$

$$\implies \left[\begin{align}
&\lambda_{1} = 0 \\
&\lambda_{2,3} = 1
\end{align}\right.$$

Теперь, применяя полученные собственные значения, найдем собственные векторы:

#### $\lambda_{2,3} = 1$

$$\begin{gather}
\begin{pmatrix}
1 & 1 & 1 \\
1 & 1 & 1 \\
1 & 1 & 1
\end{pmatrix} \vec{x}_{1}
\end{gather} = \vec{0} \implies \vec{x}_{1} \in \left\{ \begin{pmatrix}
1 \\
-1 \\
0
\end{pmatrix}, \begin{pmatrix}
1 \\
0 \\
-1
\end{pmatrix} \right\}$$

#### $\lambda_{2} = \frac{1}{2}+\frac{\sqrt{ 3 }}{6}i$

$$\begin{gather}
\begin{pmatrix}
-\frac{1}{2} + \frac{\sqrt{ 3 }}{6}i & 1 & 1 \\
1 & -\frac{1}{2} + \frac{\sqrt{ 3 }}{6}i & 1 \\
1 & 1 & -\frac{1}{2} + \frac{\sqrt{ 3 }}{6}i
\end{pmatrix} \vec{x}_{2} = \vec{0}
\end{gather}$$