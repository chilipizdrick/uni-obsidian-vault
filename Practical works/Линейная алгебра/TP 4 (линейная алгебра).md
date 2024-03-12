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

Из полученного уравнения получаем один действительный и два комплексных корня:

$$\left[\begin{align}
&k = 3 \\
&k = \frac{3}{2} + \frac{\sqrt{ 3 }}{2}i \\
&k = \frac{3}{2} - \frac{\sqrt{ 3 }}{2}i
\end{align}\right. \implies$$

$$\implies \left[\begin{align}
&\lambda_{1} = 1 \\
&\lambda_{2} = \frac{1}{2} + \frac{\sqrt{ 3 }}{6}i \\
&\lambda_{3} = \frac{1}{2} - \frac{\sqrt{ 3 }}{6}i
\end{align}\right.$$

Теперь, применяя полученные собственные значения, найдем собственные векторы:

#### $\lambda_{1} = 1$

$$\begin{gather}
\begin{pmatrix}
\frac{2}{3} - 1 & -\frac{1}{3} & -\frac{1}{3} \\
-\frac{1}{3} & \frac{2}{3} - 1 & -\frac{1}{3} \\
-\frac{1}{3} & -\frac{1}{3} & \frac{2}{3} - 1
\end{pmatrix}\begin{pmatrix}
x \\
y \\
z
\end{pmatrix} = 1\cdot \begin{pmatrix}
x \\
y \\
z
\end{pmatrix} \\
-\frac{1}{3}\begin{pmatrix}
1 & 1 & 1 \\
1 & 1 & 1 \\
1 & 1 & 1
\end{pmatrix}\begin{pmatrix}
x \\
y \\
z
\end{pmatrix} = \begin{pmatrix}
x \\
y \\
z
\end{pmatrix}
\end{gather}$$

$$
\begin{gather}
\begin{cases}
\frac{1}{3}(x+y+z) = -x \\
\frac{1}{3}(x+y+z) = -y \\
\frac{1}{3}(x+y+z) = -z
\end{cases} \implies \begin{cases}
x+y+z = -3x \\
x+y+z = -3y \\
x+y+z = -3z
\end{cases} \implies \\
\implies \begin{cases}
4x + y + z = 0 \\
x + 4y + z = 0 \\
x + y + 4z = 0
\end{cases} \\
\left(\begin{array}{ccc|c}
4 & 1 & 1 & 0 \\
1 & 4 & 1 & 0 \\
1 & 1 & 4 & 0
\end{array}\right) \to \left(\begin{array}{ccc|c}
4 & 1 & 1 & 0 \\
1 & 4 & 1 & 0 \\
0 & -3 & 3 & 0
\end{array}\right) \to \left(\begin{array}{ccc|c}
4 & 1 & 1 & 0 \\
1 & 4 & 1 & 0 \\
0 & 0 & 6 & 0
\end{array}\right) \to \\
\to \left(\begin{array}{ccc|c}
1 & 4 & 1 & 0 \\
0 & -15 & -3 & 0 \\
0 & 0 & 1 & 0
\end{array}\right) \to \left(\begin{array}{ccc|c}
1 & 4 & 1 & 0 \\
0 & 5 & 1 & 0 \\
0 & 0 & 1 & 0
\end{array}\right)
\end{gather}$$
