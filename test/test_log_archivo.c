#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Log.h"

/*
 * Objetivo: Leer todo el contenido del log en un buffer terminado en '\0'.
 * Entrada : buffer (destino), tam (tamano del destino).
 * Salida  : Cantidad de bytes leidos.
 */
static size_t leer_log(char* buffer, size_t tam) {
    size_t leidos = 0;
    FILE* f = fopen(MTH_LOG_PATH, "r");

    assert(f != NULL);
    leidos = fread(buffer, 1, tam - 1, f);
    buffer[leidos] = '\0';
    fclose(f);

    return leidos;
}

/*
 * Objetivo: Validar que LOG() escribe el mensaje y sus metadatos en el archivo.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_escritura_y_metadatos(void) {
    char contenido[4096];

    printf("Testeando la escritura del log...\n");

    remove(MTH_LOG_PATH);

    LOG("Mensaje simple");
    LOG("Mensaje con enteros %d y %d", 42, -7);
    LOG("Mensaje con texto %s", "interpolado");

    /* fflush() interno: el contenido debe estar en disco sin cerrar el log */
    leer_log(contenido, sizeof(contenido));

    assert(strstr(contenido, "Mensaje simple") != NULL);
    assert(strstr(contenido, "Mensaje con enteros 42 y -7") != NULL);
    assert(strstr(contenido, "Mensaje con texto interpolado") != NULL);

    /* Metadatos: nombre del archivo (sin la ruta) y funcion invocante */
    assert(strstr(contenido, "test_log_") != NULL);
    assert(strstr(contenido, "test_escritu") != NULL);
    assert(strchr(contenido, '[') != NULL);

    printf("  [OK] El log contiene los mensajes y sus metadatos.\n");
}

/*
 * Objetivo: Validar que cada invocacion de LOG() agrega exactamente una linea.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_una_linea_por_mensaje(void) {
    char contenido[4096];
    size_t i;
    size_t leidos;
    int lineas = 0;

    printf("Testeando el formato de una linea por mensaje...\n");

    close_log();
    remove(MTH_LOG_PATH);

    LOG("Linea 1");
    LOG("Linea 2");
    LOG("Linea 3");

    leidos = leer_log(contenido, sizeof(contenido));
    for (i = 0; i < leidos; i++) {
        if (contenido[i] == '\n') lineas++;
    }

    assert(lineas == 3);
    printf("  [OK] Se escribieron %d lineas para 3 mensajes.\n", lineas);
}

/*
 * Objetivo: Validar close_log() y la reapertura automatica del log.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_cierre_y_reapertura(void) {
    char contenido[4096];

    printf("Testeando close_log() y la reapertura del log...\n");

    close_log();
    /* Cerrar dos veces debe ser seguro (idempotente) */
    close_log();

    remove(MTH_LOG_PATH);

    /* La proxima escritura reabre el archivo automaticamente */
    LOG("Mensaje posterior al cierre");
    leer_log(contenido, sizeof(contenido));
    assert(strstr(contenido, "Mensaje posterior al cierre") != NULL);

    close_log();
    remove(MTH_LOG_PATH);

    printf("  [OK] El log se cierra y se reabre correctamente.\n");
}

int main(void) {
    printf("========================================\n");
    printf(" SUITE DE PRUEBAS: MODULO LOG\n");
    printf("========================================\n\n");

    test_escritura_y_metadatos();
    test_una_linea_por_mensaje();
    test_cierre_y_reapertura();

    printf("\n========================================\n");
    printf(" Todas las pruebas finalizaron con exito.\n");
    printf("========================================\n");
    return 0;
}
