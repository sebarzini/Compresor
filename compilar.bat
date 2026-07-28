@echo off
rem Crear carpeta build, configurar y compilar en Windows
cmake -B build -S .
cmake --build build
pause
