# 1. Versión mínima requerida de CMake (apta para máquinas viejas y nuevas)
cmake_minimum_required(VERSION 3.10)

# 2. Nombre del proyecto y lenguaje (C)
project(Compresor LANGUAGES C)

# 3. Forzar el uso estricto de ANSI C (C89 / C90)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# 4. Decirle a CMake dónde buscar los archivos de cabecera (.h)
include_directories(include)

# 5. Buscar automáticamente todos los archivos fuente (.c) dentro de src/
file(GLOB SOURCES "src/*.c")

# 6. Definir el nombre del ejecutable final y sus fuentes
add_executable(Compresor ${SOURCES})
