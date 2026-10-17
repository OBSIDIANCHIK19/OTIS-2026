<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>

<br><br><br><br><br><br><br>

<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>

<br><br><br><br><br>

<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-30</p>
<p align="right">Кулешов Н.С.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д. А.</p>

<br><br><br><br><br>
<p align="center">Брест 2026</p>

---

## Вариант 8
- Обобщенная авторегрессионная линейная модель: **Model 1.8**
- Модель с гиперболическим сглаживанием: **Model 2.10**
- Дифференциальная модель постоянного воздействия: **Model 3.2**

## Математическое описание моделей

### Model 1.8 (Generalized Autoregressive Linear Model)
`y(t+1) = a1*y(t) + a2*y(t-1) + b1*u(t) + b2*u(t-1)`

### Model 2.10 (Hyperbolic Tangent Smoothing)
`y(t+1) = a*tanh(y(t)) + b*pow(u(t), 3)`

### Model 3.2 (Pure Constant Input Drive)
`y(t+1) = y(t) + dt*(b*u(t))`

## Исследуемые входные воздействия $u(\tau)$
1. **Ступенчатое**: `u(tau) = A`
2. **Импульсное**: `u(0) = A, u(tau > 0) = 0`
3. **Гармоническое**: `u(tau) = A * sin(tau)`

## Архитектура программы (ООП)
В основе программы лежит абстрактный класс `Model`, определяющий единый интерфейс расчёта следующего шага симуляции (`calculateStep`).
От абстрактного класса наследуются конкретные классы моделей:
- `Model1_8`
- `Model2_10`
- `Model3_2`

## Функциональные возможности
Разработанное приложение обеспечивает:
- Диалоговый выбор одной из трёх математических моделей;
- Интерактивный ввод коэффициентов уравнения ($a_1, a_2, b_1, b_2, a, b$);
- Настройку параметров симуляции (тип сигнала, количество шагов, начальные условия);
- Лаконичный вывод основных параметров и начальных результатов в консоль;
- Автоматический экспорт полной таблицы результатов в `doc/results.csv`;
- Автоматический запуск построения и отображения графиков переходных процессов средствами Python (`matplotlib`).


## Результат
Программа:
- позволяет выбрать модель;
- принимает заданные пользователем коэффициенты;
- позволяет выбрать тип входного воздействия;
- позволяет задать количество шагов симуляции `n`;
- выводит результаты расчетов в компактном табличном виде в консоль;
- автоматически сохраняет результаты в файл данных для построения графиков;
- строит графики переходных процессов с помощью Python и библиотеки Matplotlib.

## Пример работы программы

### Сборка
На Windows через `build.bat`:

```bat
@echo off
setlocal enabledelayedexpansion

if not exist "%~dp0CMakeLists.txt" (
    echo ERROR CMakeLists.txt not found in this folder
    pause
    exit /b 1
)

cd /d "%~dp0"

REM Конфигурация CMake в тихом режиме (без лишних сообщений)
cmake -S . -B build -W no-dev >nul 2>&1
if errorlevel 1 goto error

REM Компиляция через MSBuild в минималистичном режиме (флаг /v:m - минимальный вывод)
cmake --build build --config Release -- /nologo /v:m
if errorlevel 1 goto error

echo Сборка успешно завершена!
echo.

REM STAGE 3 Execution (Запуск программы)
if exist "build\Release\LabWork1.exe" (
    "build\Release\LabWork1.exe"
) else if exist "build\LabWork1.exe" (
    "build\LabWork1.exe"
)

REM STAGE 4 Generating Plots (если скрипт существует)
if exist "plot_generator.py" (
    python plot_generator.py
)

pause
goto end

:error
echo [ОШИБКА] Сборка прервана с ошибкой.
pause
exit /b 1

:end
endlocal
```

После сборки запускать исполняемый файл из каталога `build`.

### Демонстрация исполняемого файла otis_task_01.exe:

![](work.png)

При запуске исполняемого файла мы получаем результат файл.csv, после чего автоматически запускается plot_generator.py для визуализации ответа:

## Демострация ступенчатого воздействия
![Результат выполнения файла plot_generator.py](plot1.png)
## Демострация импульсного воздействия
![](plot2.png)
## Демострация гармонического воздействия
![](plot3.png)


```mermaid
classDiagram
    class Model {
        <<abstract>>
        +calculateStep(u_current, u_prev1, u_prev2) double
        +getName() string
    }
    class Model1_8 {
        -a1 double
        -a2 double
        -b1 double
        -b2 double
        -y_prev1 double
        -y_prev2 double
        +calculateStep(...) double
    }
    class Model2_10 {
        -a double
        -b double
        -y_prev double
        +calculateStep(...) double
    }
    class Model3_2 {
        -b double
        -y_prev double
        +calculateStep(...) double
    }
    Model <|-- Model1_8
    Model <|-- Model2_10
    Model <|-- Model3_2