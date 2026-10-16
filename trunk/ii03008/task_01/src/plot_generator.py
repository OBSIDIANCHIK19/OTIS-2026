import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def generate_plots():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.abspath(os.path.join(script_dir, ".."))
    doc_dir = os.path.join(project_root, "doc")
    
    os.makedirs(doc_dir, exist_ok=True)
    
    data_file = os.path.join(doc_dir, "results.csv")
    if not os.path.exists(data_file):
        print(f"[ОШИБКА] Не найден файл данных: {data_file}")
        return

    df = pd.read_csv(data_file)
    title_text = "OTIS-2026 — результат моделирования, вариант 3"
    
    tau = df['tau']
    # Базовые коэффициенты модели 1.7 для симуляции разных откликов
    a = 0.7
    b1, b2, b3 = 0.5, 0.2, 0.1

    # Функция расчета модели 1.7 для разных типов u(t)
    def simulate(u_type, steps=len(tau)):
        y = np.zeros(steps)
        u = np.zeros(steps)
        for t in range(steps):
            if u_type == 'step':
                u[t] = 5.0  # Ступенчатое
            elif u_type == 'impulse':
                u[t] = 5.0 if t == 0 else 0.0  # Импульсное
            elif u_type == 'harmonic':
                u[t] = 5.0 * np.sin(t * 0.5)  # Гармоническое
            
            if t == 0:
                y[t] = 1.0
            else:
                u_prev1 = u[t-1] if t-1 >= 0 else 0
                u_prev2 = u[t-2] if t-2 >= 0 else 0
                y[t] = a * y[t-1] + b1 * u[t] + b2 * u_prev1 + b3 * u_prev2
        return tau, u, y

    # 1. Ступенчатое воздействие -> plot.png
    _, _, y_step = simulate('step')
    plt.figure(figsize=(8, 6))
    plt.plot(tau, y_step, label='y(t) (ступенчатое)', color='tab:blue', linewidth=1.5)
    plt.title(f"{title_text}\n(Ступенчатое воздействие)", fontsize=13)
    plt.xlabel('τ', fontsize=12)
    plt.ylabel('y', fontsize=12)
    plt.grid(True)
    plt.legend(fontsize=11)
    plt.savefig(os.path.join(doc_dir, "plot.png"), dpi=300)
    plt.close()

    # 2. Импульсное воздействие -> plot2.png
    _, _, y_imp = simulate('impulse')
    plt.figure(figsize=(8, 6))
    plt.plot(tau, y_imp, label='y(t) (импульсное)', color='tab:orange', linewidth=1.5)
    plt.title(f"{title_text}\n(Импульсное воздействие)", fontsize=13)
    plt.xlabel('τ', fontsize=12)
    plt.ylabel('y', fontsize=12)
    plt.grid(True)
    plt.legend(fontsize=11)
    plt.savefig(os.path.join(doc_dir, "plot2.png"), dpi=300)
    plt.close()

    # 3. Гармоническое воздействие -> plot3.png
    # Сделаем чуть больше шагов для красивой синусоиды, если нужно
    tau_harm = np.arange(0, 25, 1)
    _, _, y_harm = simulate('harmonic', steps=len(tau_harm))
    plt.figure(figsize=(8, 6))
    plt.plot(tau_harm, y_harm, label='y(t) (гармоническое)', color='tab:green', linewidth=1.5)
    plt.title(f"{title_text}\n(Гармоническое воздействие)", fontsize=13)
    plt.xlabel('τ', fontsize=12)
    plt.ylabel('y', fontsize=12)
    plt.grid(True)
    plt.legend(fontsize=11)
    plt.savefig(os.path.join(doc_dir, "plot3.png"), dpi=300)
    plt.close()

    print("[УСПЕХ] Все 3 уникальных графика успешно сгенерированы!")

if __name__ == "__main__":
    generate_plots()