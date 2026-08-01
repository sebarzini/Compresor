cmake_minimum_required(VERSION 3.15)

# Lista aquí cada uno de tus archivos de prueba independientes
# Cada uno generará su propio binario ejecutable
set(TEST_FILES "test_debug.c")

# Iterar sobre la lista para crear los ejecutables de prueba automáticamente
foreach(TEST_FILE ${TEST_FILES})
    # Obtener el nombre del archivo sin la extensión .c para usarlo como nombre del binario
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    
    # Crear el binario de prueba usando su propio código fuente y la lógica de 'src'
    add_executable(${TEST_NAME} ${TEST_FILE} ${COMPILER_SOURCES})
endforeach()
