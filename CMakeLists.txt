cmake_minimum_required(VERSION 3.10)
project(compresor LANGUAGES C)

# 1. Forzar estándar ANSI C (C90)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# 2. CONFIGURACIÓN CRUCIAL: Forzar Símbolos de Depuración (-g)
# Al fijar esto en 'Debug', CMake añade automáticamente las banderas necesarias
# para que GDB y Valgrind puedan leer el programa línea por línea.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Opciones específicas para compiladores basados en GCC/Clang (Linux, Mac, MinGW en Windows)
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    # -g: Genera símbolos detallados para GDB
    # -O0: Apaga optimizaciones para que el código binario coincida exacto con tus líneas de texto
    add_compile_options(-g -O0)
endif()

# 3. Directorio de cabeceras (.h)
include_directories(include)

# 4. Compilar la aplicación principal
file(GLOB_RECURSE MAIN_SOURCES "src/*.c")
add_executable(compresor ${MAIN_SOURCES})
