cmake_minimum_required(VERSION 3.15)

# Buscar todos los archivos de prueba (.c) en la carpeta test
file(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

foreach(TEST_FILE ${TEST_FILES})
    # Obtener el nombre del archivo sin extensión (ej: test_hash)
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    
    # Crear el ejecutable de la prueba solo con su archivo de test
    add_executable(${TEST_NAME} ${TEST_FILE})
    
    # Vincular la librería estática (aporta todas las funciones de src/ y la carpeta include/)
    target_link_libraries(${TEST_NAME} PRIVATE compilador_lib)
endforeach()