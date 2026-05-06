import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats

# Параметры варианта 62
V = 62
N = 200
r = 6
p = 0.624
seed = V + 10

rng = np.random.default_rng(seed)
sample = rng.negative_binomial(r, p, N)
sample_sorted = np.sort(sample)

print("Выборка:")
print([int(x) for x in sample])

print("\nОтсортированная выборка:")
print([int(x) for x in sample_sorted])

x_i, counts = np.unique(sample_sorted, return_counts=True)
w_i = counts / N
F_emp = np.cumsum(w_i)

mean_emp = np.sum(x_i * w_i)
mu_2 = np.sum((x_i**2) * w_i)
mu_3 = np.sum((x_i**3) * w_i)
mu_4 = np.sum((x_i**4) * w_i)

D_emp = mu_2 - mean_emp**2
std_emp = np.sqrt(D_emp)

mu_3_0 = mu_3 - 3*mu_2*mean_emp + 2*(mean_emp**3)
mu_4_0 = mu_4 - 4*mu_3*mean_emp + 6*mu_2*(mean_emp**2) - 3*(mean_emp**4)

skew_emp = mu_3_0 / (std_emp**3)
kurt_emp = mu_4_0 / (std_emp**4) - 3

mode_emp = x_i[np.argmax(counts)]
median_idx = np.where(F_emp >= 0.5)[0][0]
median_emp = x_i[median_idx]

q = 1 - p
mean_th = r * q / p
D_th = r * q / (p**2)
std_th = np.sqrt(D_th)
mode_th = int((r - 1) * q / p)
skew_th = (q - p) / np.sqrt(r * q)
kurt_th = (p**2) / (r * q) + 6 / r
median_th = stats.nbinom.median(r, p)

# График ЭФР
plt.figure(figsize=(6, 5))
x_ext = np.concatenate(([x_i[0] - 1], x_i, [x_i[-1] + 1]))
F_ext = np.concatenate(([0], F_emp, [1]))
for i in range(len(x_ext) - 1):
    x_start = x_ext[i]
    x_end = x_ext[i+1]
    y_val = F_ext[i]
    plt.plot([x_start, x_end], [y_val, y_val], color="tab:blue")
    plt.plot(x_end, y_val, marker=">", color="tab:blue", markersize=3)
plt.xlabel("$x$")
plt.ylabel("$F(x)$")
plt.grid(True, alpha=0.3)
plt.savefig("./src/assets/plot_2_1.svg")

# Полигон частот
plt.figure(figsize=(6, 5))
plt.plot(x_i, w_i, label="Относительные частоты")
M = max(x_i)
x_th = np.arange(0, M+1)
p_th = stats.nbinom.pmf(x_th, r, p)
plt.plot(x_th, p_th, color="red", label="Теоретические вероятности")
plt.xlabel("$x$")
plt.ylabel("$w / p$")
plt.legend()
plt.grid(True, alpha=0.3)
plt.savefig("./src/assets/plot_2_2.svg")

summ = 0
print("\n--- Таблица 1: Статистический ряд ---")
print(f"{"x_i^*":>5} | {"n_i":>10} | {"w_i":>10} | {"S_i":>10}")
for x, i in zip(x_i, counts):
    summ += i
    w = i / N
    print(f"{x:5} | {i:10} | {w:10.5f} | {summ:10}")

print("\n--- Таблица 2: Сравнение частот и вероятностей ---")
print(f"{"x_i":>5} | {"w_i":>10} | {"p_i":>10} | {"|w_i - p_i|":>12}")
for x, w in zip(x_i, w_i):
    p_val = stats.nbinom.pmf(x, r, p)
    print(f"{x:5} | {w:10.5f} | {p_val:10.5f} | {abs(w - p_val):12.5f}")

print("\n--- Таблица 3: Сравнение характеристик ---")
chars = [
    ("Среднее", mean_emp, mean_th),
    ("Дисперсия", D_emp, D_th),
    ("СКО", std_emp, std_th),
    ("Мода", mode_emp, mode_th),
    ("Медиана", median_emp, float(median_th)),
    ("Асимметрия", skew_emp, float(skew_th)),
    ("Эксцесс", kurt_emp, kurt_th)
]

print(f"{"Характеристика":<15} | {"Выборочное":>10} | {"Теоретическое":>13} | {"Абс. откл.":>10} | {"Отн. откл.":>10}")
for name, emp, th in chars:
    abs_err = abs(emp - th)
    rel_err = abs_err / abs(th) if th != 0 else 0
    print(f"{name:<15} | {emp:10.5f} | {th:13.5f} | {abs_err:10.5f} | {rel_err:10.5f}")
