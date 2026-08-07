cmake_minimum_required(VERSION 3.15)

# 1. Buscar todos los archivos .c dentro de la carpeta 'test'
file(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

# 2. Iterar sobre la lista para crear un ejecutable por cada test automáticamente
foreach(TEST_FILE ${TEST_FILES})
    # Obtener el nombre del archivo sin la extensión .c (ejemplo: 'test_debug')
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    
    # Crear el binario ejecutable de esta prueba con sus fuentes
    add_executable(${TEST_NAME} ${TEST_FILE} ${COMPILER_SOURCES})

    # IMPORTANTE: Esta línea VA AQUÍ, DESPUÉS de add_executable
    # Asocia la carpeta 'include' directamente al ejecutable que se acaba de crear (${TEST_NAME})
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
endforeach()