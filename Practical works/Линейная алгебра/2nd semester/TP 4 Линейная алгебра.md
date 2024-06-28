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
\end{vmatrix} = \end{gather}$$

$$\begin{gather}
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

#### $\lambda_{1} = 0$

$$\begin{pmatrix}
-2 & 1 & 1 \\
1 & -2 & 1 \\
1 & 1 & -2
\end{pmatrix} \vec{x}_{1} = \vec{0}$$

$$\begin{gather}
\left(\begin{array}{ccc|c}
-2 & 1 & 1 & 0 \\
1 & -2 & 1 & 0 \\
1 & 1 & -2 & 0
\end{array}\right) \to \left(\begin{array}{ccc|c}
0 & -3 & 3 & 0 \\
1 & -2 & 1 & 0 \\
0 & 3 & -3 & 0
\end{array}\right) \to \left(\begin{array}{ccc|c}
1 & -2 & 1 & 0 \\
0 & -1 & 1 & 0 \\
0 & 0 & 0 & 0
\end{array}\right) \to\end{gather}$$

$$\begin{gather}
\to \left(\begin{array}{ccc|c}
1 & -2 & 1 & 0 \\
0 & -1 & 1 & 0 \\
0 & 0 & 0 & 0
\end{array}\right) \implies \vec{x}_{1} = \begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix}
\end{gather}$$

#### $\lambda_{2,3} = 1$

$$\begin{gather}
\begin{pmatrix}
1 & 1 & 1 \\
1 & 1 & 1 \\
1 & 1 & 1
\end{pmatrix} \vec{x}_{2,3}
\end{gather} = \vec{0} \implies \vec{x}_{2,3} \in \left\{ \begin{pmatrix}
1 \\
-1 \\
0
\end{pmatrix}, \begin{pmatrix}
1 \\
0 \\
-1
\end{pmatrix} \right\}$$

Полученные собственные значения и соответствующие им собственные векторы показывают то, как преобразуется длина соотв. векторов из канонического базиса при проекции этих векторов на плоскость, данную в условии. Вектор $\begin{pmatrix}1 \\ 1 \\ 1\end{pmatrix}$ переходит в вектор $0\cdot \begin{pmatrix}1 \\ 1 \\ 1\end{pmatrix} = \begin{pmatrix}0 \\ 0 \\ 0\end{pmatrix}$, а векторы $\begin{pmatrix}1 \\ -1 \\ 0\end{pmatrix}$ и $\begin{pmatrix}1 \\ 0 \\ -1\end{pmatrix}$, уже лежащие в плоскости, никак не изменяются при применении к ним лин. оператора $\hat{A}$.