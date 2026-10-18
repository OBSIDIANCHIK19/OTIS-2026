#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <memory>
#include "InputSignal.h"
#include "Model1_8.h"
#include "Model2_10.h"
#include "Model3_2.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    // Установка кодировки UTF-8 для консоли Windows
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    #endif

    // Настройка вывода с фиксированной точкой для аккуратных чисел
    std::cout << std::fixed << std::setprecision(6);

    std::cout << "=========================================\n";
    std::cout << " OTIS-2026 | Лабораторная работа №1\n";
    std::cout << " Вариант 8\n";
    std::cout << "=========================================\n\n";

    std::cout << "Выберите модель:\n";
    std::cout << "1 - Model 1.8 (Generalized Autoregressive Linear Model)[cite: 1]\n";
    std::cout << "2 - Model 2.10 (Hyperbolic Tangent Smoothing)[cite: 2]\n";
    std::cout << "3 - Model 3.2 (Pure Constant Input Drive)[cite: 3]\n";
    std::cout << "Ваш выбор: ";
    
    int choice = 0;
    std::cin >> choice;

    std::unique_ptr<Model> model;
    
    // Переменные для параметров
    double a1 = 0.0;
    double a2 = 0.0;
    double b1 = 0.0;
    double b2 = 0.0;
    double a_val = 0.0;
    double b_val = 0.0;

    if (choice == 1) {
        std::cout << "\nВведите коэффициенты a1, a2, b1, b2 через пробел: ";
        std::cin >> a1 >> a2 >> b1 >> b2;
        model = std::make_unique<Model1_8>(a1, a2, b1, b2);
    } else if (choice == 2) {
        std::cout << "\nВведите коэффициенты a, b через пробел: ";
        std::cin >> a_val >> b_val;
        model = std::make_unique<Model2_10>(a_val, b_val);
    } else {
        std::cout << "\nВведите коэффициент b: ";
        std::cin >> b_val;
        model = std::make_unique<Model3_2>(b_val);
    }

    std::cout << "\nТип входного воздействия:\n";
    std::cout << "1 - ступенчатое\n";
    std::cout << "2 - импульсное\n";
    std::cout << "3 - гармоническое\n";
    std::cout << "Ваш выбор: ";
    
    int sigChoice = 0;
    std::cin >> sigChoice;
    
    InputType inputType = InputType::Step;
    if (sigChoice == 2) {
        inputType = InputType::Impulse;
    } else if (sigChoice == 3) {
        inputType = InputType::Harmonic;
    }

    double amplitude = 5.0;
    int steps = 10;
    double y0 = 0.0;

    std::cout << "\nАмплитуда А = " << amplitude << "\n";
    std::cout << "Количество шагов n = " << steps << "\n";
    std::cout << "Начальное значение у0 = " << y0 << "\n\n";

    std::cout << "Модель: " << model->getName() << "\n\n";

    std::cout << "      tau                 u                 y\n";
    std::cout << "---------------------------------------------\n";

    std::vector<double> tau_vec;
    std::vector<double> u_vec;
    std::vector<double> y_vec;

    double current_y = y0;
    double u_prev1 = 0.0;
    double u_prev2 = 0.0;

    for (int t = 0; t <= steps; ++t) {
        double current_u = InputSignal::getSignal(inputType, t);
        if (t > 0) {
            current_y = model->calculateStep(current_u, u_prev1, u_prev2);
        }
        u_prev2 = u_prev1;
        u_prev1 = current_u;

        tau_vec.push_back(t);
        u_vec.push_back(current_u);
        y_vec.push_back(current_y);

        std::cout << std::setw(9) << static_cast<double>(t) << "    " 
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