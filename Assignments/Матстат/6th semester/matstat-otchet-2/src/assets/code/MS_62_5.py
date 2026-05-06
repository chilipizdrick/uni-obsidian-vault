import numpy as np
import pandas as pd # Используется исключительно для упрощения форматирования таблиц
import matplotlib.pyplot as plt
from scipy.stats import expon

from data import ms_d_exp, lambda_val

N = len(ms_d_exp)
y = np.array(ms_d_exp)
y_sorted = np.sort(y)

F_N = np.arange(1, N + 1) / N
F_N_minus_0 = np.arange(0, N) / N

F_theor = expon.cdf(y_sorted, scale=1/lambda_val)

diff_1 = np.abs(F_N - F_theor)
diff_2 = np.abs(F_N_minus_0 - F_theor)

max_diff_1_idx = np.argmax(diff_1)
max_diff_2_idx = np.argmax(diff_2)

if diff_1[max_diff_1_idx] >= diff_2[max_diff_2_idx]:
    D_N = diff_1[max_diff_1_idx]
    y_star = y_sorted[max_diff_1_idx]
    f_y_star = F_theor[max_diff_1_idx]
    f_n_y_star = F_N[max_diff_1_idx]
    f_n_y_star_m0 = F_N_minus_0[max_diff_1_idx]
else:
    D_N = diff_2[max_diff_2_idx]
    y_star = y_sorted[max_diff_2_idx]
    f_y_star = F_theor[max_diff_2_idx]
    f_n_y_star = F_N[max_diff_2_idx]
    f_n_y_star_m0 = F_N_minus_0[max_diff_2_idx]

D_N_sqrt_N = D_N * np.sqrt(N)

df_kolmogorov = pd.DataFrame({
    "N": [N],
    "D_N": [np.round(D_N, 5)],
    "D_N * sqrt(N)": [np.round(D_N_sqrt_N, 5)],
    "y*": [np.round(y_star, 5)],
    "F(y*)": [np.round(f_y_star, 5)],
    "F_N(y*)": [np.round(f_n_y_star, 5)],
    "F_N(y* - 0)": [np.round(f_n_y_star_m0, 5)]
})

print("=== Таблица 5.3: Вычисление выборочного значения критерия Колмогорова ===")
print(df_kolmogorov.to_string(index=False))

plt.figure(figsize=(10, 6))
x_axis = np.linspace(0, np.max(y_sorted) + 1, 1000)
plt.plot(x_axis, expon.cdf(x_axis, scale=1/lambda_val), "r-", lw=2, label=rf"Теоретическая F(x), $\lambda={lambda_val}$")
plt.step(y_sorted, F_N, where="post", color="blue", lw=1.5, label="Эмпирическая F_N(x)")
plt.xlabel("$x$")
plt.ylabel("$F(x)$")
plt.legend()
plt.grid(True, linestyle="--", alpha=0.6)
plt.xlim(0, np.max(y_sorted) + 0.5)
plt.ylim(-0.05, 1.05)
plt.savefig("./src/assets/plot_5_1.svg")
