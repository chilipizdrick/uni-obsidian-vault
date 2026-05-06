import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats

# Параметры варианта 62
V = 62
N = 200
lam = 1.186
seed = V + 10

rng = np.random.default_rng(seed)
sample = rng.exponential(scale=1/lam, size=N)
sample_sorted = np.sort(sample)

print("Выборка:")
print([float(round(x, 5)) for x in sample])

print("\nОтсортированная выборка:")
print([float(round(x, 5)) for x in sample_sorted])

m = 1 + int(np.log2(N))
a_0 = 0
a_m = np.max(sample)
h = (a_m - a_0) / m
bins = np.linspace(a_0, a_m, m + 1)

counts, _ = np.histogram(sample, bins=bins)
w_i = counts / N
x_star = (bins[:-1] + bins[1:]) / 2

F_emp_x = np.insert(sample_sorted, 0, 0)
F_emp_y = np.arange(N + 1) / N

mean_emp = np.sum(x_star * w_i)
mu_2 = np.sum((x_star**2) * w_i)
mu_3 = np.sum((x_star**3) * w_i)
mu_4 = np.sum((x_star**4) * w_i)

D_emp_raw = mu_2 - mean_emp**2
s2_b = D_emp_raw - (h**2) / 12
std_emp = np.sqrt(s2_b)

mu_3_0 = mu_3 - 3*mu_2*mean_emp + 2*(mean_emp**3)
mu_4_0 = mu_4 - 4*mu_3*mean_emp + 6*mu_2*(mean_emp**2) - 3*(mean_emp**4)

skew_emp = mu_3_0 / (std_emp**3)
kurt_emp = mu_4_0 / (std_emp**4) - 3

k = np.argmax(w_i)
if k == 0:
    w_prev = 0
    w_next = w_i[k+1]
elif k == m - 1:
    w_prev = w_i[k-1]
    w_next = 0
else:
    w_prev = w_i[k-1]
    w_next = w_i[k+1]

mode_emp = bins[k] + h * (w_i[k] - w_prev) / (2*w_i[k] - w_prev - w_next)

cumsum_w = np.cumsum(w_i)
k_med = np.where(cumsum_w >= 0.5)[0][0]
sum_prev = cumsum_w[k_med-1] if k_med > 0 else 0
median_emp = bins[k_med] + (h / w_i[k_med]) * (0.5 - sum_prev)

mean_th = 1 / lam
D_th = 1 / (lam**2)
std_th = 1 / lam
mode_th = 0
median_th = np.log(2) / lam
skew_th = 2
kurt_th = 6

# График ЭФР
plt.figure(figsize=(6, 5))
plt.plot(F_emp_x, F_emp_y, drawstyle="steps-post")
plt.xlabel("$x$")
plt.ylabel("$F(x)$")
plt.grid(True, alpha=0.3)
plt.savefig("./src/assets/plot_3_1.svg")

# Гистограмма частот
plt.figure(figsize=(6, 5))
plt.bar(x_star, w_i/h, width=h, edgecolor="black", alpha=0.7, label="Относительные частоты")
x_th = np.linspace(0, a_m, 100)
f_th = lam * np.exp(-lam * x_th)
plt.plot(x_th, f_th, color="red", lw=2, label="Теоретическая плотность")
plt.xlabel("$x$")
plt.ylabel("$f(x)$")
plt.grid(True, alpha=0.3)
plt.legend()
plt.savefig("./src/assets/plot_3_2.svg")

print("\n--- Таблица 1: Интервальный ряд ---")
print(f"{"Интервалы":<15} | {"n_i":>10} | {"w_i":>10}")
for i in range(m):
    interval_str = f"[{bins[i]:.3f}, {bins[i+1]:.3f})"
    in_interval_count = len([x for x in sample_sorted if bins[i] < x < bins[i+1]])
    print(f"{interval_str:<15} | {in_interval_count:>10} | {w_i[i]:10.5f}")

print("\n--- Таблица 2: Ассоциированный статистический ряд ---")
print(f"{"x_i^*":<15} | {"n_i":>10} | {"w_i":>10}")
for i in range(m):
    print(f"{x_star[i]:<15.5f} | {int(counts[i]):>10} | {w_i[i]:10.5f}")
print("-" * 43)
print(f"{"Сумма:":<15} | {int(np.sum(counts)):>10} | {np.sum(w_i):10.5f}")


print("\n--- Таблица 3: Сравнение вероятностей по интервалам ---")
print(f"{"Интервал":<15} | {"w_i":>10} | {"p_i":>10} | {"|w_i - p_i|":>12}")
for i in range(m):
    p_val = stats.expon.cdf(bins[i+1], scale=1/lam) - stats.expon.cdf(bins[i], scale=1/lam)
    interval_str = f"[{bins[i]:.3f}, {bins[i+1]:.3f})"
    print(f"{interval_str:<15} | {w_i[i]:10.5f} | {p_val:10.5f} | {abs(w_i[i] - p_val):12.5f}")

print("\n--- Таблица 4: Сравнение характеристик ---")
chars = [
    ("Среднее", mean_emp, mean_th),
    ("Дисперсия", s2_b, D_th),
    ("СКО", std_emp, std_th),
    ("Мода", mode_emp, mode_th),
    ("Медиана", median_emp, median_th),
    ("Асимметрия", skew_emp, skew_th),
    ("Эксцесс", kurt_emp, kurt_th)
]

print(f"{"Характеристика":<15} | {"Выборочное":>10} | {"Теоретическое":>13} | {"Абс. откл.":>10} | {"Отн. откл.":>10}")
for name, emp, th in chars:
    abs_err = abs(emp - th)
    rel_err = abs_err / abs(th) if th != 0 else 0
    print(f"{name:<15} | {emp:10.5f} | {th:13.5f} | {abs_err:10.5f} | {rel_err:10.5f}")
