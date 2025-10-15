---
tags:
  - seminar
  - 5th-semester
  - 2025-10-06
---

### Задача 1

$$\begin{gather}
n = 600, \ p = 0.4 \\
P(210 \leq k \leq 270)
\end{gather}$$

> [!important] Теорема Муавра-Лапласа
> Биномиальное распределение можно заменить нормальным, чем больше $n$, тем больше точность приближения.

$$\begin{gather}
np = 240, \ \sqrt{ npq } = 12 \\
P(210 \leq k \leq 270) = P\left( \frac{210 - 240}{12} \leq \frac{k-np}{\sqrt{ npq }} \leq \frac{270 - 240}{12} \right) = \\
= \Phi(2.5) - \Phi(-2.5) = 0.9876
\end{gather}$$

### Задача 2

$$\begin{gather}
n = 1000, \ p = \frac{1}{2} \\
P(np-z < k < np + z) = 0.99 \\
P\left( -\frac{z}{\sqrt{ npq }} < \frac{k-np}{\sqrt{ npq }} < \frac{z}{\sqrt{ npq }}\right) = 0.99 \\
P\left( -\frac{z}{\sqrt{ 250 }} < \frac{k-np}{\sqrt{ npq }} < \frac{z}{\sqrt{ 250 }} \right) = \Phi\left( \frac{z}{\sqrt{ 250 }} \right) - \Phi\left( -\frac{z}{\sqrt{ 250 }} \right) \approx \\
\approx \Phi \left( \frac{z}{15.8} \right) - \Phi\left( -\frac{z}{15.8} \right) = 0.99
\end{gather}$$

$$\begin{gather}
\Phi(-x) = 1-\Phi(x) \implies 2\Phi\left( \frac{z}{\sqrt{ npq }} \right) - 1 = 0.99 \implies\\
\implies \Phi\left( \frac{z}{\sqrt{ npq }} \right) = 0.995
\end{gather}$$

$$\begin{gather}
\frac{z}{\sqrt{ 250 }} = 2.576 \\
z \approx 41
\end{gather}$$

### Задача 3

$$\begin{gather}
n = 900, \ p = 0.2, \ np = 180, \ \sqrt{ npq } = 12 \\
P(k < z) = 0.99 \\
P\left( -\frac{np}{\sqrt{ npq }} < \frac{k-np}{\sqrt{ npq }} < \frac{z - np}{\sqrt{ npq }}\right) = 0.99 \\
\Phi\left( \frac{z-180}{12} \right) - \Phi\left( -\frac{180}{12} \right) = 0.99 \\
\Phi\left( \frac{z-180}{12} \right) = 0.99 + \Phi\left( -\frac{180}{12} \right) \\
\frac{z-180}{12} = 2.326 \\
z = 12\cdot 2.326 + 180 \approx 208
\end{gather}$$

> [!important] Локальная теорема Муавра-Лапласа
> Приблизить вероятность происхождения события под номером $k$ можно, если взять его на интервале $\left( k-\frac{1}{2}, k+\frac{1}{2} \right)$.
> $$\begin{gather}
P_{n}(k) = \frac{1}{\sqrt{ 2\pi }} \cdot \frac{1}{\sqrt{ npq }} \cdot e^{-x^{2}/2}, \ \text{где} \ x = \frac{k-np}{\sqrt{ npq }}
\end{gather}$$

### Задача 4

В группе 30 человек, вероятность мальчика = $\frac{1}{2}$, найти вероятность, что мальчиков и девочек будет поровну.

$$P_{30}(15) = \left[\begin{align}
& Бином. \\
& Интегр. \\
& Локальн. \\
\end{align}\right.$$

$$\begin{gather}
\ P_{30}(15) = 0.1444644481 \\
\ P_{30}(15) = \Phi\left( \frac{15.5 - 15}{\sqrt{ 30\cdot \frac{1}{4} }} \right) - \Phi \left(\frac{14.5 - 15}{\sqrt{ 30\cdot \frac{1}{4} }}\right) = \\
= \Phi\left( \frac{1}{2} \cdot \frac{1}{2.7386} \right) - \Phi\left( -\frac{1}{2}\cdot \frac{1}{2.7386} \right) = 0.5724342642 - 0.4275657358 = \\
= 0.1448685284
\end{gather}$$

$$\begin{gather}
3. P_{30}(15) = 0.1456731241
\end{gather}$$

### Задача 5

Каждый студент независимо ходит на лекцию с вероятностью $0.2$.

$$\begin{gather}
P(np-z \leq k \leq np+z) = 0.99 \\
P\left( -\frac{z}{\sqrt{ npq }} \leq \frac{k-np}{\sqrt{ npq }}\leq \frac{z}{\sqrt{ npq }} \right) = 0.99 \\
z = 10.304
\end{gather}$$

> [!definition] Закон больших чисел
> $$\begin{gather}
P\left( \left| \frac{k}{n}-p \right| < \epsilon  \right) = P\left( -\epsilon < \frac{k-np}{n} < \epsilon \right) = \\
= P\left( -\epsilon \sqrt{ \frac{n}{pq} } < \frac{k-np}{\sqrt{ npq }} < \epsilon\sqrt{ \frac{n}{pq} } \right) = 2\Phi\left( \epsilon \sqrt{ \frac{n}{pq} } \right) - 1
\end{gather}$$

### Задача 6

Сколько раз надо бросить игральную кость, чтобы вероятность $$\left| \frac{k}{n} - \frac{1}{6} \right| < 0.01$$ была больше вероятности другого события.

$$\begin{gather}
P\left( \left| \frac{k}{n} -\frac{1}{6} \right| < 0.01 \right) = \frac{1}{2} \\
2\Phi\left( \epsilon \sqrt{ \frac{n}{pq} } \right) - 1 = \frac{1}{2} \\
\Phi\left( \epsilon \sqrt{ \frac{n}{pq} } \right) = \frac{3}{4} \\
\sqrt{ \frac{n}{pq} } = 67.44897502 \\
\frac{n}{pq} = 4549.36 \\
n = 4549.36\cdot \frac{5}{36} \approx 632 \\
\end{gather}$$

