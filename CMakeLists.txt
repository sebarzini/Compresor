cmake_minimum_required(VERSION 3.15)
project(Compilador_C C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Elige el tipo de construccion" FORCE)
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wformat=2 -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-strong")
    set(CMAKE_C_FLAGS_DEBUG "-g -O1")
elseif(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /sdl /GS")
    set(CMAKE_C_FLAGS_DEBUG "/Zi /Od")
endif()

# Obtener los fuentes de la lógica con rutas absolutas
file(GLOB COMPILER_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM COMPILER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")

# Crear una librería estática interna con el código de 'src'
add_library(compilador_lib STATIC ${COMPILER_SOURCES})
target_include_directories(compilador_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Las macros de traza solo se habilitan en builds Debug: en Release no deben
# imprimir rutas ni detalles internos.
target_compile_definitions(compilador_lib PUBLIC $<$<CONFIG:Debug>:MODO_DEBUG>)

# Entropia del sistema para el material de clave (BCryptGenRandom en Windows)
if(WIN32)
    target_link_libraries(compilador_lib PUBLIC bcrypt)
endif()

# Ejecutable principal del proyecto
add_executable(mi_compilador src/main.c)
target_link_libraries(mi_compilador PRIVATE compilador_lib)

# Incluir subdirectorio de pruebas
add_subdirectory(test)