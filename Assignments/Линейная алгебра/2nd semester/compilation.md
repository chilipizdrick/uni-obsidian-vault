
# Типовой расчет по алгебре и геомерии

## Ершов Алексей  КМБО-03-23

### Вариант 4

| 1    | 2   | 3   | 4   | 5   | 5.5 | 6   | 7   | 8   | 9   |
| ---- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| <br> |     |     |     |     |     |     |     |     |     |

#

## ТР 1

$$\begin{gather}
\hat{A}: P_{3} \to P_{3} \\
\hat{A}(p(t)) = t \frac{dp(t+1)}{dt}
\end{gather}$$

### а) Доказать, что $\hat{A}$ - линейный оператор

$$\begin{gather}
1) \ \hat{A}(p(t) + q(t)) = \hat{A}(p(t)) + \hat{A}(q(t)) = t \frac{dp(t+1)}{dt} + t \frac{dq(t+1)}{dt} = \\
= t\left( \frac{d}{dt} p(t+1) + \frac{d}{dt} q(t+1)\right) = \underset{\text{по сво-ву произв. суммы}}{t\cdot \frac{d}{dt} (p(t+1) + q(t+1))} = \\
= \hat{A}(p(t) + q(t))
\end{gather}$$

$$\begin{gather}
2) \ \hat{A}(\lambda p(t)) = \lambda\hat{A}(p(t)) = \lambda \cdot t\cdot \frac{d}{dt} p(t+1) = \underset{\text{по сво-ву произв. коэф.}}{t \cdot \frac{d}{dt}(\lambda p(t+1))} = \\
= \hat{A}(\lambda p(t))
\end{gather}$$

Как видно, отображение $\hat{A}$ обладает линейными свойствами, а значит оно является линейным оператором в линейном пространстве $P_{3}$.

### б) Найти матрицу $\hat{A}$

$$\begin{align}
&\hat{A}(1) = 0 = \begin{pmatrix}
0 \\
0 \\
0 \\
0
\end{pmatrix} \\ &\hat{A}(t) = t = \begin{pmatrix}
0 \\
1 \\
0 \\
0
\end{pmatrix} \\
\end{align}$$

$$\begin{align}
&\hat{A}(t^{2}) = 2t^{2} + 2t = \begin{pmatrix}
0 \\
2 \\
2 \\
0
\end{pmatrix} \\
&\hat{A}(t^{3}) = 3t^{3}+6t^{2}+3t = \begin{pmatrix}
0 \\
3 \\
6 \\
3
\end{pmatrix}
\end{align}$$

Таким образом, матрица оператора $\hat{A}$ будет иметь вид:

$$\hat{A}_{\{ E \}} = \begin{pmatrix}
0 & 0 & 0 & 0 \\
0 & 1 & 2 & 3 \\
0 & 0 & 2 & 6 \\
0 & 0 & 0 & 3
\end{pmatrix}$$

### в) Существование обратного оператора

Данный линейный оператор не имеет обратного оператора, т.к. для его существования необходимо, чтобы $\det \hat{A}_{\{ E \}} \neq 0$, а полученная матрица оператора имеет столбец, состоящий из нулей, следовательно, $\det \hat{A}_{\{ E \}} = 0$.

### г) $\mathrm{Im} \ \hat{A},  \mathrm{Ker} \ \hat{A}, \ \mathrm{def} \ \hat{A}, \ \mathrm{rank} \ \hat{A}$

Для того, чтобы найти $\mathrm{Ker} \ \hat{A}$, решим след. систему:

$$\left(\begin{array}{cccc|c}
0 & 0 & 0 & 0 & 0 \\
0 & 1 & 2 & 3 & 0 \\
0 & 0 & 2 & 6 & 0 \\
0 & 0 & 0 & 3 & 0
\end{array}\right) \to \left(\begin{array}{cccc|c}
0 & \underline 1 & 2 & 3 & 0 \\
0 & 0 & \underline 1 & 3 & 0 \\
0 & 0 & 0 & \underline 1 & 0
\end{array}\right) \implies \begin{cases}
x_{1} = C \\
x_{2} = 0 \\
x_{3} = 0 \\
x_{4} = 0
\end{cases}$$

Следовательно, $\mathrm{Ker} \ \hat{A}$ будет иметь вид:

$$\begin{gather}
\mathrm{Ker} \ \hat{A} = \left\{ C\begin{pmatrix}
1 \\
0 \\
0 \\
0
\end{pmatrix} \right\} \implies \mathrm{def} \ \hat{A} = 1 \\
\text{Представление в виде многочлена:} \\
\mathrm{Ker} \ \hat{A} = \{ p(t) \ | \ p(t) = C \}, \ C \in \mathbb{R}
\end{gather}$$

А $\mathrm{Im} \ A$ будет равняться линейной оболочке всех линейно-независимых столбцов матрицы $\hat{A}$:

$$\begin{gather}
\mathrm{Im} \ \hat{A} = \mathrm{span} \left(\begin{pmatrix}
0 \\
1 \\
0 \\
0
\end{pmatrix},\begin{pmatrix}
0 \\
2 \\
2 \\
0
\end{pmatrix}, \begin{pmatrix}
0 \\
3 \\
6 \\
3
\end{pmatrix}\right) = \left\{ C_{1}\begin{pmatrix}
0 \\
1 \\
0 \\
0
\end{pmatrix} + C_{2}\begin{pmatrix}
0 \\
1 \\
1 \\
0
\end{pmatrix} + C_{3}\begin{pmatrix}
0 \\
1 \\
2 \\
3
\end{pmatrix} \right\}
\end{gather}$$

$$\begin{gather}
\implies \mathrm{rank} \ \hat{A} = 3 \\
\text{Представление в виде многочлена:} \\
\mathrm{Im} \ \hat{A} = \{ p(t) \ | \ p(t) = 3C_{3}t^{3} + (C_{2} + 2C_{3})t^{2} + (C_{1} + C_{2} + C_{3})t \}
\end{gather}$$

## ТР 2

$$\begin{gather}
\hat{A}: P_{3} \to P_{3} \\
\hat{A}(p(t)) = t \frac{dp(t+1)}{dt} \\
p(t) = t^{2} + 4 \\
q(t) = 2t^{2} + t
\end{gather}$$

### а) Найти образ $p(t)$

$$\hat{A}(t^{2}+4) = t \cdot \frac{d}{dt}((t+1)^{2}+4) = t \cdot (2t + 2) = 2t^{2} + 2t$$

### б) Найти прообраз $q(t)$

$$\hat{A}_{\{ E \}} = \begin{pmatrix}
0 & 0 & 0 & 0 \\
0 & 1 & 2 & 3 \\
0 & 0 & 2 & 6 \\
0 & 0 & 0 & 3
\end{pmatrix}$$

Чтобы найти прообраз $q(t) = 2t^{2} + t$, решим систему:

$$\left(\begin{array}{cccc|c}
0 & 0 & 0 & 0 & 0 \\
0 & 1 & 2 & 3 & 1 \\
0 & 0 & 2 & 6 & 2 \\
0 & 0 & 0 & 3 & 0
\end{array}\right) \to \left(\begin{array}{cccc|c}
0 & \underline 1 & 2 & 3 & 1 \\
0 & 0 & \underline 1 & 3 & 1 \\
0 & 0 & 0 & \underline 1 & 0
\end{array}\right) \implies \begin{cases}
x_{1} = C \\
x_{2} = -1 \\
x_{3} = 1 \\
x_{4} = 0
\end{cases}$$

Таким образом, прообраз многочлена $q(t)$ - один из многочленов вида:

$$u(t) = t^{2} - t + C, \ C \in \mathbb{R}$$

Проверка:

$$\begin{gather}
\hat{A}(u(t)) = t\cdot\frac{d}{dt}((t+1)^{2} - (t+1) + C) = \\
= t\cdot\frac{d}{dt}(t^{2} + t + C) = 2t^{2} + t 
\end{gather}$$

## ТР 3

$$\begin{gather}
\hat{A}: P_{3} \to P_{3} \\
\text{проектирование на плоскость} \ x+y+z = 0
\end{gather}$$

### а) Найти матрицу отображения $\hat{A}$

Возьмем базис из 3-х взаимноперпендикулярных векторов $B = \langle \vec{n},\vec{a},\vec{b} \rangle$:

1) $\vec{n} = \begin{pmatrix} 1 \\ 1 \\ 1 \end{pmatrix}$ - вектор нормали плоскости $x+y+z = 0$
2) $\vec{a} = \begin{pmatrix} 1 \\ -1 \\ 0 \end{pmatrix} \in P = \{ x+y+z = 0 \}$
3) $\vec{b} = \vec{n}\times \vec{a} = \begin{pmatrix} 1 \\ 1 \\ -2 \end{pmatrix} \in P = \{ x+y+z = 0 \}$

Следовательно, матрица перехода $C_{B\to E}$ будет иметь вид:

$$C_{B\to E} = \begin{pmatrix}
1 & 1 & 1 \\
1 & -1 & 1 \\
1 & 0 & -2
\end{pmatrix}$$

Заодно найдем матрицу обратного перехода:

$$\begin{gather}
C_{E\to B} = C_{B\to E}^{-1} = \frac{C_{B\to E \ *}^{T}}{\det C_{B\to E}} = \frac{1}{6} \begin{pmatrix}
2 & 2 & 2 \\
3 & -3 & 0 \\
1 & 1 & -2
\end{pmatrix}
\end{gather}$$

Матрица отображения $\hat{A}$ в силу свойств выбранных базисных векторов будет иметь вид:

$$\hat{A}_{\{ B \}} = \begin{pmatrix}
0 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{pmatrix}$$

В базисе $E$ матрица отображения $\hat{A}$ будет равна

$$\begin{gather}
C_{E\to B} \hat{A}_{\{ B \}}C_{B \to E} = \frac{1}{6}\begin{pmatrix}
2 & 2 & 2 \\ 3 & -3 & 0 \\
1 & 1 & -2
\end{pmatrix} \begin{pmatrix}
0 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{pmatrix} \begin{pmatrix}
1 & 1 & 1 \\
1 & -1 & 1 \\
1 & 0 & -2
\end{pmatrix} = \\
= \frac{1}{6} \begin{pmatrix}
0 & 1 & 1 \\
0 & -1 & 1 \\
0 & 0 & -2
\end{pmatrix} \begin{pmatrix}
1 & 1 & 1 \\
1 & -1 & 1 \\
1 & 0 & -2
\end{pmatrix} = \frac{1}{6} \begin{pmatrix}
4 & -2 & -2 \\
-2 & 4 & -2 \\
-2 & -2 & 4
\end{pmatrix} = \end{gather}$$

$$\begin{gather}
= \frac{1}{3}\begin{pmatrix}
2 & -1 & -1 \\
-1 & 2 & -1 \\
-1 & -1 & 2
\end{pmatrix} = \begin{pmatrix}
\frac{2}{3} & -\frac{1}{3} & -\frac{1}{3} \\
-\frac{1}{3} & \frac{2}{3} & -\frac{1}{3} \\
-\frac{1}{3} & -\frac{1}{3} & \frac{2}{3}
\end{pmatrix}
\end{gather}$$
### б) Образ точки $(1,0,0)$

Найдем отображение вектора $\begin{pmatrix} 1 \\ 0 \\ 0 \end{pmatrix}$, оно и будет отображением соответствующей точки:

$$\hat{A}\begin{pmatrix}
1 \\
0 \\
0
\end{pmatrix} = \frac{1}{3}\begin{pmatrix}
2 & -1 & -1 \\
-1 & 2 & -1 \\
-1 & -1 & 2
\end{pmatrix}\begin{pmatrix}
1 \\
0 \\
0
\end{pmatrix} = \frac{1}{3}\begin{pmatrix}
2 \\
-1 \\
-1
\end{pmatrix} = \begin{pmatrix}
\frac{2}{3} \\
-\frac{1}{3} \\
-\frac{1}{3}
\end{pmatrix}$$

## ТР 4

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

## ТР 5

$$\begin{gather}
M = \left\{ X = \begin{pmatrix}
x & y \\
u & v
\end{pmatrix} \ \Big| \ x+v = 0 \right\} \ \left(x+v = 0 \iff \mathrm{tr} \ A = 0\right) \\
\hat{A}(X) = BX-XB, \ B = \begin{pmatrix}
0 & 1 \\
1 & 0
\end{pmatrix}
\end{gather}$$

$$\begin{gather}
\hat{A}(X) = BX - XB = \begin{pmatrix}
0 & 1 \\
1 & 0
\end{pmatrix}\begin{pmatrix}
x & y \\
u & v
\end{pmatrix} - \begin{pmatrix}
x & y \\
u & v
\end{pmatrix}\begin{pmatrix}
0 & 1 \\
1 & 0
\end{pmatrix} = \\
= \begin{pmatrix}
u & v \\
x & y
\end{pmatrix} - \begin{pmatrix}
y & x \\
v & u
\end{pmatrix} = \begin{pmatrix}
u-y & v-x \\
x-v & y-u
\end{pmatrix}
\end{gather}$$

### 1. Доказать, что $\hat{A}$ - линейный оператор в М

$$\begin{gather}
1) \ \hat{A}(X+Y) = B(X+Y) - (X+Y)B = BX + BY - XB - YB = \\
= (BX - XB) + (BY - YB) = \hat{A}(X) + \hat{A}(Y)
\end{gather}$$

$$\begin{gather}
2) \ \hat{A}(\lambda X) = B\lambda X - \lambda XB = \lambda(BX - XB) = \lambda \hat{A}(X)
\end{gather}$$

### 2. Найти матрицу $A$ оператора $\hat{A}$ в каком-нибудь базисе пространства М

Для простоты возьмем **почти** канонический базис пр-ва $M_{2\times 2}$ (в нашем случае $x = -v$, поэтому размерность пространства станет равна $\mathrm{dim} \ M = 3$):

$$E = \left\langle \begin{pmatrix}
1 & 0 \\
0 & -1
\end{pmatrix}, \begin{pmatrix}
0 & 1 \\
0 & 0
\end{pmatrix}, \begin{pmatrix}
0 & 0 \\
1 & 0
\end{pmatrix} \right\rangle$$

$$\begin{align}
&1) \ \hat{A}\begin{pmatrix}
1 & 0 \\
0 & -1
\end{pmatrix} = \begin{pmatrix}
0-0 & -1-1 \\
1-(-1) & 0-0
\end{pmatrix} = \begin{pmatrix}
0 & -2 \\
2 & 0
\end{pmatrix} = -2e_{2}+2e_{3} \\
&2) \ \hat{A}\begin{pmatrix}
0 & 1 \\
0 & 0
\end{pmatrix} = \begin{pmatrix}
0-1 & 0-0 \\
0-0 & 1-0
\end{pmatrix} = \begin{pmatrix}
-1 & 0 \\
0 & 1
\end{pmatrix} = -e_{1} \\
&3) \ \hat{A}\begin{pmatrix}
0 & 0 \\
1 & 0
\end{pmatrix} = \begin{pmatrix}
1-0 & 0-0 \\
0-0 & 0-1
\end{pmatrix} = \begin{pmatrix}
1 & 0 \\
0 & -1
\end{pmatrix} = e_{1}
\end{align}$$

$$\begin{gather}
\begin{cases}
\hat{A}(e_{1}) = \begin{pmatrix}
0 \\
-2 \\
2
\end{pmatrix} \\
\hat{A}(e_{2}) = \begin{pmatrix}
-1 \\
0 \\
0
\end{pmatrix} \\
\hat{A}(e_{3}) = \begin{pmatrix}
1 \\
0 \\
0
\end{pmatrix}
\end{cases} \implies A = \begin{pmatrix}
0 & -1 & 1 \\
-2 & 0 & 0 \\
2 & 0 & 0
\end{pmatrix}
\end{gather}$$

### 3. Найти собственные значения и собственные векторы оператора $\hat{A}$

$$\begin{vmatrix}
-\lambda & -1 & 1 \\
-2 & -\lambda & 0 \\
2 & 0 & -\lambda
\end{vmatrix} = 0$$

$$\begin{gather}
\begin{vmatrix}
-2 & -\lambda \\
2 & 0
\end{vmatrix} - \lambda \begin{vmatrix}
-\lambda & -1 \\
-2 & -\lambda
\end{vmatrix} = - \lambda^{3} + 4\lambda = -\lambda(\lambda^{2} - 4) = -\lambda(\lambda-2)(\lambda+2) \\
\lambda(\lambda-2)(\lambda+2) = 0 \\
\begin{cases}
\lambda_{1} = 0 \\
\lambda_{2} = 2 \\
\lambda_{3} = -2
\end{cases}
\end{gather}$$

#### $\lambda_{1} = 0$, $\vec{x}_{1}$ - ?

$$\begin{gather}
\begin{pmatrix}
0 & -1 & 1 \\
-2 & 0 & 0 \\
2 & 0 & 0
\end{pmatrix}\vec{x}_{1} = \vec{0} \implies \\
\implies \vec{x}_{1} = \begin{pmatrix}
0 \\
1 \\
1
\end{pmatrix}
\end{gather}$$

#### $\lambda_{2} = 2$, $\vec{x}_{2}$ - ?

$$\begin{gather}
\begin{pmatrix}
-2 & -1 & 1 \\
-2 & -2 & 0 \\
2 & 0 & -2
\end{pmatrix}\vec{x}_{2} = \vec{0} \\
\left(\begin{array}{ccc|c}
-2 & -1 & 1 & 0 \\
-2 & -2 & 0 & 0 \\
2 & 0 & -2 & 0
\end{array}\right) \sim \left(\begin{array}{ccc|c}
2 & 0 & -2 & 0 \\
0 & -2 & -2 & 0 \\
0 & -1 & -1 & 0
\end{array}\right) \sim \left(\begin{array}{ccc|c}
1 & 0 & -1 & 0 \\
0 & 1 & 1 & 0
\end{array}\right) \implies \\
\implies \vec{x}_{2} = \begin{pmatrix}
1 \\
-1 \\
1
\end{pmatrix}
\end{gather}$$

#### $\lambda_{3} = -2$, $\vec{x}_{3}$ - ?

$$\begin{gather}
\begin{pmatrix}
2 & -1 & 1 \\
-2 & 2 & 0 \\
2 & 0 & 2
\end{pmatrix}\vec{x}_{3} = \vec{0} \\
\left(\begin{array}{ccc|c}
2 & -1 & 1 & 0 \\
-2 & 2 & 0 & 0 \\
2 & 0 & 2 & 0
\end{array}\right) \sim \left(\begin{array}{ccc|c}
-1 & 1 & 0 & 0 \\
0 & 1 & 1 & 0 \\
0 & 1 & 1 & 0
\end{array}\right) \sim \left(\begin{array}{ccc|c}
-1 & 1 & 0 & 0 \\
0 & 1 & 1 & 0 
\end{array}\right) \implies \\
\implies \vec{x}_{3} = \begin{pmatrix}
1 \\
1 \\
-1
\end{pmatrix}
\end{gather}$$

### 4. Доказать, что $\hat{A}$ - оператор простого типа, описать его действие в собственном базисе

Оператор $\hat{A}$ является оператором простого типа т.к. из его собственных векторов можно составить базис линейного пространства $M$, на котором он действует (иными словами, все его собственные значения действительны и различны).

Проверить то, что оператор $\hat{A}$ является простым можно диагонализировав его

$$\Lambda = P^{-1}AP$$

$$\begin{gather}
B = \left\langle \begin{pmatrix}
0 \\
1 \\
1
\end{pmatrix}, \begin{pmatrix}
1 \\
-1 \\
1
\end{pmatrix}, \begin{pmatrix}
1 \\
1 \\
-1
\end{pmatrix} \right\rangle - \text{собтвенный базис} \implies \\
\implies P = \begin{pmatrix}
0 & 1 & 1 \\
1 & -1 & 1 \\
1 & 1 & -1
\end{pmatrix} \end{gather}$$

$$\begin{gather}
P^{-1} = \left(\begin{array}{ccc|ccc}
0 & 1 & 1 & 1 & 0 & 0 \\
1 & -1 & 1 & 0 & 1 & 0 \\
1 & 1 & -1 & 0 & 0 & 1
\end{array}\right) \sim \left(\begin{array}{ccc|ccc}
1 & 0 & 2 & 1 & 1 & 0 \\
1 & -1 & 1 & 0 & 1 & 0 \\
0 & 2 & -2 & 0 & -1 & 1
\end{array}\right) \sim \\
\sim \left(\begin{array}{ccc|ccc}
1 & 0 & 2 & 1 & 1 & 0 \\
0 & 1 & 1 & 1 & 0 & 0 \\
0 & 0 & -4 & -2 & -1 & 1
\end{array}\right) \sim \left(\begin{array}{ccc|ccc}
1 & 0 & 0 & 0 & \frac{1}{2} & \frac{1}{2} \\
0 & 1 & 0 & \frac{1}{2} & -\frac{1}{4} & \frac{1}{4} \\
0 & 0 & 1 & \frac{1}{2} & \frac{1}{4} & -\frac{1}{4}
\end{array}\right) = \\
= \begin{pmatrix}
0 & \frac{1}{2} & \frac{1}{2} \\
\frac{1}{2} & -\frac{1}{4} & \frac{1}{4} \\
\frac{1}{2} & \frac{1}{4} & -\frac{1}{4}
\end{pmatrix}
\end{gather}$$

$$\begin{gather}
\Lambda = P^{-1}AP = \begin{pmatrix}
0 & \frac{1}{2} & \frac{1}{2} \\
\frac{1}{2} & -\frac{1}{4} & \frac{1}{4} \\
\frac{1}{2} & \frac{1}{4} & -\frac{1}{4}
\end{pmatrix}\begin{pmatrix}
0 & -1 & 1 \\
-2 & 0 & 0 \\
2 & 0 & 0
\end{pmatrix}\begin{pmatrix}
0 & 1 & 1 \\
1 & -1 & 1 \\
1 & 1 & -1
\end{pmatrix} = \\
= \begin{pmatrix}
0 & \frac{1}{2} & \frac{1}{2} \\
\frac{1}{2} & -\frac{1}{4} & \frac{1}{4} \\
\frac{1}{2} & \frac{1}{4} & -\frac{1}{4}
\end{pmatrix}\begin{pmatrix}
0 & 2 & -2 \\
0 & -2 & -2 \\
0 & 2 & 2
\end{pmatrix} = \underbrace{\begin{pmatrix}
0 & 0 & 0 \\
0 & 2 & 0 \\
0 & 0 & -2
\end{pmatrix}}_{\text{диаг. матрица}}
\end{gather}$$

Таким образом, $\hat{A}$ - действительно простой линейный оператор.

#### Действие в собственном базисе оператора $\hat{A}$

$$\begin{gather}
B = \left\langle \begin{pmatrix}
0 \\
1 \\
1
\end{pmatrix}, \begin{pmatrix}
1 \\
-1 \\
1
\end{pmatrix}, \begin{pmatrix}
1 \\
1 \\
-1
\end{pmatrix} \right\rangle \sim \left\langle \begin{pmatrix}
0 & 1 \\
1 & 0
\end{pmatrix}, \begin{pmatrix}
1 & -1 \\
1 & -1
\end{pmatrix}, \begin{pmatrix}
1 & 1 \\
-1 & -1
\end{pmatrix} \right\rangle \end{gather}$$

$$\begin{gather}
\begin{cases}
\hat{A}\begin{pmatrix}
0 & 1 \\
1 & 0
\end{pmatrix} = \begin{pmatrix}
0 & 0 \\
0 & 0
\end{pmatrix} \\
\hat{A}\begin{pmatrix}
1 & -1 \\
1 & -1
\end{pmatrix} = \begin{pmatrix}
-2 & 2 \\
-2 & 2
\end{pmatrix} \\
\hat{A}\begin{pmatrix}
1 & 1 \\
-1 & -1
\end{pmatrix} = \begin{pmatrix}
-2 & -2 \\
2 & 2
\end{pmatrix}
\end{cases}
\end{gather}$$

Действие оператора $\hat{A}$ в собственном базисе чем-то похоже на проекцию некоторого 3-мерного вектора, представленного матрицей $2\times 2$ на плоскость.

## ТР 5.5

$$\begin{gather}
X = \begin{pmatrix}
-4 & 1 & 1 \\
-7 & 4 & 10 \\
4 & -4 & -9
\end{pmatrix} \ Y = \begin{pmatrix}
1 & 3 & -3 \\
-1 & 7 & -5 \\
-2 & 8 & -5
\end{pmatrix} \ Z = \begin{pmatrix}
2 & 1 & 0 \\
0 & 3 & 0 \\
0 & 0 & 3
\end{pmatrix}
\end{gather}$$

Для каждой из указанных матриц:
1. Найти характеристический и минимальный многочлены.
2. Найти корневые подпространства.
3. Найти базис, в котором матрица приводится к стандартному блочно-диагональному виду, в котором стандартные блоки являются либо Жордановыми клетками, либо матрицей умножения на комплексное число.
4. Пользуясь минимальным многочленом, вычислить обратную матрицу как линейную комбинацию ее степеней, меньших степени минимального многочлена.
5. Вычислить явно $n$-ую степень каждой матрицы.

## $X$:

### 1.

$$\begin{gather}
\mathcal{X}_{X} = \begin{vmatrix}
-4-\lambda & 1 & 1 \\
-7 & 4-\lambda & 10 \\
4 & -4 & -9-\lambda
\end{vmatrix} = \\
= -(4+\lambda)\begin{vmatrix}
4-\lambda & 10 \\
-4 & -9-\lambda
\end{vmatrix} - \begin{vmatrix}
-7 & 10 \\
4 & -9-\lambda
\end{vmatrix} + \begin{vmatrix}
-7 & 4-\lambda \\
4 & -4
\end{vmatrix} = \\
= -(4+\lambda)((4-\lambda)(-9-\lambda)+40)-(7(9+\lambda)-40)+(28-4(4-\lambda))= \end{gather}$$

$$\begin{gather}
=-(4+\lambda)(-36-4\lambda+9\lambda+\lambda^{2}+40)-(63+7\lambda-40)+(28-16+4\lambda)= \\
=-(4+\lambda)(4+5\lambda+\lambda^{2})-(23+7\lambda)+(12+4\lambda)= \\
=-16-20\lambda-4\lambda^{2}-4\lambda-5\lambda^{2}-\lambda^{3}-23-7\lambda+12+4\lambda= \\
=-\lambda^{3}-9\lambda^{2}-27\lambda-27= \\
=(\lambda + 3)^{3}
\end{gather}$$

$$\begin{gather}
\mathcal{X}_{X}(x) = \mathcal{M}_{X}(x) = (x+3)^{3} \\
\begin{pmatrix}
-1 & 1 & 1 \\
-7 & 7 & 10 \\
4 & -4 & -6
\end{pmatrix}^{3} = \begin{pmatrix}
0 & 0 & 0 \\
0 & 0 & 0 \\
0 & 0 & 0
\end{pmatrix}
\end{gather}$$

### 2.

Для нахождения корневых векторов, построим Жордановы цепочки:

### $X (\lambda_{1,2,3} = -3):$

$$\begin{gather}
(A - \lambda I)\vec{x}_{k-1} = \vec{x}_{k}, \ \vec{x}_{0} = \begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix} - \text{корневой вектор глубины} \ 3 \\
\begin{pmatrix}
-1 & 1 & 1 \\
-7 & 7 & 10 \\
4 & -4 & -6
\end{pmatrix}\begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix} = \begin{pmatrix}
1 \\
10 \\
-6
\end{pmatrix} = \vec{x}_{1} - \text{корневой вектор глубины} \ 2 \\\end{gather}$$

$$\begin{gather}
\begin{pmatrix}
-1 & 1 & 1 \\
-7 & 7 & 10 \\
4 & -4 & -6
\end{pmatrix}\begin{pmatrix}
1 \\
10 \\
-6
\end{pmatrix} = \begin{pmatrix}
3 \\
3 \\
0
\end{pmatrix} = \vec{x}_{2} - \text{корневой вектор глубины} \ 1 \\
\begin{pmatrix}
-1 & 1 & 1 \\
-7 & 7 & 10 \\
4 & -4 & -6
\end{pmatrix}\begin{pmatrix}
3 \\
3 \\
0
\end{pmatrix} = \begin{pmatrix}
0 \\
0 \\
0
\end{pmatrix} = \vec{x}_{3} - \text{корневой вектор глубины} \ 0
\end{gather}$$

Тогда корневые подпространства оператора $X$ соответствующие собственному значению $\lambda_{1,2,3} = -3$ будут иметь вид:

$$\begin{align}
&k = 0: \begin{pmatrix}
0 \\
0 \\
0
\end{pmatrix} \\
&k = 1: C_{1}\begin{pmatrix}
1 \\
1 \\
0
\end{pmatrix} \ (\text{собств. подпр-во}) \\\end{align}$$

$$\begin{align}
&k = 2: C_{1}\begin{pmatrix}
1 \\
1 \\
0
\end{pmatrix} + C_{2}\begin{pmatrix}
1 \\
10 \\
-6
\end{pmatrix} \\
&k = 3: C_{1}\begin{pmatrix}
1 \\
1 \\
0
\end{pmatrix} + C_{2}\begin{pmatrix}
1 \\
10 \\
-6
\end{pmatrix} + C_{3}\begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix}
\end{align}$$

### 3.

Воспользуемся найденными в п. 2 корневыми векторами:

$$\begin{gather}
B = \left\langle \begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix},\begin{pmatrix}
1 \\
10 \\
-6
\end{pmatrix},\begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix} \right\rangle \\
C_{E\to B}\Lambda C_{B\to E} = C_{E\to B}\Lambda C_{E\to B}^{-1} = \\\end{gather}$$

$$\begin{gather}
= \begin{pmatrix}
1 & 1 & 1 \\
1 & 10 & 1 \\
0 & -6 & 1
\end{pmatrix}\begin{pmatrix}
-3 & 1 & 0 \\
0 & -3 & 1 \\
0 & 0 & -3
\end{pmatrix}\begin{pmatrix}
1 & 1 & 1 \\
1 & 10 & 1 \\
0 & -6 & 1
\end{pmatrix}^{-1} = \\
= \frac{1}{9}\begin{pmatrix}
1 & 1 & 1 \\
1 & 10 & 1 \\
0 & -6 & 1
\end{pmatrix}\begin{pmatrix}
-3 & 1 & 0 \\
0 & -3 & 1 \\
0 & 0 & -3
\end{pmatrix}\begin{pmatrix}
16 & -7 & -9 \\
-1 & 1 & 0 \\
-6 & 6 & 9
\end{pmatrix}
\end{gather}$$

### 4.

$$\begin{gather}
\mathcal{M}_{X}(x) = (x+3)^{3} \\
(X+3)^{3} = 0 \\
(X+3)(X^{2}+6X+9) = 0 \\\end{gather}$$

$$\begin{gather}
X^{3}+9X^{2}+27X+27I = 0 \Large| \normalsize \cdot X^{-1} \\
X^{2}+9X+27I+27X^{-1} = 0 \\
X^{-1} = -\frac{1}{27}X^{2} - \frac{1}{3}X - I \\\end{gather}$$

$$\begin{gather}
X^{-1} = -\frac{1}{27}\begin{pmatrix}
-4 & 1 & 1 \\
-7 & 4 & 10 \\
4 & -4 & -9
\end{pmatrix}^{2} - \frac{1}{3}\begin{pmatrix}
-4 & 1 & 1 \\
-7 & 4 & 10 \\
4 & -4 & -9
\end{pmatrix}-\begin{pmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{pmatrix} = \\
= \frac{1}{27}\begin{pmatrix}
-4 & -5 & -6 \\
23 & -32 & -33 \\
-12 & 12 & 9
\end{pmatrix}
\end{gather}$$

### 5.

$$\begin{gather}
X^{n} = CJ_{X}^{n}C^{-1} = \\
= \frac{1}{9}\begin{pmatrix}
1 & 1 & 1 \\
1 & 10 & 1 \\
0 & -6 & 1
\end{pmatrix}\begin{pmatrix}
-3 & 1 & 0 \\
0 & -3 & 1 \\
0 & 0 & -3
\end{pmatrix}^{n}\begin{pmatrix}
16 & -7 & -9 \\
-1 & 1 & 0 \\
-6 & 6 & 9
\end{pmatrix} = \\\end{gather}$$

$$\begin{gather}
= \frac{1}{9}\begin{pmatrix}
1 & 1 & 1 \\
1 & 10 & 1 \\
0 & -6 & 1
\end{pmatrix}\begin{pmatrix}
(-3)^{n} & n(-3)^{n-1} & \sum_{i=0}^{n-1}(-3)^{n-2} \\
0 & (-3)^{n} & n(-3)^{n-1} \\
0 & 0 & (-3)^{n}
\end{pmatrix}\begin{pmatrix}
16 & -7 & -9 \\
-1 & 1 & 0 \\
-6 & 6 & 9
\end{pmatrix}
\end{gather}$$

## $Y$:

### 1.

Для матрицы $Y$ воспользуемся формулой для нахождения характеристического многочлена матрицы $3\times 3$.

$$\begin{gather}
\mathcal{X}_{Y} = -\lambda^{3} + \mathrm{tr}(Y)\lambda^{2} - \lambda\left(\sum_{i=1}^{3} M_{ij}\right) + \det Y \\
\det Y = \begin{vmatrix}
7 & -5 \\
8 & -5
\end{vmatrix} + \begin{vmatrix}
3 & -3 \\
8 & -5
\end{vmatrix} - 2\begin{vmatrix}
3 & -3 \\
7 & -5
\end{vmatrix} = \\\end{gather}$$

$$\begin{gather}
= (-35+40) + (-15+24) - 2(-15+21) = 5 + 9 -2\cdot 6 = 14 - 12 = 2 \\
\mathcal{X}_{Y} = -\lambda^{3} + 3\lambda^{2} - 2(5-9+6)\lambda + 2 = \\
= -\lambda^{3}+3\lambda^{2}-4\lambda+2
\end{gather}$$

$$\begin{gather}
\mathcal{X}_{Y}(x) = \mathcal{M}_{Y}(x) = -x^{3}+3x^{2}-4x+2 = \\
= (1-x)(x^{2}-2x+2) = (1-x)(x-1+i)(x-1-i)
\end{gather}$$

### 2.

### $\lambda_{1} = 1$:

$$\begin{gather}
(A - \lambda I)\vec{x}_{k-1} = \vec{x}_{k}, \ \vec{x}_{0} = \begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix}- \text{корневой вектор глубины 1} \  \\
\begin{pmatrix}
0 & 3 & -3 \\
-1 & 6 & -5 \\
-2 & 8 & -6
\end{pmatrix}\begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix} = \begin{pmatrix}
0 \\
0 \\
0
\end{pmatrix} - \text{корневой вектор глубины} \ 0
\end{gather}$$

Корневые подпространства оператора $Y$ при $\lambda_{1} = 1$:

$$\begin{align}
&k = 0: \begin{pmatrix}
0 \\
0 \\
0
\end{pmatrix} \\ \\
&k = 1: C_{1}\begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix} \ (\text{собств. подпр-во})
\end{align}$$

### $\lambda_{2} = 1-i$

$$\begin{gather}
(A - \lambda I)\vec{x}_{k-1} = \vec{x}_{k}, \ \vec{x}_{0} = \begin{pmatrix}
6-3i \\
9-2i \\
10
\end{pmatrix} - \text{корневой вектор глубины} \ 1 \\
\begin{pmatrix}
i & 3 & -3 \\
-1 & 6+i & -5 \\
-2 & 8 & -6+i
\end{pmatrix}\begin{pmatrix}
6-3i \\
9-2i \\
10
\end{pmatrix} = \begin{pmatrix}
0 \\
0 \\
0
\end{pmatrix} - \text{корневой вектор глубины} \ 0 
\end{gather}$$

Корневые подпространства оператора $Y$ при $\lambda_{2} = 1-i$:

$$\begin{align}
&k = 0: \begin{pmatrix}
0 \\
0 \\
0
\end{pmatrix} \\ \\
&k = 1: C_{1}\begin{pmatrix}
6-3i \\
9-2i \\
10
\end{pmatrix} \ (\text{собств. подпр-во})
\end{align}$$

### $\lambda_{3} = 1+i$

$$\begin{gather}
(A - \lambda I)\vec{x}_{k-1} = \vec{x}_{k}, \ \vec{x}_{0} = \begin{pmatrix}
6+3i \\
9+2i \\
10
\end{pmatrix} - \text{корневой вектор глубины} \ 1 \\
\begin{pmatrix}
-i & 3 & -3 \\
-1 & 6-i & -5 \\
-2 & 8 & -6-i
\end{pmatrix}\begin{pmatrix}
6+3i \\
9+2i \\
10
\end{pmatrix} = \begin{pmatrix}
0 \\
0 \\
0
\end{pmatrix} - \text{корневой вектор глубины} \ 0
\end{gather}$$

Корневые подпространства оператора $Y$ при $\lambda_{3} = 1+i$:

$$\begin{align}
&k = 0: \begin{pmatrix}
0 \\
0 \\
0
\end{pmatrix} \\ \\
&k = 1: C_{1}\begin{pmatrix}
6+3i \\
9+2i \\
10
\end{pmatrix} \ (\text{собств. подпр-во})
\end{align}$$

### 3.

Сопряженные комплексные собственные значения $\lambda_{2,3} = 1\pm i$ образуют матрицу умножения на комплексное число $\begin{pmatrix} 1 & 1 \\ -1 & 1\end{pmatrix}$. Чтобы получить базис, в котором матрица будет приводится к блочно-диагональному виду, возьмем действительную и мнимую часть от полученных собственных векторов и соберем из них векторы нового базиса.

$$\begin{gather}
B = \left\langle \begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix},\begin{pmatrix}
6 \\
9 \\
10
\end{pmatrix},\begin{pmatrix}
3 \\
2 \\
0
\end{pmatrix} \right\rangle \\\end{gather}$$

$$\begin{gather}
\begin{pmatrix}
1 & 6 & 3 \\
1 & 9 & 2 \\
1 & 10 & 0
\end{pmatrix}\begin{pmatrix}
1 & 0 & 0 \\
0 & 1 & 1 \\
0 & -1 & 1
\end{pmatrix}\begin{pmatrix}
1 & 6 & 3 \\
1 & 9 & 2 \\
1 & 10 & 0
\end{pmatrix}^{-1} = \\
= \frac{1}{5}\begin{pmatrix}
1 & 6 & 3 \\
1 & 9 & 2 \\
1 & 10 & 0
\end{pmatrix}\begin{pmatrix}
1 & 0 & 0 \\
0 & 1 & 1 \\
0 & -1 & 1
\end{pmatrix}\begin{pmatrix}
20 & -30 & 15 \\
-2 & 3 & -1 \\
-1 & 4 & -3
\end{pmatrix}
\end{gather}$$

### 4.

$$\begin{gather}
\mathcal{M}_{Y}(x) = x^{3}+3x^{2}-4x+2 \\
Y^{3}+3Y^{2}-4Y+2I = 0 \Large| \normalsize \cdot Y^{-1} \\
Y^{2} + 3Y -4I +2Y^{-1} = 0 \\
Y^{-1} = -\frac{1}{2}Y^{2}-\frac{3}{2}Y+2I \\\end{gather}$$

$$\begin{gather}
Y^{-1} = -\frac{1}{2}\begin{pmatrix}
1 & 3 & -3 \\
-1 & 7 & -5 \\
-2 & 8 & -5
\end{pmatrix}^{2}-\frac{3}{2}\begin{pmatrix}
1 & 3 & -3 \\
-1 & 7 & -5 \\
-2 & 8 & -5
\end{pmatrix}+2\begin{pmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{pmatrix} = \\
= \frac{1}{2}\begin{pmatrix}
-3 & -9 & 12 \\
1 & -23 & 22 \\
6 & -34 & 28
\end{pmatrix}
\end{gather}$$

### 5.

$$\begin{gather}
Y^{n} = CJ_{Y}^{n}C^{-1} = \\
\frac{1}{5}\begin{pmatrix}
1 & 6 & 3 \\
1 & 9 & 2 \\
1 & 10 & 0
\end{pmatrix}\begin{pmatrix}
1 & 0 & 0 \\
0 & 1 & 1 \\
0 & -1 & 1
\end{pmatrix}^{n}\begin{pmatrix}
20 & -30 & 15 \\
-2 & 3 & -1 \\
-1 & 4 & -3
\end{pmatrix} = \\
\frac{1}{5}\begin{pmatrix}
1 & 6 & 3 \\
1 & 9 & 2 \\
1 & 10 & 0
\end{pmatrix}\begin{pmatrix}
1 & 0 & 0 \\
0 & \sqrt{ 2 }\cos \frac{\pi n}{4} & \sqrt{ 2 }\sin \frac{\pi n}{4} \\
0 & -\sqrt{ 2 }\sin \frac{\pi n}{4} & \sqrt{ 2 }\cos \frac{\pi n}{4} \\
\end{pmatrix}\begin{pmatrix}
20 & -30 & 15 \\
-2 & 3 & -1 \\
-1 & 4 & -3
\end{pmatrix}
\end{gather}$$

## $Z$:

### 1.

$$\begin{gather}
\mathcal{X}_{Z} = \begin{vmatrix}
2-\lambda & 1 & 0 \\
0 & 3-\lambda & 0 \\
0 & 0 & 3-\lambda
\end{vmatrix} = (2-\lambda)(3-\lambda)^{2}
\end{gather}$$

$$\begin{gather}
\mathcal{X}_{Z}(x) = (2-x)(3-x)^{2} \\
\mathcal{M}_{Z}(x) = (2-x)(3-x) \\
\begin{pmatrix}
0 & 1 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{pmatrix}\begin{pmatrix}
-1 & 1 & 0 \\
0 & 0 & 0 \\
0 & 0 & 0
\end{pmatrix} = \begin{pmatrix}
0 & 0 & 0 \\
0 & 0 & 0 \\
0 & 0 & 0
\end{pmatrix}
\end{gather}$$

### 2.

### $\lambda_{1} = 2$

$$\begin{gather}
(A - \lambda I)\vec{x}_{k-1} = \vec{x}_{k}, \ \vec{x}_{0} = \begin{pmatrix}
1 \\
0 \\
0
\end{pmatrix} - \text{корневой вектор глубины} \ 1 \\
\begin{pmatrix}
0 & 1 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{pmatrix}\begin{pmatrix}
1 \\
0 \\
0
\end{pmatrix} = \begin{pmatrix}
0 \\
0 \\
0
\end{pmatrix} - \text{корневой вектор глубины} \ 0
\end{gather}$$

Корневые подпространства оператора $Z$ при $\lambda_{1} = 2$:

$$\begin{align}
&k = 0: \begin{pmatrix}
0 \\
0 \\
0
\end{pmatrix} \\
&k = 1: C_{1}\begin{pmatrix}
1 \\
0 \\
0
\end{pmatrix} \ (\text{собств. подпр-во})
\end{align}$$

### $\lambda_{2,3} = 3$

$$\begin{gather}
(A - \lambda I)\vec{x}_{k-1} = \vec{x}_{k}, \ \vec{x}_{0} = \begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix}, \ \vec{x}_{0,2} = \begin{pmatrix}
1 \\
1 \\
0
\end{pmatrix}  - \text{корневые векторы глубины} \ 1 \\
\begin{pmatrix}
-1 & 1 & 0 \\
0 & 0 & 0 \\
0 & 0 & 0
\end{pmatrix}\begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix} = \begin{pmatrix}
-1 & 1 & 0 \\
0 & 0 & 0 \\
0 & 0 & 0
\end{pmatrix}\begin{pmatrix}
1 \\
1 \\
0
\end{pmatrix} = \begin{pmatrix}
0 \\
0 \\
0
\end{pmatrix} - \text{корневой вектор глубины} \ 0
\end{gather}$$

Корневые подпространства оператора $Z$ при $\lambda_{2,3} = 3$:

$$\begin{align}
&k = 0: \begin{pmatrix}
0 \\
0 \\
0
\end{pmatrix} \\
&k = 1: C_{1}\begin{pmatrix}
1 \\
1 \\
0
\end{pmatrix} + C_{2}\begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix} \ (\text{собств. подпр-во})
\end{align}$$

### 3.

$$\begin{gather}
B = \left\langle \begin{pmatrix}
1 \\
0 \\
0
\end{pmatrix},\begin{pmatrix}
1 \\
1 \\
0
\end{pmatrix}\begin{pmatrix}
1 \\
1 \\
1
\end{pmatrix} \right\rangle \\\end{gather}$$

$$\begin{gather}
\begin{pmatrix}
1 & 1 & 1 \\
0 & 1 & 1 \\
0 & 0 & 1
\end{pmatrix}\begin{pmatrix}
2 & 0 & 0 \\
0 & 3 & 1 \\
0 & 0 & 3
\end{pmatrix}\begin{pmatrix}
1 & 1 & 1 \\
0 & 1 & 1 \\
0 & 0 & 1
\end{pmatrix}^{-1} = \\
= \begin{pmatrix}
1 & 1 & 1 \\
0 & 1 & 1 \\
0 & 0 & 1
\end{pmatrix}\begin{pmatrix}
2 & 0 & 0 \\
0 & 3 & 1 \\
0 & 0 & 3
\end{pmatrix}\begin{pmatrix}
1 & -1 & 0 \\
0 & 1 & -1 \\
0 & 0 & 1
\end{pmatrix}
\end{gather}$$

### 4.

$$\begin{gather}
\mathcal{M}_{Z}(x) = (x-2)(x-3) = x^{2}-5x+6 \\
Z^{2}-5Z+6I = 0 \Large| \normalsize \cdot Z^{-1} \\
Z - 5I + 6Z^{-1} = 0 \\
Z^{-1} = -\frac{1}{6}Z + \frac{5}{6}I \\\end{gather}$$

$$\begin{gather}
Z^{-1} = -\frac{1}{6}\begin{pmatrix}
2 & 1 & 0 \\
0 & 3 & 0 \\
0 & 0 & 3
\end{pmatrix} + \frac{5}{6}\begin{pmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{pmatrix} = \\
= \frac{1}{6}\begin{pmatrix}
3 & -1 & 0 \\
0 & 2 & 0 \\
0 & 0 & 2
\end{pmatrix}
\end{gather}$$

### 5.

$$\begin{gather}
Z^{n} = CJ_{Z}^{n}C^{-1} = \\
= \begin{pmatrix}
1 & 1 & 1 \\
0 & 1 & 1 \\
0 & 0 & 1
\end{pmatrix}\begin{pmatrix}
2 & 0 & 0 \\
0 & 3 & 1 \\
0 & 0 & 3
\end{pmatrix}^{n}\begin{pmatrix}
1 & -1 & 0 \\
0 & 1 & -1 \\
0 & 0 & 1
\end{pmatrix} = \\
= \begin{pmatrix}
1 & 1 & 1 \\
0 & 1 & 1 \\
0 & 0 & 1
\end{pmatrix}\begin{pmatrix}
2^{n} & 0 & 0 \\
0 & 3^{n} & n\cdot3^{n-1} \\
0 & 0 & 3^{n}
\end{pmatrix}\begin{pmatrix}
1 & -1 & 0 \\
0 & 1 & -1 \\
0 & 0 & 1
\end{pmatrix}
\end{gather}$$

## ТР 6

$$\begin{gather}
b_{ij} = b(\vec{e}_{i},\vec{e}_{j}), \ \begin{array}{|c|c|}
\hline i \setminus j & 1 & 2 & 3 \\
\hline 1 & 2 & -1 & -1 \\
\hline 2 & -3 & 9 & 4 \\
\hline 3 & 1 & 0 & 2 \\
\hline
\end{array}
\end{gather}$$

### 1.

$$\begin{gather}
b(\vec{x},\vec{y}) = 2x_{1}y_{1}-x_{1}y_{2}-x_{1}y_{3}-3x_{2}y_{1}+9x_{2}y_{2}+4x_{2}y_{3}+x_{1}y_{3}+2x_{3}y_{3} \\
b(\vec{x},\vec{y}) = \begin{pmatrix}
x_{1} & x_{2} & x_{3}
\end{pmatrix}\begin{pmatrix}
2 & -1 & -1 \\
-3 & 9 & 4 \\
1 & 0 & 2
\end{pmatrix}\begin{pmatrix}
y_{1} \\
y_{2} \\
y_{3}
\end{pmatrix}
\end{gather}$$

### 2.

$$\begin{gather}
k(\vec{x}) = 2x_{1}x_{1}-x_{1}x_{2}-x_{1}x_{3}-3x_{2}x_{1}+9x_{2}x_{2}+4x_{2}x_{3}+x_{1}x_{3}+2x_{3}x_{3} = \\
= 2x_{1}^{2}+9x_{2}^{2}+2x_{3}^{2}-4x_{1}x_{2}+4x_{2}x_{3} \\\end{gather}$$

$$\begin{gather}
k(\vec{x}) = \begin{pmatrix}
x_{1} & x_{2} & x_{3}
\end{pmatrix}\begin{pmatrix}
2 & -2 & 0 \\
-2 & 9 & 2 \\
0 & 2 & 2
\end{pmatrix}\begin{pmatrix}
x_{1} \\
x_{2} \\
x_{3}
\end{pmatrix}
\end{gather}$$

### 3.

$$\begin{gather}
k(\vec{x}) = 2(x_{1}^{2} - 2x_{1}x_{2}) + 2(x_{3}^{2} + 2x_{2}x_{3}) + 9x^{2} = \\
= 2(x_{1}^{2} - 2x_{1}x_{2} + x_{2}^{2}) - 2x_{2}^{2} + 2(x_{3}^{2} + 2x_{2}x_{3} + x_{2}^{2}) - 2x_{2}^{2} + 9x_{2}^{2} = \\
= 2\underbrace{(x_{1}-x_{2})^{2}}_{y_{1}^{2}} + 2\underbrace{(x_{2}+x_{3})^{2}}_{y_{2}^{2}} + 5\underbrace{x_{2}^{2}}_{y_{3}^{2}} = 2y_{1}^{2}+2y_{2}^{2}+5y_{3}^{2} \\\end{gather}$$

$$\begin{gather}
\begin{cases}
y_{1} = x_{1}-x_{2} \\
y_{2} = x_{2}+x_{3} \\
y_{3} = x_{2}
\end{cases} \\\end{gather}$$

$$\begin{gather}
\vec{y} = \begin{pmatrix}
1 & -1 & 0 \\
0 & 1 & 1 \\
0 & 1 & 0
\end{pmatrix}\vec{x} \\
\vec{y}^{T} = \vec{x^{T}}\begin{pmatrix}
1 & 0 & 0 \\
-1 & 1 & 1 \\
0 & 1 & 0
\end{pmatrix}
\end{gather}$$

$$\begin{gather}
p(\vec{y}) = \vec{y}^{T}\begin{pmatrix}
2 & 0 & 0 \\
0 & 2 & 0 \\
0 & 0 & 5
\end{pmatrix}\vec{y} \\
p(\vec{x}) = \vec{x}^{T}\begin{pmatrix}
1 & 0 & 0 \\
-1 & 1 & 1 \\
0 & 1 & 0 \\
\end{pmatrix}\begin{pmatrix}
2 & 0 & 0 \\
0 & 2 & 0 \\
0 & 0 & 5
\end{pmatrix}\begin{pmatrix}
1 & -1 & 0 \\
0 & 1 & 1 \\
0 & 1 & 0 \\
\end{pmatrix}\vec{x} \\
\end{gather}$$

$$\begin{align}
&n_{+} = 3 \\
&n_{-} = 0 \\
&n_{0} = 0
\end{align}$$

## ТР 7

$$\vec{e}_{1} = \begin{pmatrix}
1 \\
0 \\
2
\end{pmatrix}, \ \vec{e}_{2} = \begin{pmatrix}
2 \\
1 \\
1
\end{pmatrix}, \ \vec{e}_{3} = \begin{pmatrix}
1 \\
1 \\
0
\end{pmatrix}$$

### а)

$$\begin{gather}
G_{S} = \begin{pmatrix}
(e_{1},e_{1}) & (e_{1},e_{2}) & (e_{1},e_{3}) \\
(e_{2},e_{1}) & (e_{2},e_{2}) & (e_{2},e_{3}) \\
(e_{3},e_{1}) & (e_{3},e_{2}) & (e_{3},e_{3}) \\
\end{pmatrix} = \begin{pmatrix}
5 & 4 & 1 \\
4 & 6 & 3 \\
1 & 3 & 2
\end{pmatrix} \\\end{gather}$$

$$\begin{gather}
|\vec{v}| = \sqrt{ (\vec{v}, \vec{v}) } = \sqrt{ \begin{pmatrix}
x & y & z
\end{pmatrix}\begin{pmatrix}
5 & 4 & 1 \\
4 & 6 & 3 \\
1 & 3 & 2
\end{pmatrix}\begin{pmatrix}
x \\
y \\
z
\end{pmatrix} } = \\
= \sqrt{ 5x^{2} + 6y^{2} + 2z^{2} + 8xy + 2xz + 6yz }
\end{gather}$$

### б)

Для ортогонализации базиса $S$ воспользуемся алгоритмом Грама-Шмидта.

$$\begin{gather}
\vec{a}_{1} = \vec{e}_{1} = \begin{pmatrix}
1 \\
0 \\
2
\end{pmatrix} \\
\vec{p}_{1} = \frac{\vec{a}_{1}}{|\vec{a}_{1}|} = \frac{1}{\sqrt{ 5 }}\begin{pmatrix}
1 \\
0 \\
2
\end{pmatrix} = \frac{\sqrt{ 5 }}{5}\begin{pmatrix}
1 \\
0 \\
2
\end{pmatrix}
\end{gather}$$

$$\begin{gather}
\vec{a}_{2} = \vec{e}_{2} - \mathrm{Proj}_{\vec{a}_{1}} \ \vec{e}_{2} = \vec{e}_{2} -\frac{(\vec{e}_{2}, \vec{a}_{1})}{(\vec{a}_{1},\vec{a}_{1})}\vec{a}_{1} = \\\end{gather}$$

$$\begin{gather}
= \begin{pmatrix}
2 \\
1 \\
1
\end{pmatrix} - \frac{4}{5} \cdot \begin{pmatrix}
1 \\
0 \\
2
\end{pmatrix} = \frac{1}{5}\begin{pmatrix}
6 \\
5 \\
-3
\end{pmatrix} \sim \begin{pmatrix}
6 \\
5 \\
-3
\end{pmatrix} \\
\vec{p}_{2} = \frac{\vec{a}_{2}}{|\vec{a}_{2}|} = \frac{1}{\sqrt{ 70 }}\begin{pmatrix}
6 \\
5 \\
-3
\end{pmatrix} = \frac{\sqrt{ 70 }}{70} \begin{pmatrix}
6 \\
5 \\
-3
\end{pmatrix}
\end{gather}$$

$$\begin{gather}
\vec{a}_{3} = \vec{e}_{3} - \mathrm{Proj}_{\vec{a}_{1}} \ \vec{e}_{2} - \mathrm{Proj}_{\vec{a}_{2}} \ \vec{e}_{3} = \vec{e}_{3} - \frac{(\vec{e}_{3},\vec{a}_{1})}{(\vec{a}_{1}, \vec{a}_{1})}\vec{a_{1}} - \frac{(\vec{e}_{3},\vec{a}_{2})}{(\vec{a}_{2}, \vec{a}_{2})}\vec{a}_{2} = \\\end{gather}$$

$$\begin{gather}
= \begin{pmatrix}
1 \\
1 \\
0
\end{pmatrix} - \frac{1}{5}\begin{pmatrix}
1 \\
0 \\
2
\end{pmatrix} - \frac{11}{70}\begin{pmatrix}
6 \\
5 \\
-3
\end{pmatrix} = \frac{1}{14}\begin{pmatrix}
-2 \\
3 \\
1
\end{pmatrix} \sim \begin{pmatrix}
-2 \\
3 \\
1
\end{pmatrix} \\
\vec{p}_{3} = \frac{\vec{a}_{3}}{|\vec{a}_{3}|} = \frac{\sqrt{ 14 }}{14}\begin{pmatrix}
-2 \\
3 \\
1
\end{pmatrix} \\
\end{gather}$$

$$P = \left\langle \frac{\sqrt{ 5 }}{5}\begin{pmatrix}
1 \\
0 \\
2
\end{pmatrix},
\frac{\sqrt{ 70 }}{70}\begin{pmatrix}
6 \\
5 \\
-3
\end{pmatrix}, \frac{\sqrt{ 14 }}{14}\begin{pmatrix}
-2 \\
3 \\
1
\end{pmatrix} \right\rangle$$

### Проверка ортонормированности

### 1.

$$\begin{gather}
\left( \begin{pmatrix}
1 \\
0 \\
2
\end{pmatrix}, \begin{pmatrix}
6+(-2) \\
5+3 \\
-3+1 \\
\end{pmatrix} \right) = \left( \begin{pmatrix}
1 \\
0 \\
2
\end{pmatrix}, \begin{pmatrix}
4 \\
8 \\
-2
\end{pmatrix} \right) = 4-4 = 0 \\
\left( \begin{pmatrix}
6 \\
5 \\
-3
\end{pmatrix}, \begin{pmatrix}
1+(-2) \\
0+3 \\
2+1
\end{pmatrix} \right) = \left( \begin{pmatrix}
6 \\
5 \\
-3
\end{pmatrix}, \begin{pmatrix}
-1 \\
3 \\
3
\end{pmatrix} \right) = -6+15-9 = 0 \\\end{gather}$$

$$\begin{gather}
\left( \begin{pmatrix}
-2 \\
3 \\
1
\end{pmatrix}, \begin{pmatrix}
1+6 \\
0+5 \\
2-3
\end{pmatrix} \right) = \left( \begin{pmatrix}
-2 \\
3 \\
1
\end{pmatrix}, \begin{pmatrix}
7 \\
5 \\
-1
\end{pmatrix} \right) = -14+15-1 = 0
\end{gather}$$

$$PP^{T} = \begin{pmatrix}
\frac{\sqrt{ 5 }}{5} & \frac{6\sqrt{ 70 }}{70} & -\frac{2\sqrt{ 14 }}{14} \\
0 & \frac{5\sqrt{ 70 }}{70} & \frac{3\sqrt{ 14 }}{14} \\
\frac{2\sqrt{ 5 }}{5} & -\frac{3\sqrt{ 70 }}{70} & \frac{\sqrt{ 14 }}{14}
\end{pmatrix}\begin{pmatrix}
\frac{\sqrt{ 5 }}{5} & 0 & \frac{2\sqrt{ 5 }}{5} \\
\frac{6\sqrt{ 70 }}{70} & \frac{5\sqrt{ 70 }}{70} & -\frac{3\sqrt{ 70 }}{70} \\
-\frac{2\sqrt{ 14 }}{14} & \frac{3\sqrt{ 14 }}{14} & \frac{\sqrt{ 14 }}{14}
\end{pmatrix} = \begin{pmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{pmatrix}$$

### 2.

$$C = \left( P^{-1}S \right)^{-1}, \ \text{но можно проще}$$

$$\begin{gather}
\vec{p}_{1} = \frac{\sqrt{ 5 }}{5}\vec{e}_{1} \\
\vec{p}_{2} = \frac{\sqrt{ 70 }}{70}(-4\vec{e}_{1} + 5\vec{e}_{2}) \\
\vec{p}_{3} = \frac{\sqrt{ 14 }}{14}(6\vec{e}_{1} - 11\vec{e}_{2} + 14\vec{e}_{3})
\end{gather}$$

$$\begin{gather}
C = \begin{pmatrix}
\frac{\sqrt{ 5 }}{5} & -\frac{2\sqrt{ 70 }}{35} & \frac{3\sqrt{ 14 }}{7} \\
0 & \frac{\sqrt{ 70 }}{14} & -\frac{11\sqrt{ 14 }}{14} \\
0 & 0 & \sqrt{ 14 }
\end{pmatrix}
\end{gather}$$

$$\begin{gather}
C^{T}G_{S}C = \begin{pmatrix}
\frac{\sqrt{ 5 }}{5} & 0 & 0 \\
-\frac{2\sqrt{ 70 }}{35} & \frac{\sqrt{ 70 }}{14} & 0 \\
\frac{3\sqrt{ 14 }}{7} & -\frac{11\sqrt{ 14 }}{14} & \sqrt{ 14 }
\end{pmatrix}\begin{pmatrix}
5 & 4 & 1 \\
4 & 6 & 3 \\
1 & 3 & 2
\end{pmatrix}\begin{pmatrix}
\frac{\sqrt{ 5 }}{5} & -\frac{2\sqrt{ 70 }}{35} & \frac{3\sqrt{ 14 }}{7} \\
0 & \frac{\sqrt{ 70 }}{14} & -\frac{11\sqrt{ 14 }}{14} \\
0 & 0 & \sqrt{ 14 }
\end{pmatrix} = \\\end{gather}$$

$$\begin{gather}
= \begin{pmatrix}
\sqrt{ 5 } & \frac{4\sqrt{ 5 }}{5} & \frac{\sqrt{ 5 }}{5} \\
0 & \frac{\sqrt{ 70 }}{5} & \frac{11\sqrt{ 70 }}{70} \\
0 & 0 & \frac{\sqrt{ 14 }}{14}
\end{pmatrix}\begin{pmatrix}
\frac{\sqrt{ 5 }}{5} & -\frac{2\sqrt{ 70 }}{35} & \frac{3\sqrt{ 14 }}{7} \\
0 & \frac{\sqrt{ 70 }}{14} & -\frac{11\sqrt{ 14 }}{14} \\
0 & 0 & \sqrt{ 14 }
\end{pmatrix} = \begin{pmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{pmatrix}
\end{gather}$$

## ТР 8

$$\begin{gather}
[-2; -1], \ B = \langle t^{2} ; t; 1 \rangle, \ (p(t),q(t)) = \int_{-2}^{-1} p(t)q(t) \, dt 
\end{gather}$$

### 1. Ортогонализация

$$\begin{gather}
(1,1) = \int_{-2}^{-1} dt = 1 \\
(t, 1) = (1, t) = \int_{-2}^{-1} t \, dt = \frac{1}{2} - 2 = -\frac{3}{2} \\
(1, t^{2}) = (t^{2}, 1) = \int_{-2}^{-1} t^{2} \, dt = -\frac{1}{3} + \frac{8}{3} = \frac{7}{3} \\
\end{gather}$$

$$\begin{gather}
(t, t) = \int_{-2}^{-1} t^{2}  \, dt = (1, t^{2}) = \frac{7}{3} \\
(t, t^{2}) = (t^{2}, t) = \int_{-2}^{-1} t^{3} \, dt = \frac{1}{4} - 4 = -\frac{15}{4} \\
(t^{2}, t^{2}) = \int_{-2}^{-1} t^{4} \, dt = -\frac{1}{5} + \frac{32}{5} = \frac{31}{5}
\end{gather}$$

$$G = \begin{pmatrix}
1 & -\frac{3}{2} & \frac{7}{3} \\
-\frac{3}{2} & \frac{7}{3} & -\frac{15}{4} \\
\frac{7}{3} & -\frac{15}{4} & \frac{31}{5}
\end{pmatrix}$$

$$s_{1} = e_{1} = \begin{pmatrix}
1 \\
0 \\
0
\end{pmatrix} = 1$$

$$\begin{gather}
s_{2} = e_{2} - \mathrm{Proj}_{s_{1}}e_{2} = e_{2} - \frac{(e_{2}, s_{1})}{(s_{1},s_{1})}e_{1} = \\
= \begin{pmatrix}
0 \\
1 \\
0
\end{pmatrix} - \frac{-\frac{3}{2}}{1}\begin{pmatrix}
1 \\
0 \\
0
\end{pmatrix} = \begin{pmatrix}
\frac{3}{2} \\
1 \\
0
\end{pmatrix} = t+\frac{3}{2}
\end{gather}$$

$$\begin{gather}
s_{3} = e_{3} - \mathrm{Proj}_{s_{1}}e_{3} - \mathrm{Proj}_{s_{2}}e_{3} = \\
= \begin{pmatrix}
0 \\
0 \\
1
\end{pmatrix} - \frac{7}{3}\begin{pmatrix}
1 \\
0 \\
0
\end{pmatrix} \underbrace{- \frac{-\frac{1}{4}}{\frac{1}{12}}}_{+3}\begin{pmatrix}
\frac{3}{2} \\
1 \\
0
\end{pmatrix} = \begin{pmatrix}
\frac{13}{6} \\
3 \\
1
\end{pmatrix} = t^{2} +3t+\frac{13}{6}
\end{gather}$$

$$\begin{pmatrix}
0 & 0 & 1
\end{pmatrix}\begin{pmatrix}
1 & -\frac{3}{2} & \frac{7}{3} \\
-\frac{3}{2} & \frac{7}{3} & -\frac{15}{4} \\
\frac{7}{3} & -\frac{15}{4} & \frac{31}{5}
\end{pmatrix}\begin{pmatrix}
\frac{3}{2} \\
1 \\
0
\end{pmatrix} = -\frac{1}{4}$$

$$\begin{pmatrix}
\frac{3}{2} & 1 & 0
\end{pmatrix}\begin{pmatrix}
1 & -\frac{3}{2} & \frac{7}{3} \\
-\frac{3}{2} & \frac{7}{3} & -\frac{15}{4} \\
\frac{7}{3} & -\frac{15}{4} & \frac{31}{5}
\end{pmatrix}\begin{pmatrix}
\frac{3}{2} \\
1 \\
0
\end{pmatrix} = \frac{1}{12}$$

$$S = \left\langle 1; t+\frac{3}{2}; t^{2}+3t+\frac{13}{6} \right\rangle$$

### 2. Ортонормирование

$$\begin{gather}
|\vec{v}| = \sqrt{ \begin{pmatrix}
x & y & z
\end{pmatrix}\begin{pmatrix}
1 & -\frac{3}{2} & \frac{7}{3} \\
-\frac{3}{2} & \frac{7}{3} & -\frac{15}{4} \\
\frac{7}{3} & -\frac{15}{4} & \frac{31}{5}
\end{pmatrix}\begin{pmatrix}
x \\
y \\
z
\end{pmatrix} } = \\
= \sqrt{ x^{2}+\frac{7}{3}y^{2}+\frac{31}{5}z^{2}-3xy+\frac{14}{3}xz-\frac{15}{2}yz }
\end{gather}$$

$$1) \ \left(\begin{pmatrix}
1 \\
0 \\
0
\end{pmatrix},\begin{pmatrix}
1 \\
0 \\
0
\end{pmatrix}\right) = 1 \implies p_{1} = a_{1} = \begin{pmatrix}
1 \\
0 \\
0
\end{pmatrix}$$
$$\begin{gather}
2) \ p_{2} = \frac{a_{2}}{|a_{2}|} \\
|a_{2}| = \sqrt{ \left( \frac{3}{2} \right)^{2}+\frac{7}{3}\cdot 1^{2} - 3\cdot 1\cdot \frac{3}{2} } = \frac{\sqrt{ 3 }}{6} \implies \\
\implies p_{2} = \frac{6}{\sqrt{ 3 }}\begin{pmatrix}
\frac{3}{2} \\
1 \\
0
\end{pmatrix} = \begin{pmatrix}
\frac{3\sqrt{ 3 }}{4} \\
\frac{\sqrt{ 3 }}{2} \\
0
\end{pmatrix}
\end{gather}$$

$$\begin{gather}
3) \ p_{3} = \frac{a_{3}}{|a_{3}|} \\
|a_{3}| = \sqrt{ \left( \frac{13}{6} \right)^{2} + \frac{6}{3} \cdot 3^{2} + \frac{31}{5} - 3 \cdot \frac{13}{6} \cdot 3 + \frac{14}{3} \cdot \frac{13}{6} - \frac{15}{2} \cdot 3 } = \\\end{gather}$$

$$\begin{gather}
= \sqrt{ \frac{1}{180} } = \frac{1}{6\sqrt{ 5 }} \\
p_{3} = 6\sqrt{ 5 }\begin{pmatrix}
\frac{13}{6} \\
3 \\
1
\end{pmatrix} = \begin{pmatrix}
13\sqrt{ 5 } \\
18\sqrt{ 5 } \\
6\sqrt{ 5 }
\end{pmatrix}
\end{gather}$$

$$P = \left\langle 1; \frac{\sqrt{ 3 }}{2}t+\frac{3\sqrt{ 3 }}{4}; 6\sqrt{ 5 }t^{2}+18\sqrt{ 5 }t+13\sqrt{ 5 } \right\rangle$$

## ТР 9

$$k(\vec{x}) = \vec{x}^{T}\begin{pmatrix}
2 & -2 & 0 \\
-2 & 9 & 2 \\
0 & 2 & 2
\end{pmatrix}\vec{x}$$

$$\begin{gather}
\mathcal{X}_{K}(\lambda) = -\lambda^{3} + \mathrm{tr}(K)\lambda^{2} - \lambda\left(\sum_{i,j=1}^{3} M_{ij}\right) + \det K = \\\end{gather}$$

$$\begin{gather}
= -\lambda^{3} + 13\lambda^{2} - \lambda(14+4+14) + 14 \cdot 2 + (-2) \cdot 4 + 0 \cdot (-4) = \\
= -\lambda^{3} + 13\lambda^{2} - 32\lambda + 20 = -(\lambda-1)(\lambda-2)(\lambda-10)
\end{gather}$$

### $\lambda_{1} = 1$:

$$\begin{gather}
\begin{pmatrix}
1 & -2 & 0 \\
-2 & 8 & 2 \\
0 & 2 & 1
\end{pmatrix}\begin{pmatrix}
2 \\
1 \\
-2
\end{pmatrix} = \vec{0} \implies \vec{x}_{1} = \begin{pmatrix}
2 \\
1 \\
-2
\end{pmatrix}, \ |\vec{x}_{1}| = 3
\end{gather}$$

### $\lambda_{2} = 2$:

$$\begin{gather}
\begin{pmatrix}
0 & -2 & 0 \\
-2 & 7 & 2 \\
0 & 2 & 0
\end{pmatrix}\begin{pmatrix}
1 \\
0 \\
1
\end{pmatrix} = \vec{0} \implies \vec{x}_{2} = \begin{pmatrix}
1 \\
0 \\
1
\end{pmatrix}, \ |\vec{x}_{2}| = \sqrt{ 2 }
\end{gather}$$

### $\lambda_{3} = 10$:

$$\begin{gather}
\begin{pmatrix}
-8 & -2 & 0 \\
-2 & -1 & 2 \\
0 & 2 & -8
\end{pmatrix}\begin{pmatrix}
1 \\
-4 \\
-1
\end{pmatrix} = \vec{0} \implies \vec{x}_{3} = \begin{pmatrix}
1 \\
-4 \\
-1
\end{pmatrix}, \ |\vec{x}_{3}| = 3\sqrt{ 2 }
\end{gather}$$

Тогда канонический вид квадратичной формы $k$ и ее матрица ортогонального преобразования координат $P$ имеют вид:

$$\begin{gather}
k(\vec{y}) = \vec{y}^{T}\begin{pmatrix}
1 & 0 & 0 \\
0 & 2 & 0 \\
0 & 0 & 10
\end{pmatrix} \vec{y}, \ P = \begin{pmatrix}
\frac{2}{3} & \frac{\sqrt{ 2 }}{2} & \frac{\sqrt{ 2 }}{6} \\
\frac{1}{3} & 0 & -\frac{2\sqrt{ 2 }}{3} \\
-\frac{2}{3} & \frac{\sqrt{ 2 }}{2} & -\frac{\sqrt{ 2 }}{6}
\end{pmatrix}
\end{gather}$$

$$\begin{gather}
k(\vec{y}) = \alpha \iff y_{1}^{2}+2y_{2}^{2}+10y_{3}^{2} = \alpha - \\
- \text{элипсоид}
\end{gather}$$

![[ТР 9 Линейная алгебра 2024-06-02 17.38.04.excalidraw]]