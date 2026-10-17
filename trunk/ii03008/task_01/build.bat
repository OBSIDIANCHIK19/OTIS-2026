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