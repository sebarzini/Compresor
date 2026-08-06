@echo off
setlocal enabledelayedexpansion

echo ===========================================
echo  Compilando Compresor/Encriptador (Windows)
echo ===========================================

:: 1. Buscar GCC en las rutas habituales de Dev-C++ y Code::Blocks
set "COMPILER_PATH="

if exist "C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\gcc.exe" (
    set "COMPILER_PATH=C:\Program Files (x86)\Dev-Cpp\MinGW64\bin"
) else if exist "C:\Dev-Cpp\MinGW64\bin\gcc.exe" (
    set "COMPILER_PATH=C:\Dev-Cpp\MinGW64\bin"
) else if exist "C:\Program Files\CodeBlocks\MinGW\bin\gcc.exe" (
    set "COMPILER_PATH=C:\Program Files\CodeBlocks\MinGW\bin"
) else if exist "C:\Program Files (x86)\CodeBlocks\MinGW\bin\gcc.exe" (
    set "COMPILER_PATH=C:\Program Files (x86)\CodeBlocks\MinGW\bin"
)

:: 2. Si se encontro el compilador de Dev-C++ o Code::Blocks, agregarlo temporalmente al PATH
if defined COMPILER_PATH (
    echo [INFO] Compilador detectado en: !COMPILER_PATH!
    set "PATH=!COMPILER_PATH!;%PATH%"
) else (
    echo [INFO] Buscando GCC/MinGW en el PATH global del sistema...
)

:: 3. Configurar CMake usando MinGW Makefiles
cmake -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] No se pudo configurar CMake con MinGW.
    echo Revisa si Dev-C++ o Code::Blocks estan instalados en una ruta no predeterminada.
    pause
    exit /b %ERRORLEVEL%
)

:: 4. Compilar
cmake --build build

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] Fallo el proceso de compilacion.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo ===========================================
echo [OK] Compilacion completada con exito.
echo El ejecutable esta en: build/
echo ===========================================
pause