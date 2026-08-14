#include <assert.h>
#include "archivo.h"

#define RUTA_TMP "tmp_test_archivo.bin"
#define RUTA_INEXISTENTE "tmp_test_archivo_no_existe.bin"

static const byte DATOS[] = { 0x00, 0x41, 0xFF, 0x10, 0x7E };
static const size_t DATOS_LEN = sizeof(DATOS);

/*
 * Objetivo: Validar la apertura de archivos en modo escritura y lectura.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_abrir_archivo(void) {
    FILE* archivo;

    printf("Testeando abrir_archivo()...\n");

    /* Ruta nula: no debe intentar abrir nada */
    assert(abrir_archivo(NULL, 1) == NULL);
    assert(abrir_archivo(NULL, 0) == NULL);

    /* Apertura para escritura: crea el archivo */
    archivo = abrir_archivo(RUTA_TMP, 1);
    assert(archivo != NULL);
    fclose(archivo);

    /* Apertura para lectura de un archivo existente */
    archivo = abrir_archivo(RUTA_TMP, 0);
    assert(archivo != NULL);
    fclose(archivo);

    /* Apertura para lectura de un archivo inexistente */
    remove(RUTA_INEXISTENTE);
    assert(abrir_archivo(RUTA_INEXISTENTE, 0) == NULL);

    remove(RUTA_TMP);
    printf("  [OK] abrir_archivo() supero las pruebas.\n");
}

/*
 * Objetivo: Validar la escritura de un buffer y su posterior lectura completa.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_escribir_y_leer(void) {
    FILE* archivo;
    byte* leido;
    size_t bytes_read = 123; /* valor inicial arbitrario: debe ser sobrescrito */

    printf("Testeando escribir_file() y leer_file()...\n");

    archivo = abrir_archivo(RUTA_TMP, 1);
    assert(archivo != NULL);
    escribir_file(archivo, (byte*)DATOS, DATOS_LEN);
    fclose(archivo);

    archivo = abrir_archivo(RUTA_TMP, 0);
    assert(archivo != NULL);
    leido = leer_file(archivo, &bytes_read, DATOS_LEN);
    assert(leido != NULL);
    assert(bytes_read == DATOS_LEN);
    assert(memcmp(leido, DATOS, DATOS_LEN) == 0);
    free(leido);
    fclose(archivo);

    printf("  [OK] Los %zu bytes escritos se recuperaron sin cambios.\n", DATOS_LEN);
}

/*
 * Objetivo: Validar que escribir_file() ignora parametros invalidos sin fallar.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_escribir_parametros_invalidos(void) {
    FILE* archivo;
    long tam;

    printf("Testeando escribir_file() con parametros invalidos...\n");

    /* Archivo nulo o buffer nulo: no debe escribir ni fallar */
    escribir_file(NULL, (byte*)DATOS, DATOS_LEN);
    escribir_file(NULL, NULL, 0);

    archivo = abrir_archivo(RUTA_TMP, 1);
    assert(archivo != NULL);
    escribir_file(archivo, NULL, DATOS_LEN);
    escribir_file(archivo, (byte*)DATOS, 0);
    fclose(archivo);

    /* El archivo debe haber quedado vacio */
    archivo = abrir_archivo(RUTA_TMP, 0);
    assert(archivo != NULL);
    assert(fseek(archivo, 0, SEEK_END) == 0);
    tam = ftell(archivo);
    fclose(archivo);
    assert(tam == 0);

    remove(RUTA_TMP);
    printf("  [OK] escribir_file() ignoro los parametros invalidos.\n");
}

/*
 * Objetivo: Validar el calculo dinamico de bytes restantes de leer_file() (len == 0)
 *           y el respeto de la posicion actual del descriptor.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_leer_file_dinamico(void) {
    FILE* archivo;
    byte* leido;
    size_t bytes_read = 0;

    printf("Testeando leer_file() con longitud dinamica...\n");

    archivo = abrir_archivo(RUTA_TMP, 1);
    assert(archivo != NULL);
    escribir_file(archivo, (byte*)DATOS, DATOS_LEN);
    fclose(archivo);

    /* len == 0: lee hasta el final del archivo */
    archivo = abrir_archivo(RUTA_TMP, 0);
    assert(archivo != NULL);
    leido = leer_file(archivo, &bytes_read, 0);
    assert(leido != NULL);
    assert(bytes_read == DATOS_LEN);
    assert(memcmp(leido, DATOS, DATOS_LEN) == 0);
    free(leido);
    fclose(archivo);

    /* len == 0 desde una posicion intermedia: solo los bytes restantes */
    archivo = abrir_archivo(RUTA_TMP, 0);
    assert(archivo != NULL);
    assert(fseek(archivo, 2, SEEK_SET) == 0);
    leido = leer_file(archivo, &bytes_read, 0);
    assert(leido != NULL);
    assert(bytes_read == DATOS_LEN - 2);
    assert(memcmp(leido, DATOS + 2, DATOS_LEN - 2) == 0);
    free(leido);
    fclose(archivo);

    /* len == 0 al final del archivo: no hay nada que leer */
    archivo = abrir_archivo(RUTA_TMP, 0);
    assert(archivo != NULL);
    assert(fseek(archivo, 0, SEEK_END) == 0);
    bytes_read = 99;
    assert(leer_file(archivo, &bytes_read, 0) == NULL);
    assert(bytes_read == 0);
    fclose(archivo);

    printf("  [OK] leer_file() calculo correctamente los bytes restantes.\n");
}

/*
 * Objetivo: Validar los casos limite de leer_file().
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_leer_file_casos_limite(void) {
    FILE* archivo;
    byte* leido;
    size_t bytes_read = 77;

    printf("Testeando leer_file() en casos limite...\n");

    /* Archivo nulo: devuelve NULL y deja el contador en cero */
    assert(leer_file(NULL, &bytes_read, DATOS_LEN) == NULL);
    assert(bytes_read == 0);
    assert(leer_file(NULL, NULL, DATOS_LEN) == NULL);

    /* Pedir mas bytes de los disponibles: devuelve lo que hay */
    archivo = abrir_archivo(RUTA_TMP, 0);
    assert(archivo != NULL);
    leido = leer_file(archivo, &bytes_read, DATOS_LEN + 10);
    assert(leido != NULL);
    assert(bytes_read == DATOS_LEN);
    assert(memcmp(leido, DATOS, DATOS_LEN) == 0);
    free(leido);
    fclose(archivo);

    /* Sin contador de salida: la lectura sigue siendo valida */
    archivo = abrir_archivo(RUTA_TMP, 0);
    assert(archivo != NULL);
    leido = leer_file(archivo, NULL, DATOS_LEN);
    assert(leido != NULL);
    assert(memcmp(leido, DATOS, DATOS_LEN) == 0);
    free(leido);
    fclose(archivo);

    remove(RUTA_TMP);
    printf("  [OK] leer_file() manejo los casos limite.\n");
}

/*
 * Objetivo: Validar la deteccion de existencia de archivos regulares.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_existe_archivo(void) {
    FILE* archivo;

    printf("Testeando existe_archivo()...\n");

    assert(existe_archivo(NULL) == 0);

    remove(RUTA_TMP);
    assert(existe_archivo(RUTA_TMP) == 0);

    archivo = abrir_archivo(RUTA_TMP, 1);
    assert(archivo != NULL);
    escribir_file(archivo, (byte*)DATOS, DATOS_LEN);
    fclose(archivo);
    assert(existe_archivo(RUTA_TMP) == 1);

    /* Un directorio no cuenta como archivo */
    assert(existe_archivo(".") == 0);

    remove(RUTA_TMP);
    assert(existe_archivo(RUTA_TMP) == 0);

    printf("  [OK] existe_archivo() supero las pruebas.\n");
}

int main(void) {
    printf("========================================\n");
    printf(" SUITE DE PRUEBAS: MODULO ARCHIVO\n");
    printf("========================================\n\n");

    test_abrir_archivo();
    test_escribir_y_leer();
    test_escribir_parametros_invalidos();
    test_leer_file_dinamico();
    test_leer_file_casos_limite();
    test_existe_archivo();

    /*
     * NOTA: cerrar_archivo() no se ejerce aqui porque su implementacion actual
     * invoca fclose() cuando el puntero es NULL (condicion invertida), lo que
     * provoca comportamiento indefinido. Ver la descripcion del Pull Request.
     */

    printf("\n========================================\n");
    printf(" Todas las pruebas finalizaron con exito.\n");
    printf("========================================\n");
    return 0;
}
