cmake_minimum_required(VERSION 3.15)
project(Compilador C)

# Forzar el modo Debug si el usuario no especificó uno (activa -g para GDB)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Elige el tipo de construccion" FORCE)
endif()

# Estándar de C
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Buscar TODOS los archivos fuente de la lógica interna en 'src' (excluyendo main.c)
# Esto nos permite reutilizarlos en las pruebas sin duplicar código
file(GLOB COMPILER_SOURCES "src/*.c")
list(REMOVE_ITEM COMPILER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")

# Hacer que la carpeta 'include' sea visible globalmente para todos los objetivos
include_directories(include)

# Ejecutable principal del compilador
add_executable(mi_compilador src/main.c ${COMPILER_SOURCES})

# Pasar los archivos fuente de la lógica al subdirectorio de pruebas
set(COMPILER_SOURCES ${COMPILER_SOURCES} PARENT_SCOPE)

# Incluir la carpeta de pruebas al proceso de compilación
add_subdirectory(test)
