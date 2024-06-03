# Типовой расчет по математическому анализу 
## Ершов Алексей Геннадьевич КМБО-03-23
### Вариант 4

| 1    | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 10  |
| ---- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| <br> |     |     |     |     |     |     |     |     |     |

# 

## 1.4(a)

$$\int x^{2}\ln(x^{2}+2x+5) \, dx$$

$$\begin{gather}
\int x^{2}\ln(x^{2}+2x+5) \, dx = \frac{x^{3}}{3}\ln(x^{2}+2x+5) - \int \frac{x^{3}}{3} \cdot \frac{2x+2}{x^{2}+2x+5} \, dx = \\
= \frac{x^{3}\ln(x^{2}+2x+5)}{3} - \frac{2}{3} \underbrace{\int \frac{x^{4}+x^{3}}{x^{2}+2x+5} \, dx}_{(1)} = \dots = \\
= \frac{x^{3}\ln(x^{2}+2x+5)}{3} + \frac{x^{3}}{3}-\frac{x^{2}}{2}-3x+\frac{11}{2}\ln |x^{2}+2x+5| + \\
+ 2\arctan \frac{x+1}{2} + C
\end{gather}$$

$$\begin{gather}
(1): \int \frac{x^{4}+x^{3}}{x^{2}+2x+5} \, dx = \int \left[ (x^{2}-x-3) + \frac{11x+15}{x^{2}+2x+5} \right] \, dx = \\
= \frac{x^{3}}{3} - \frac{x^{2}}{2} - 3x + \underbrace{\int \frac{5.5(2x+2) + 4}{x^{2}+2x+5} \, dx}_{(2)} = \dots = \\
= \frac{x^{3}}{3}-\frac{x^{2}}{2}-3x+\frac{11}{2}\ln |x^{2}+2x+5| + 2\arctan \frac{x+1}{2} + C
\end{gather}$$

$$\begin{gather}
(2): \frac{11}{2}\int \frac{2x+2}{x^{2}+2x+5} \, dx + 4\int \frac{dx}{x^{2}+2x+5} = \frac{11}{2}\int \frac{d(x^{2}+2x+5)}{x^{2}+2x+5} + \\
+ 4\int \frac{dx}{(x+1)^{2} + 2^{2}} = \frac{11}{2}\ln |x^{2}+2x+5| + 2\arctan \frac{x+1}{2} + C
\end{gather}$$

## 1.4(б)

$$\int \frac{-x^{4}+5x^{3}-7x^{2}+11x-16}{(x-1)(x+1)^{2}(x^{2}-4x+5)} \, dx$$

$$\begin{gather}
\int \frac{-x^{4}+5x^{3}-7x^{2}+11x-16}{(x-1)(x+1)^{2}(x^{2}-4x+5)} \, dx = \\
= \int \underbrace{\left[\frac{A}{x-1} + \frac{B}{x+1} + \frac{C}{(x+1)^{2}} + \frac{Dx + E}{x^{2}-4x+5}\right]}_{(1)} \, dx = \\
\end{gather}$$

$$\begin{gather}
= -\int \frac{1}{x-1} \, dx + 2\int \frac{1}{(x+1)^{2}} \, dx + \int \frac{1}{x^{2}-4x+5} \, dx = \\
=-\ln |x-1| - \frac{2}{x+1} + C + \int \frac{1}{(x-2)^{2}+1^{2}} \, dx = \\
= -\ln |x-1| - \frac{2}{x+1} + \arctan(x-2) + C
\end{gather}$$

$$\begin{gather}
(1): \ \frac{-x^4+5 x^3-7 x^2+11 x-16}{(x-1) (x+1)^2 \left(x^2-4 x+5\right)}= \\
= \frac{A}{x-1}+\frac{B}{x+1}+\frac{C}{(x+1)^{2}}+\frac{Dx + E}{x^{2}-4x+5}
\end{gather}$$

$$\begin{gather}
-x^{4}+5x^{3}-7x^{2}+11x-16 = \\
= A(x+1)^{2}(x^{2}-4x+5) + B(x-1)(x+1)(x^{2}-4x+5) + \\
+ C(x-1)(x^{2}+4x-5) + (Dx+E)(x-1)(x+1)^{2}
\end{gather}$$  

$$\begin{gather}
-x^4+5 x^3-7 x^2+11 x-16=5 A-5 B-5 C-E+ \\
+\left(A+B+D\right) x^4+\left(-2 A-4 B+C+D+E\right) x^3+ \\
\left(-2 A+4 B-5 C-D+E\right) x^2+\left(6 A+4 B+9 C-D-E\right) x
\end{gather}$$

$$\begin{array}{c}
-16=5 A-5 B-5 C-E \\
11=6 A+4 B+9 C-D-E \\
-7=-2 A+4 B-5 C-D+E \\
5=-2 A-4 B+C+D+E \\
-1=A+B+D
\end{array}$$

$$\begin{gather}
\left(
\begin{array}{ccccc}
 5 & -5 & -5 & 0 & -1 \\
 6 & 4 & 9 & -1 & -1 \\
 -2 & 4 & -5 & -1 & 1 \\
 -2 & -4 & 1 & 1 & 1 \\
 1 & 1 & 0 & 1 & 0
\end{array}
\right)\left(
\begin{array}{c}
 A \\
 B \\
 C \\
 D \\
 E
\end{array}
\right) =\left(
\begin{array}{c}
 -16 \\
 11 \\
 -7 \\
 5 \\
 -1
\end{array}
\right)
\end{gather}$$

$$\begin{gather}
\left(\begin{array}{ccccc|c}
 5 & -5 & -5 & 0 & -1 & -16 \\
 6 & 4 & 9 & -1 & -1 & 11 \\
 -2 & 4 & -5 & -1 & 1 & -7 \\
 -2 & -4 & 1 & 1 & 1 & 5 \\
 1 & 1 & 0 & 1 & 0 & -1
\end{array}\right)
\end{gather}$$

После преобразований приходим к данной системе:

$$\left(
\begin{array}{ccccc|c}
 1 & 0 & 0 & 0 & 0 & -1 \\
 0 & 1 & 0 & 0 & 0 & 0 \\
 0 & 0 & 1 & 0 & 0 & 2 \\
 0 & 0 & 0 & 1 & 0 & 0 \\
 0 & 0 & 0 & 0 & 1 & 1
\end{array}
\right) \implies \begin{cases}
A = -1 \\
B = 0 \\
C = 2 \\
D = 0 \\
E = 1
\end{cases}$$

Откуда следует, что

$$\begin{gather}
\frac{-x^4+5 x^3-7 x^2+11 x-16}{(x-1) (x+1)^2 \left(x^2-4 x+5\right)}= \\
= -\frac{1}{x-1}+\frac{2}{(x+1)^{2}}+\frac{1}{x^{2}-4x+5}
\end{gather}$$
## 2.4(а)

$$\begin{gather}
\int _{0}^{2}(2+x^{2})\sqrt{ 4x-x^{2} } \, dx = \int _{0}^{2}(2+((x-2)+2)^{2}) \sqrt{ 2^{2}-(x-2)^{2} }d(x-2) = \\
= \begin{bmatrix}
x-2 = 2\sin t \\
t = \arcsin \frac{x-2}{2} \\
d(x - 2) = 2\cos t \, dt
\end{bmatrix} = \int_{-\frac{\pi}{2}}^{0} (2 + (2\sin t + 2)^{2})\sqrt{ 2^{2} - 2^{2}\sin ^{2}t } \cdot 2\cos t\,dt = \\
\end{gather}$$

$$\begin{gather}
= 4\int _{-\frac{\pi}{2}}^{0} (4\sin ^{2}t + 8\sin t + 6)\cos ^{2} t\, dt = \\
= 4 \int _{-\frac{\pi}{2}}^{0} [\sin ^{2} 2t + 8 \sin t \cos ^{2} t + 6 \cos ^{2}t]\, dt = \\
\end{gather}$$

$$\begin{gather}
= 2\int _{-\frac{\pi}{2}}^{0} [1 - \cos 4t + 8 \sin t(1 + \cos 2t) + 6(1+\cos 2t)] \, dt = \\ 
= 2\int _{-\frac{\pi}{2}}^{0} [1 - \cos 4t + 8 \sin t + 8\sin t\cos 2t + 6 + 6\cos 2t] \, dt = \\
\end{gather}$$

$$\begin{gather}
= 2\int _{-\frac{\pi}{2}}^{0} [1 - \cos 4t + 8 \sin t + 4\sin 3t - 4\sin t + 6 + 6\cos 2t] \, dt = \\ 
= 2\int _{-\frac{\pi}{2}}^{0} [7 +4\sin t + 4\sin 3t + 6\cos 2t - \cos 4t] \, dt = \\
\end{gather}$$

$$\begin{gather}
= 2\left[ 7t -4\cos t -\frac{4}{3}\cos 3t + 3\sin 2t -\frac{1}{4}\sin 4t \right] \Big|_{-\frac{\pi}{2}}^{0} = \\
= 2\left( -4-\frac{4}{3} \right) - 2\left( -\frac{7\pi}{2} \right) = 7\pi - \frac{32}{3}
\end{gather}$$

## 2.4(б)

$$\begin{gather}
\int_{1}^{1.5} \frac{(x+2)^{3}}{\sqrt{ (2x-x^{2})^{5} }} \, dx = \int_{1}^{1.5} \frac{((x-1)+3)^{3}}{\sqrt{ (1-(x-1)^{2})^{5} }} \, d(x-1) = \\
= \begin{bmatrix}
x-1 = \sin t \\
t = \arcsin(x-1) \\
d(x-1) = \cos t\,dt
\end{bmatrix} = \int_{0}^{\pi/6} \frac{(\sin t+3)^{3}}{\sqrt{ (1-\sin^{2}t)^{5} }} \cos t \, dt = \\
\end{gather}$$

$$\begin{gather}
= \int_{0}^{\pi/6} \frac{(\sin t+3)^{3}}{\cos ^{4}t} \, dt = \int_{0}^{\pi/6} \frac{\sin ^{3}t + 9\sin ^{2} t + 27\sin t + 27}{\cos ^{4}t} \, dt = \\
= \underbrace{\int_{0}^{\pi/6} \frac{\sin ^{3}t}{\cos^{4} t} \, dt}_{I_{1}} + 9\underbrace{\int_{0}^{\pi/6} \frac{\sin ^{2}t}{\cos^{4} t} \, dt}_{I_{2}} + 27\underbrace{\int_{0}^{\pi/6} \frac{\sin t}{\cos^{4} t} \, dt}_{I_{3}} + 27\underbrace{\int_{0}^{\pi/6} \frac{1}{\cos^{4} t} \, dt}_{I_{4}} = \\
\end{gather}$$

$$\begin{gather}
= \frac{88\sqrt{ 3 }-54}{27} + 9\cdot \frac{\sqrt{ 3 }}{9} + 27 \cdot \frac{160\sqrt{ 3 }-135}{27} + 27 \cdot \frac{10\sqrt{ 3 }}{27} = \\
= \frac{88\sqrt{ 3 }}{27} - 2 + \sqrt{ 3 } + 160\sqrt{ 3 } - 135 + 10\sqrt{ 3 } = \\
\end{gather}$$

$$\begin{gather}
= \frac{(88+171\cdot 27) \sqrt{ 3 } - 137 \cdot 27}{27} = \frac{4705\sqrt{ 3 } - 3699}{27}
\end{gather}$$

$$\begin{gather}
I_{1} = \int_{0}^{\pi/6} \frac{\sin ^{3}t}{\cos^{4} t} \, dt = -\int_{0}^{\pi/6} \frac{\sin ^{2}t \, d\cos t}{\cos^{4} t} = \\
= -\int_{0}^{\pi/6} \left[ \frac{d\cos t}{\cos^{4} t} - \frac{\cos ^{2}t \, d\cos t}{\cos^{4} t} \right] = \int_{0}^{\pi/6} \frac{d\cos t}{\cos ^{2}t} - \int_{0}^{\pi/6} \frac{d\cos t}{\cos ^{4}t} = \\
\end{gather}$$

$$\begin{gather}
= \left[ \frac{5}{\cos ^{5}t} - \frac{3}{\cos ^{3}t } \right] \Big|_{0}^{\pi/6} = \left( \frac{5}{\frac{9\sqrt{ 3 }}{32}} - \frac{3}{\frac{3\sqrt{ 3 }}{8}} \right) - (5-3) = \\
= \frac{160 - 72}{9\sqrt{ 3 }} - 2 = \frac{88\sqrt{ 3 }}{27} - 2 = \frac{88\sqrt{ 3 } - 54}{27}
\end{gather}$$

$$\begin{gather}
I_{2} = \int_{0}^{\pi/6} \frac{\sin^{2} t}{\cos^{4} t} \, dt = \int_{0}^{\pi/6} \tan^{2}t \, d\tan t = \frac{\tan^{3}t}{3} \Big|_{0}^{\pi/6} = \left( \frac{3\sqrt{ 3 }}{27} \right) - 0 = \frac{\sqrt{ 3 }}{9}
\end{gather}$$

$$\begin{gather}
I_{3} = \int_{0}^{\pi/6} \frac{\sin t}{\cos^{4} t} \, dt = -\int_{0}^{\pi/6} \frac{d\cos t}{\cos^{4} t} = \frac{5}{\cos ^{5}t} \Big|_{0}^{\pi/6} = \\
= \frac{5}{\frac{9\sqrt{ 3 }}{32}} - 5 = \frac{160}{9\sqrt{ 3 }} - 5 = \frac{160\sqrt{ 3 }}{27} - 5 = \frac{160\sqrt{ 3 } - 135}{27}
\end{gather}$$

$$\begin{gather}
I_{4} = \int_{0}^{\pi/6} \frac{1}{\cos^{4} t} \, dt = \begin{bmatrix}
u = \frac{1}{\cos ^{2}t} \\
dv = \frac{1}{\cos ^{2}t}dt \\
du = \frac{2\sin t}{\cos ^{3}t} \\
v = \tan t
\end{bmatrix} = \frac{\tan t}{\cos ^{2}t} \Big|_{0}^{\pi/6} - 2\int \frac{\tan^{2}t}{\cos^{2}t} \, dt  = \\
= \frac{\tan t}{\cos ^{2}t} \Big|_{0}^{\pi/6} - 2\int \tan^{2}t \, d\tan t = \left[\frac{\tan t}{\cos ^{2}t}  - \frac{2\tan^{3}t}{3}\right]\Big|_{0}^{\pi/6} = \\
\end{gather}$$

$$\begin{gather}
= \left( \frac{\frac{\sqrt{ 3 }}{3}}{\frac{3}{4}} - \frac{\frac{6\sqrt{ 3 }}{27}}{3} \right) - 0 = \frac{4\sqrt{ 3 }}{9} - \frac{2\sqrt{ 3 }}{27} =  \frac{10\sqrt{ 3 }}{27}
\end{gather}$$
## 3.4

$$\int_{0}^{\infty}e^{-4x}\cos 3x \, dx$$

$$\begin{gather}
\int_{0}^{\infty}e^{-4x}\cos 3x \, dx = \begin{bmatrix}
\left.\begin{matrix}
e^{-4x} = \frac{1}{e^{4x}} - \text{сх.} \\
\cos 3x - \text{огр.}
\end{matrix}\right\} \implies I - \text{сх.}
\end{bmatrix} = \\
= \lim_{  a \to \infty } \underbrace{\int_{0}^{a}e^{-4x}\cos 3x \, dx}_{I_{1}} = \lim_{ a \to \infty } \left.\frac{e^{-4x}(3\sin 3x -4\cos 3x)}{25} \right|_{0}^{a} = \\
\end{gather}$$

$$\begin{gather}
= \lim_{ a \to \infty } \left[\left( \frac{\cancelto{0}{ e^{-4a} }\overbrace{(3\sin 3a -4\cos 3a)}^{\text{огр.}}}{25} \right) - \left( \frac{-4}{25} \right)\right] = \frac{4}{25}
\end{gather}$$

$$\begin{gather}
I_{1} = \int_{0}^{a}e^{-4x}\cos 3x \, dx = \begin{bmatrix}
u = e^{-4x} \\
dv = \cos 3x \, dx \\
du = -4e^{-4x} \, dx \\
v = \frac{\sin 3x}{3}
\end{bmatrix} = \\ 
\end{gather}$$

$$\begin{gather}
= \frac{e^{-4x}\sin3x}{3} + \frac{4}{3}\int_{0}^{a} e^{-4x}\sin 3x \, dx = \begin{bmatrix}
u = e^{-4x} \\
dv = \sin 3x \, dx \\
du = -4e^{-4x} \, dx \\
v = -\frac{\cos3x}{3}
\end{bmatrix} = \\ 
\end{gather}$$

$$\begin{gather}
= \frac{e^{-4x}\sin3x}{3} + \frac{4}{3}\left( -\frac{e^{-4x}\cos 3x}{3} - \frac{4}{3} \underbrace{\int_{0}^{a} e^{-4x}\cos 3x \, dx}_{I_{1}} \right) \implies \\ 
\end{gather}$$

$$\begin{gather}
\implies I_{1} = \frac{e^{-4x}\sin 3x}{3} + \frac{4}{3}\left(-\frac{e^{-4x}\cos 3x}{3} - \frac{4}{3}I_{1}\right) \\
I_{1} = \frac{e^{-4x}\sin 3x}{3} -\frac{4e^{-4x}\cos 3x}{9} - \frac{16}{9}I_{1} \\ 
\end{gather}$$

$$\begin{gather}
25I_{1} = 3e^{-4x}\sin 3x -4e^{-4x}\cos 3x \\
I_{1} = \left.\frac{e^{-4x}(3\sin 3x -4\cos 3x)}{25} \right|_{0}^{a}
\end{gather}$$
## 4.4

$$\begin{gather}
\int _{a}^{b} \, dx  \int_{\phi(x)}^{\psi(x)} f(x,y) \, dy \\
a = 1, \ b = 2, \ \phi(x) = \frac{x^{2}}{4}, \ \psi(x) = \sqrt{ 5 - x^{2} }
\end{gather}$$

![[ТР 4 Математический анализ 2024-04-20 11.34.47.excalidraw|75%]]

$$\begin{gather}
D : \left\{ 1 \leq x \leq 2; \ \frac{x^{2}}{4} \leq y \leq \sqrt{ 5 - x^{2} } \right\} \implies \\
\implies D = D_{1}\cup D_{2} \ | \  \begin{cases}
D_{1} : \left\{ \frac{1}{4} \leq y \leq 1; \ 1 \leq x \leq 2\sqrt{ y } \right\} \\
D_{2} : \left\{ 1 \leq y \leq 2; \ 1 \leq x \leq \sqrt{ 5 - y^{2} } \right\}
\end{cases}
\end{gather}$$

$$\begin{gather}
\int_{1}^{2}  \, dx \int_{x^{2}/4}^{\sqrt{ 5-x^{2} }} f(x,y) \, dy = \begin{bmatrix}
y = \frac{x^{2}}{4} \implies x = 2\sqrt{ y } \\
y = \sqrt{ 5-x^{2} } \implies x = \sqrt{ 5 - y^{a} }
\end{bmatrix} = \\
= \int_{\frac{1}{4}}^{1} \, dy \int_{1}^{2\sqrt{ y }} f(x,y) \, dx + \int_{1}^{2} \, dy \int_{1}^{\sqrt{ 5 - y^{2} }} f(x,y) \, dx   \end{gather}$$ 
## 5.4

$$\begin{gather}
f: \begin{cases}
x^{2} + y^{2} + z^{2} \leq 1 \\
x^{2} + z^{2} \leq z
\end{cases}
\end{gather}$$

$\sigma_{1}$ - сфера радиусом с центром в начале координат.
$\sigma_{2}$ - цилиндр с радиусом $\frac{1}{2}$ в плоскости $xOz$, сдвинутый по оси $Oz$ на $\frac{1}{2}$.

$$\begin{gather}
V: \begin{cases}
\sigma{1} : x^{2} + y^{2} + z^{2} \leq 1^{2} \\
\sigma_{2} : x^{2} + \left( z - \frac{1}{2} \right)^{2} \leq \left(\frac{1}{2}\right)^{2}
\end{cases}
\end{gather}$$

Перейдем к цилиндрическим координатам, сдвинув область $V$ на $-\frac{1}{2}$ по оси $z$:

![[ТР 5 Математический анализ 2024-05-30 14.38.12.excalidraw|100%]]

$$V: \begin{cases}
x^{2} + y^{2} + \left( z + \frac{1}{2} \right)^{2} \leq 1^{2} \\
x^{2} + z^{2} \leq \left(\frac{1}{2}\right)^{2}
\end{cases}$$

$$\begin{cases}
x = \rho\cos \phi \\
z = \rho\sin \phi \\
z^{2} + x^{2} = \rho^{2} \\
y = h
\end{cases}$$

$$\begin{gather}
x^{2} + y^{2} + \left( z + \frac{1}{2} \right)^{2} = 1 \implies h = y = \pm\sqrt{ 1 - x^{2} - \left( z + \frac{1}{2} \right)^{2} } = \\
= \sqrt{ \frac{3}{4} - \rho^{2} - \rho \sin \phi }
\end{gather}$$

$$\begin{gather}
\iiint_{V}\,dV = \int_{0}^{2\pi} \, d\phi \int_{0}^{1/2} \rho \, d\rho \int_{-\sqrt{ \frac{3}{4} - \rho^{2} - \rho \sin \phi }}^{\sqrt{ \frac{3}{4} - \rho^{2} - \rho \sin \phi }} \, dh = \\
= 2\int_{0}^{2\pi} \, d\phi \underbrace{\int_{0}^{1/2} \rho \sqrt{ \frac{3}{4} - \rho^{2} - \rho \sin \phi } \, d\rho}_{I_{1}} = \begin{bmatrix}
\dots
\end{bmatrix}
\end{gather}$$
## 6.4

$$\begin{gather}
\oint_{L} P(x,y)\,dx + Q(x,y)\,dy \\
L = \{ (x,y) \ | \ x^{2}+y^{2}=16 \}, \ P(x,y) = -xy^{2}, \ Q(x,y) = 2x^{2}y
\end{gather}$$

## 6.4(а)

$$\begin{gather}
\oint_{L} -xy^{2} \, dx + 2x^{2}y \, dy = \begin{bmatrix}
x^{2}+y^{2}=16 \iff \\
\iff \begin{cases}
x=4\cos t \\
y=4\sin t
\end{cases}, \ t \in [0, 2\pi] \\
dx = -4\sin t\,dt \\
dy = 4\cos t\,dt 
\end{bmatrix} = \\
\end{gather}$$

$$\begin{gather}
= \int_{0}^{2\pi} \left[ -4\cos t\cdot 16\sin ^{2}t\cdot (-4\sin t) + 2\cdot 16\cos ^{2}t\cdot 4\sin t\cdot 4\cos t \right] \, dt = \\
= \int_{0}^{2\pi} \left[ 256\cos t \sin ^{3}t + 512\cos ^{3}t\sin t \right] \, dt = \\\end{gather}$$

$$\begin{gather}
= 256\int_{0}^{2\pi} \sin ^{2}(\sin t\cos t)+2\cos ^{2}t(\sin t\cos t) \, dt = \\
= 128\int_{0}^{2\pi} \sin 2t(1+\cos ^{2}t) \, dt = \\\end{gather}$$

$$\begin{gather}
= 128\int_{0}^{2\pi} \sin 2t\left( \frac{3}{2} + \frac{1}{2}\cos 2t \right) \, dt = \\
= 192\int_{0}^{2\pi} \sin 2t \, dt + 32\int_{0}^{2\pi} \sin 4t \, dt = \\\end{gather}$$

$$\begin{gather}
= \left.\left[-96\cos 2t - 8\cos 4t\right]\right|_{0}^{2\pi} = \\
= (-104) - (-104) = 0
\end{gather}$$

## 6.4(б)

$$\begin{gather}
\oint_{L} P(x,y)\, dx + Q(x,y)\, dy = \iint_{D} \left( \frac{\partial Q}{\partial x} - \frac{\partial P}{\partial y} \right) \,dxdy \\\end{gather}$$

$$\begin{gather}
\oint_{L} -xy^{2}\, dx + 2x^{2}y \, dy = \iint_{D} \left( 4xy - 2xy \right) \, dxdy = \\
= 2\iint_{D} xy \, dxdy = 2\int_{-4}^{4}  \, dx \int_{-\sqrt{ 16-x^{2} }}^{\sqrt{ 16-x^{2} }} xy \, dy = \\\end{gather}$$

$$\begin{gather}
= 2\int_{-4}^{4} x(16-x^{2}) \, dx = 2\int_{-4}^{4} 16x - x^{3} \, dx = \\
= \left.\left[ 16x^{2} - \frac{x^{4}}{2} \right] \right|_{-4}^{4} = (256 - 128) - (256 - 128) = 0
\end{gather}$$
## 7.4

$$\text{Найти} \ \mathrm{div}(u \ \mathrm{grad} \ u)$$

$$\begin{gather}
\mathrm{div}(u \ \mathrm{grad} \ u) = \mathrm{div}\left( u \begin{pmatrix}
\frac{ \partial u }{ \partial x }  \\
\frac{ \partial u }{ \partial y }  \\
\frac{ \partial u }{ \partial z } 
\end{pmatrix} \right) = \mathrm{div} \begin{pmatrix}
u\frac{ \partial u }{ \partial x }  \\
u\frac{ \partial u }{ \partial y }  \\
u\frac{ \partial u }{ \partial z } 
\end{pmatrix} = \\
= u\frac{ \partial^{2} u }{ \partial x^{2} } + u\frac{ \partial^{2} u }{ \partial y^{2} } + u\frac{ \partial^{2} u }{ \partial z^{2} } = u \left( \frac{ \partial^{2} u }{ \partial x^{2} } + \frac{ \partial^{2} u }{ \partial y^{2} } + \frac{ \partial^{2} u }{ \partial z^{2} } \right) 
\end{gather}$$
## 8.4

$$\begin{gather}
\sigma : y^{2} = x^{2}+z^{2} \\
Ц : x^{2}+z^{2}=4x \\
\end{gather}$$

![[ТР 8 Математический анализ 2024-05-30 14.26.25.excalidraw|100%]]

$$\begin{gather}
Ц : (x-2)^{2} +z^{2} = 2^{2} \\
y = \sqrt{ x^{2}-z^{2} } \\
\sigma = \sigma_{1} \cup \sigma_{2} \\
\iint_{\sigma} d\sigma = 2\iint_{\sigma_{1}} d\sigma_{1} = \\ \end{gather}$$

$$\begin{gather}
= 2\iint_{D_{xz}}\sqrt{ 1 + (y'_{x})^{2} + (y'_{z})^{2} } \, dxdz = \\
= 2\iint_{D_{xz}}\sqrt{ 1 + \frac{x^{2}}{x^{2}+z^{2}} + \frac{z^{2}}{x^{2}+z^{2}} } \, dxdz = \\
= 2\iint_{D_{xz}}\sqrt{ 2 } \, dxdz = \\\end{gather}$$

$$\begin{gather}
= 2\sqrt{ 2 }\int_{0}^{4} \, dx \int_{-\sqrt{ 4x-x^{2} }}^{\sqrt{ 4x-x^{2} }} \, dz = 4\sqrt{ 2 }\int_{0}^{4} \sqrt{ 4x-x^{2} } \, dx = \\
= 4\sqrt{ 2 }\int_{0}^{4} \sqrt{ -(x-2)^{2} + 4 } \, dx = \begin{bmatrix}
x-2 = 2\sin t \\
t = \arcsin \frac{x-2}{2} \\
d(x-2) = 2\cos t
\end{bmatrix} = \\\end{gather}$$

$$\begin{gather}
= 16\sqrt{ 2 }\int_{-\pi/2}^{\pi/2} \sqrt{ 1-\sin ^{2}t } \, \cos tdt = 16\sqrt{ 2 }\int_{-\pi/2}^{\pi/2} \cos ^{2}t \, dt = \\
= 4\sqrt{ 2 }\int_{-\pi/2}^{\pi/2} [\cos 2t + 1] \, d(2t) = \\
= 4\sqrt{ 2 }\left.\left[ \sin 2t + 2t \right]\right|_{-\pi/2}^{\pi/2} = 8\sqrt{ 2 }\pi
\end{gather}$$
## 9.6 (вар. 6 т.к. 4 решили на семинаре)

$$\begin{gather}
a = \{ 3x; 2y; z^{2} \} \\
\sigma : x^{2}+y^{2}+z^{2} = 4, y \geq 0
\end{gather}$$

![[ТР 9 Математический анализ 2024-05-29 18.08.24.excalidraw|100%]]

## 9.6(а)

$$\begin{gather}
\sigma = \sigma_{1} \ (y = 0) \cup \sigma_{2} \ (x^{2} + y^{2} + z^{2} = 4) \\
\iint_{\sigma} = \iint_{\sigma_{1}} + \iint_{\sigma_{2}} \\
\end{gather}$$

$$\begin{gather}
\iint_{\sigma_{1}} 3x\,dydz + 2y\,dxdz + z^{2}\,dxdy =  \begin{bmatrix}
F_{\sigma_{1}} : y = 0 \\
\vec{N}_{\sigma_{1}} = \{ 0; -1; 0 \} \\
\end{bmatrix} = \\
-\left. \iint_{D_{xz}} 2y \, dxdz \right|_{y = 0} = 0
\end{gather}$$

$$\begin{gather}
\iint_{\sigma_{2}} 3x\,dydz + 2y\,dxdz + z^{2}\,dxdy = \\
= \begin{bmatrix}
F_{\sigma_{2}} : y = \sqrt{ 4-x^{2}-z^{2} } \\
\vec{N}_{\sigma_{2}} = \{ -y'_{x}; 1; -y'_{z} \} = \\
= \left\{  \frac{x}{\sqrt{ 4-x^{2}-z^{2} }}; 1; \frac{z}{\sqrt{ 4-x^{2}-z^{2} }} \right\}
\end{bmatrix} = \\
\end{gather}$$

$$\begin{gather}
= \left. \iint_{D_{xz}} \frac{3x^{2}}{\sqrt{ 4-x^{2}-z^{2}}} + 2y + \frac{z^{3}}{\sqrt{ 4-x^{2}-z^{2} }} \, dxdy \right|_{y = \sqrt{ 4-x^{2}-z^{2} }} = \\
= \iint_{D_{xz}} \frac{3x^{2}}{\sqrt{ 4-x^{2}-z^{2}}} + 2\sqrt{ 4-x^{2}-z^{2} } + \frac{z^{3}}{\sqrt{ 4-x^{2}-z^{2} }} \, dxdy = \\
\end{gather}$$

$$\begin{gather}
= \begin{bmatrix}
x = r\cos \phi \\
z = r\sin \phi \\
r^{2} = x^{2} + z^{2} \\
|J| = r
\end{bmatrix} = \\
= \int_{0}^{2\pi} \, d\phi \int_{0}^{2} r\left[ \frac{3r^{2}\cos^{2} \phi + r^{3}\sin^{3} \phi}{\sqrt{ 4-r^{2} }} + 2\sqrt{ 4-r^{2} } \right]  \, dr =
\end{gather}$$

$$\begin{gather}
= \int_{0}^{2\pi} \, d\phi \int_{0}^{2} \left[ \frac{3r^{3}\cos^{2} \phi + r^{4}\sin^{3} \phi + 2r(4-r^{2})}{\sqrt{ 4-r^{2} }} \right]  \, dr = \\
= \begin{bmatrix}
r = 2\sin t \\
t = \arcsin \frac{r}{2} \\
dr = 2\cos t\,dt
\end{bmatrix} = \\
\end{gather}$$

$$\begin{gather}
= \int_{0}^{2\pi} \, d\phi \int_{0}^{\pi/2} \left[ \frac{24\cos^{2} \phi \cdot \sin^{3} t + 16\sin^{3} \phi \cdot \sin^{4} t + 32\sin t\cos^{2} t}{2\cos t} \right] \cdot 2\cos t \, dt = \\
= 8\int_{0}^{2\pi} \, d\phi \underbrace{\int_{0}^{\pi/2} \left[ 3\cos^{2} \phi \cdot \sin^{3} t + 2\sin^{3} \phi \cdot \sin^{4} t + 4\sin t\cos^{2} t \right] \, dt}_{I_{1}} = \\
= \dots \ (\text{см. ниже}) = \\
\end{gather}$$

$$\begin{gather}
= \int_{0}^{2\pi} \left[ 3\pi \sin ^{3}\phi + 16\cos ^{2}\phi + \frac{16}{3} \right] \, d\phi = \\
= \int_{0}^{2\pi} \left[ \frac{3\pi}{2} \sin \phi(1-\cos 2\phi) + 8(1+\cos 2\phi) + \frac{16}{3} \right] \, d\phi
\end{gather}$$

$$\begin{gather}
= \int_{0}^{2\pi} \left[ \underbrace{\frac{3\pi}{2} \sin \phi(1-\cos 2\phi) + 8\cos 2\phi}_{\text{будет}=0} + \frac{40}{3} \right] \, d\phi = \underline{\underline{\frac{80\pi}{3}}} \\
I_{1} = \int_{0}^{\pi/2} \left[ 3\cos^{2} \phi \cdot \sin^{3} t + 2\sin^{3} \phi \cdot \sin^{4} t + 4\sin t\cos^{2} t \right] \, dt = \\
\end{gather}$$

$$\begin{gather}
= \int_{0}^{\pi/2} \left[ \frac{3}{2}\cos^{2} \phi \sin t(1-\cos 2t) + \frac{1}{2}\sin^{3} \phi (1-\cos 2t)^{2} + 2\sin t(1 + \cos 2t) \right] \, dt = \\
= \int_{0}^{\pi/2} \left[ \frac{3}{4}\cos^{2} \phi (3\sin t - \sin 3t) + \frac{1}{2}\sin^{3} \phi \left( 1 - 2\cos 2t + \frac{1}{2}(1+\cos 4t) \right) + \right. \\
+ \left.2\sin t + 2\sin t\cos 2t \right] \, dt = \\
\end{gather}$$

$$\begin{gather}
= \int_{0}^{\pi/2} \left[ \frac{3}{4}\cos^{2} \phi (3\sin t - \sin 3t) + \right. \\
\left. + \frac{1}{2}\sin^{3} \phi \left( \frac{3}{2} - 2\cos 2t + \underbrace{\frac{1}{2}\cos 4t}_{\text{будет} = 0} \right) + 2\sin 3t \right] \, dt =
\end{gather}$$

$$\begin{gather}
= \int_{0}^{\pi/2} \left[ \left( 2-\frac{3}{4}\cos^{2} \phi \right)\sin 3t + \frac{9}{4}\cos^{2} \phi \sin t - \sin^{3} \phi \cos 2t + \frac{3}{4}\sin^{3} \phi \right] \, dt = \\
= \left.\left[ -\frac{1}{3}\left( 2-\frac{3}{4}\cos^{2} \phi \right) \cdot \cos 3t - \frac{9}{4}\cos^{2} \phi \cdot \cos t - \right.\right. \\
\end{gather}$$

$$\begin{gather}
\left.\left. - \frac{1}{2}\sin^{3} \phi \cdot \sin 2t + \frac{3}{4}\sin^{3} \phi \cdot t \right]\right|_{0}^{\pi/2} = \\
= \frac{1}{3}\left( 2-\frac{3}{4}\cos^{2} \phi \right) + \frac{9}{4}\cos^{2} \phi + \frac{3\pi}{8}\sin^{3} \phi = \\
= \frac{3\pi}{8}\sin^{3} \phi + 2\cos^{2} \phi + \frac{2}{3}
\end{gather}$$

## 9.6(б) (по т. Гаусса-Остроградского)

$$\begin{gather}
\iint_{\sigma} P\,dydz + Q\,dxdz + R\,dzdy = \iiint_{V} (P'_{x} + Q'_{y} + R'_{z})\,dxdydz
\end{gather}$$

$$\begin{gather}
\iint_{\sigma} 3x\,dydz + 2y\,dxdz + z^{2}\,dxdy = \iiint_{V} (2z + 5) \, dxdydz = \\
= \begin{bmatrix}
x = r\cos \phi \\
z = r\sin \phi \\
r^{2} = x^{2} + z^{2} \\
|J| = r
\end{bmatrix} = \\
\end{gather}$$

$$\begin{gather}
= \int_{0}^{2\pi}  \, d\phi \int_{0}^{2} r \, dr \int_{0}^{\sqrt{ 4-r^{2} }} \left[ 2r\sin\phi+5 \right] \, dy = \\
= \int_{0}^{2\pi}  \, d\phi \underbrace{\int_{0}^{2} \left[ r\sqrt{ 4-r^{2} }(2r\sin \phi+5) \right] \, dr}_{I_{2}} = \\
= \dots \ (\text{см. ниже}) = \\
\end{gather}$$

$$\begin{gather}
= \int_{0}^{2\pi} \left[ 2\pi \sin \phi + \frac{40}{3} \right]  \, d\phi = \\
=\left.\left[ -2\pi \cos \phi + \frac{40\phi}{3} \right]\right|_{0}^{2\pi} = \underline{\underline{\frac{80\pi}{3}}}
\end{gather}$$

$$\begin{gather}
I_{2} = \int_{0}^{2} r\sqrt{ 4-r^{2} }(2r\sin \phi+5) \, dr = \\
= \begin{bmatrix}
r = 2\sin t \\
t = \arcsin \frac{r}{2} \\
dr = 2\cos t\,dt
\end{bmatrix} = \\
\end{gather}$$

$$\begin{gather}
= 8\int_{0}^{\pi/2} \left[ 4\sin \phi \sin^{2} t \cos^{2} t + 5\sin t \cos^{2} t \right]  \, dt = \\
= 4\sin \phi \int_{0}^{\pi/2} dt - \sin \phi \int_{0}^{\pi/2} \cos (4t) \, d(4t) + \frac{10}{3} \int_{0}^{\pi/2} \sin (3t) \, d(3t) + \\
+ 10 \int_{0}^{\pi/2} \sin t \, dt = 2\pi \sin \phi + \frac{40}{3}
\end{gather}$$

## 10.4

$$
\vec{a} = \{ y;xy;-z \}, \ 
\Gamma = x+y+z=2, \left[\begin{align}
&x=0 \\
&z=0 \\
&y=0
\end{align}\right.
$$

![[scan_2024-05-23_12-49-56.jpg]]

## 10.4(а)

$$\begin{gather}
\oint_{\Gamma} y\,dx + xy\,dy -z\,dz \\
\oint_{\Gamma} = \oint_{\Gamma_{1}} + \oint_{\Gamma_{2}} + \oint_{\Gamma_{3}}
\end{gather}$$

$$\begin{gather}
\oint_{\Gamma_{1}} = \begin{bmatrix}
F : y = 2-x \implies x = 2-y \\
y = t, \ 
x = 2-t, \ 
z = 0 \\
t \in [0;2] \\
dx = -dt \\
dy = dt \\
dz = 0
\end{bmatrix} = \int_{0}^{2} \left(-t + t(2-t) \right)\,dt = \\
= \int_{0}^{2} \left( -t^{2} + t \right) \, dt = -\frac{8}{3} + 2 = -\frac{2}{3}
\end{gather}$$

$$\begin{gather}
\oint_{\Gamma_{2}} = \begin{bmatrix}
F : z = 2-x \\
x = t, \
z = 2-t, \
y = 0 \\
t \in [0;2] \\
dx = dt \\
dy = 0 \\
dz = -dt
\end{bmatrix} = \int_{0}^{2} \left( 2-t \right)  \, dt = 4 - 2 = 2
\end{gather}$$

$$\begin{gather}
\oint_{\Gamma_{3}} = \begin{bmatrix}
F : z = 2-y \\
y = t, \
z = 2-t, \
x = 0 \\
t \in [0; 2] \\
dx = 0 \\
dy = dt \\
dz = -dt
\end{bmatrix} = \int_{0}^{2} (t-2) \, dt = \\
= -\int_{0}^{2} (2-t) \, dt = -\oint_{\Gamma_{2}} = -2
\end{gather}$$

$$\begin{gather}
\oint_{\Gamma} = -\frac{2}{3} + 2 - 2 = -\frac{2}{3}
\end{gather}$$

## 10.4(б) (по т. Стокса)

$$\begin{gather}
\oint_{\Gamma} (\vec{a}, d\vec{r}) = \iint_{\sigma} (\mathrm{rot} \ \vec{a}, \vec{n}) \,d\sigma \\
\mathrm{rot} \ \vec{a} = \begin{vmatrix}
\vec{i} & \vec{j} & \vec{k} \\
\frac{ \partial  }{ \partial x } & \frac{ \partial  }{ \partial y } & \frac{ \partial  }{ \partial z } \\
y & xy & -z
\end{vmatrix} = \vec{i} \cdot 0 - \vec{j} \cdot 0 + \vec{k} \cdot (y-1) = \{ 0; 0; y-1 \} \\
\end{gather}$$

$$\begin{gather}
\vec{n} = \{ 1; 1; 1 \} \ (\text{смотрит на нас}) \\
\iint_{\sigma} (\mathrm{rot} \ \vec{a}, \vec{n}) \, d\sigma = \iint_{\sigma} (y-1) \, d\sigma = \\
= \int_{0}^{2} \, dx \int_{0}^{2-x} (y-1) \, dy = \frac{1}{2}\int_{0}^{2} (-2x+x^{2}) \, dx = -\frac{2}{3}
\end{gather}$$