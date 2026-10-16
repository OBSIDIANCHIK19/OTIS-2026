@echo off
setlocal
chcp 65001 > nul
cd /d "%~dp0"

if not exist build mkdir build
cd build
cmake .. > nul
cmake --build . --config Release > nul
cd ..

REM Убедимся, что папка doc существует перед запуском
if not exist doc mkdir doc

if exist "build\Release\LabWork1.exe" (
    build\Release\LabWork1.exe
) else if exist "build\LabWork1.exe" (
    LabWork1.exe
)

python src\plot_generator.py

pause
endlocal