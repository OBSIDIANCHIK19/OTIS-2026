@echo off
chcp 65001 > nul
setlocal
cd /d "%~dp0"

if not exist "CMakeLists.txt" (
    echo [ERROR] CMakeLists.txt not found in:
    echo %CD%
    pause
    exit /b 1
)

echo [1/2] Configuring project...
cmake -S . -B build -Wno-dev
if errorlevel 1 goto error

echo.
echo [2/2] Building project...
cmake --build build --config Release
if errorlevel 1 goto error

echo.
echo Build completed successfully.

if exist "build\Release\LabWork1.exe" (
    "build\Release\LabWork1.exe"
) else if exist "build\LabWork1.exe" (
    "build\LabWork1.exe"
) else (
    echo [WARNING] LabWork1.exe was not found.
)

if exist "plot_generator.py" (
    echo.
    echo Generating plots...
    python plot_generator.py
)

pause
exit /b 0

:error
echo.
echo [ERROR] Build failed. Read the error above.
pause
exit /b 1