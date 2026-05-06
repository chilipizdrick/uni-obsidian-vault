import numpy as np
import pandas as pd # Используется исключительно для упрощения форматирования таблиц
import matplotlib.pyplot as plt
from scipy.stats import norm
from math import log2, floor

from data import ms_d_norm

N = len(ms_d_norm)
y = np.array(ms_d_norm)
y_sorted = np.sort(y)

a_0 = np.min(y)
a_m = np.max(y)
m = 1 + floor(log2(N))
h = (a_m - a_0) / m

intervals = []
n_k = []
w_k = []

for k in range(1, m + 1):
    left = a_0 + (k - 1) * h
    right = a_0 + k * h
    intervals.append((left, right))

    if k == 1:
        count = np.sum((y >= left) & (y <= right))
    else:
        count = np.sum((y > left) & (y <= right))

    n_k.append(count)
    w_k.append(count / N)

df_intervals = pd.DataFrame({
    "Интервалы": [f"[{inter[0]:.5f}, {inter[1]:.5f}]" if i==0 else f"({inter[0]:.5f}, {inter[1]:.5f}]" for i, inter in enumerate(intervals)],
    "n_k": n_k,
    "w_k": w_k
})

a_hat = np.mean(y)
sigma2_hat = np.mean(y**2) - a_hat**2 - (h**2) / 12
sigma_hat = np.sqrt(sigma2_hat)

k_vals = list(range(0, m + 1))
a_k_vals = [a_0 + k * h for k in k_vals]

t_k_vals = [(ak - a_hat) / sigma_hat for ak in a_k_vals]
phi_0_vals = [norm.pdf(tk) for tk in t_k_vals]
density_vals = [(1 / sigma_hat) * phi for phi in phi_0_vals]
Phi_vals = [norm.cdf(tk) for tk in t_k_vals]

p_k_star_table = [None]
p_k_star = []

for k in range(1, m + 1):
    if k == 1:
        p = Phi_vals[1]
    elif k == m:
        p = 1 - Phi_vals[m-1]
    else:
        p = Phi_vals[k] - Phi_vals[k-1]

    p_k_star.append(p)
    p_k_star_table.append(p)

df_p_k = pd.DataFrame({
    "k": k_vals,
    "a_k": np.round(a_k_vals, 5),
    "(a_k - a^)/sigma^": np.round(t_k_vals, 5),
    "1/sigma^ * phi_0(...)": np.round(density_vals, 5),
    "Phi(...)": np.round(Phi_vals, 5),
    "p_k*": [np.round(p, 5) if p is not None else "-" for p in p_k_star_table]
})

abs_diff = np.abs(np.array(w_k) - np.array(p_k_star))
chi_components = (N * (np.array(w_k) - np.array(p_k_star))**2) / np.array(p_k_star)
chi_b_2 = np.sum(chi_components)

df_chi = pd.DataFrame({
    "k": range(1, m + 1),
    "Интервал": df_intervals["Интервалы"],
    "w_k": np.round(w_k, 5),
    "p_k*": np.round(p_k_star, 5),
    "|w_k - p_k*|": np.round(abs_diff, 5),
    "N(w_k - p_k*)^2 / p_k*": np.round(chi_components, 5)
})

print("=== Таблица 4.3: Интервальный ряд ===")
print(df_intervals.to_string(index=False))
print(f"\nОценки: a_hat = {a_hat:.5f}, sigma^2_hat = {sigma2_hat:.5f}, sigma_hat = {sigma_hat:.5f}\n")

print("=== Таблица 4.4: Вычисление p_k* ===")
print(df_p_k.to_string(index=False))
print("-" * 60)
print(f"Сумма p_k*: {np.sum(p_k_star):.5f}\n")

print("=== Таблица 4.5: Вычисление выборочного значения критерия хи-квадрат ===")
print(df_chi.to_string(index=False))
print("-" * 60)
print(f"Сумма w_k: {np.sum(w_k):.5f}")
print(f"chi^2_B = {chi_b_2:.5f}")

plt.figure(figsize=(10, 6))
plt.bar([x[0] + h/2 for x in intervals], np.array(w_k)/h, width=h, color="lightblue", edgecolor="black", label="Гистограмма отн. частот")

x_axis = np.linspace(a_0 - h, a_m + h, 1000)
plt.plot(x_axis, norm.pdf(x_axis, a_hat, sigma_hat), "r-", lw=2, label=rf"$N({a_hat:.2f}, {sigma2_hat:.2f})$")

plt.xlabel("$x$")
plt.ylabel("$f(x)$")
plt.legend()
plt.grid(True, linestyle="--", alpha=0.6)
plt.savefig("./src/assets/plot_4_1.svg")
