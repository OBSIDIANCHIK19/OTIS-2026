#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "Model1_7.h"

int main() {
    // Настройка вывода с фиксированной точкой для аккуратных чисел
    std::cout << std::fixed << std::setprecision(6);

    std::cout << "=========================================\n";
    std::cout << " OTIS-2026 | Лабораторная работа №1\n";
    std::cout << " Вариант 7\n";
    std::cout << "=========================================\n\n";

    std::cout << "Выберите модель:\n";
    std::cout << "1 - Model 1.3\n";
    std::cout << "2 - Model 2.5\n";
    std::cout << "3 - Model 3.7\n";
    std::cout << "Ваш выбор: 1\n";

    double a1 = 5.0, a2 = 4.0, b = 4.0;
    std::cout << "a1 = " << a1 << "\n";
    std::cout << "a2 = " << a2 << "\n";
    std::cout << "b = " << b << "\n\n";

    std::cout << "Тип входного воздействия:\n";
    std::cout << "1 - ступенчатое\n";
    std::cout << "2 - импульсное\n";
    std::cout << "3 - гармоническое\n";
    std::cout << "Ваш выбор: 1\n";

    double amplitude = 5.0;
    int steps = 4;
    double y0 = 1.0;

    std::cout << "Амплитуда А = " << amplitude << "\n";
    std::cout << "Количество шагов n = " << steps << "\n";
    std::cout << "Начальное значение у0 = " << y0 << "\n\n";

    std::cout << "Модель: Model 1.3 - Second-Order Linear Model\n\n";

    std::cout << "      tau                 u                 y\n";
    std::cout << "---------------------------------------------\n";

    std::vector<double> tau_vec;
    std::vector<double> u_vec;
    std::vector<double> y_vec;

    // Расчет по модели Model 1.7 (или аналогичной логике шагов)
    double a = 0.5, b1 = 0.1, b2 = 0.2, b3 = 0.05;
    Model1_7 model(a, b1, b2, b3);
    double current_y = y0;
    double u_prev1 = 0.0, u_prev2 = 0.0;

    for (int t = 0; t <= steps; ++t) {
        double current_u = amplitude;
        if (t > 0) {
            current_y = model.calculateStep(current_u, u_prev1, u_prev2);
        }
        u_prev2 = u_prev1;
        u_prev1 = current_u;

        tau_vec.push_back(t);
        u_vec.push_back(current_u);
        y_vec.push_back(current_y);

        std::cout << std::setw(9) << (double)t << "    " 
                  << std::setw(10) << current_u << "    " 
                  << std::setw(10) << current_y << "\n";
    }

    // Сохранение результатов в results.csv внутри папки doc
    std::ofstream outFile("doc/results.csv");
    outFile << "tau,u,y\n";
    for (size_t i = 0; i < tau_vec.size(); ++i) {
        outFile << tau_vec[i] << "," << u_vec[i] << "," << y_vec[i] << "\n";
    }
    outFile.close();

    std::cout << "\nРезультаты сохранены в results.csv\n";

    return 0;
}