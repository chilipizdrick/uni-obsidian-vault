Нахождение корневых подпространств эквивалентно нахождению всех решений системы $(A - \lambda I)^{k}\vec{x} = \vec{0}$, где $k \in 1,2,\dots, \mathrm{ord}(\lambda)$.

### $X (\lambda = -3):$

$$\begin{gather}
(A - \lambda I)\vec{x} = \begin{pmatrix}
-1 & 1 & 1 \\
-7 & 7 & 10 \\
4 & -4 & -6
\end{pmatrix}\vec{x} = \vec{0} \\
\left(\begin{array}{ccc|c}
-1 & 1 & 1 & 0 \\
-7 & 7 & 10 & 0 \\
4 & -4 & -6 & 0
\end{array}\right) \sim \left(\begin{array}{ccc|c}
-1 & 1 & 1 & 0 \\
-7 & 7 & 10 & 0 \\
-4 & 4 & 6 & 0
\end{array}\right) \sim \left(\begin{array}{ccc|c}
-1 & 1 & 1 & 0 \\
0 & 0 & 3 & 0 \\
0 & 0 & 2 & 0
\end{array}\right) \implies \\
\implies \vec{x}_{1} = C\begin{pmatrix}
1 \\
-1 \\
0
\end{pmatrix} - \text{корневое подпространство глубины} \ 1
\end{gather}$$

$$\begin{gather}
(A - \lambda I)^{2}\vec{x} = \begin{pmatrix}
-1 & 1 & 1 \\
-7 & 7 & 10 \\
4 & -4 & -6
\end{pmatrix}^{2}\vec{x} = \begin{pmatrix}
-2 & 2 & 3 \\
-2 & 2 & 3 \\
0 & 0 & 0
\end{pmatrix}\vec{x} = \vec{0} \\
\vec{x}_{2} = C\begin{pmatrix}
5 \\
2 \\
2
\end{pmatrix} - \text{корневое подпространство глубины} \ 2
\end{gather}$$