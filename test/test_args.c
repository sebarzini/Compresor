#include <assert.h>
#include <string.h>
#include "main.h"

/*
 * Objetivo: Construir una configuracion con los valores por defecto de main().
 * Entrada : Ninguna.
 * Salida  : Configuracion inicial.
 */
static t_config config_por_defecto(void) {
    t_config cfg = { MODO_NINGUNO, 4, NULL, NULL, NULL };
    return cfg;
}

/*
 * Objetivo: Validar que sin argumentos la configuracion queda intacta.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_sin_argumentos(void) {
    char* argv[] = { "compresor", NULL };
    t_config cfg = config_por_defecto();

    printf("Testeando parse() sin argumentos...\n");

    parse(1, argv, &cfg);

    assert(cfg.modo == MODO_NINGUNO);
    assert(cfg.n_bits == 4);
    assert(cfg.password == NULL);
    assert(cfg.file_in == NULL);
    assert(cfg.file_out == NULL);

    printf("  [OK] Se conservaron los valores por defecto.\n");
}

/*
 * Objetivo: Validar el reconocimiento de cada modo de operacion.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_modos(void) {
    char* argv_c[] = { "compresor", "-c", NULL };
    char* argv_d[] = { "compresor", "-d", NULL };
    char* argv_h[] = { "compresor", "-h", NULL };
    char* argv_a[] = { "compresor", "-a", NULL };
    t_config cfg;

    printf("Testeando parse() con cada modo...\n");

    cfg = config_por_defecto();
    parse(2, argv_c, &cfg);
    assert(cfg.modo == MODO_COMPRIMIR);

    cfg = config_por_defecto();
    parse(2, argv_d, &cfg);
    assert(cfg.modo == MODO_DESCOMPRIMIR);

    cfg = config_por_defecto();
    parse(2, argv_h, &cfg);
    assert(cfg.modo == MODO_AYUDA);

    cfg = config_por_defecto();
    parse(2, argv_a, &cfg);
    assert(cfg.modo == MODO_ABOUT);

    printf("  [OK] Los cuatro modos se reconocieron correctamente.\n");
}

/*
 * Objetivo: Validar el parseo de las opciones con valor asociado.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_opciones_con_valor(void) {
    char* argv[] = { "compresor", "-c", "-i", "entrada.txt", "-o", "salida.mzi",
                     "-n", "8", "-p", "clave secreta", NULL };
    t_config cfg = config_por_defecto();

    printf("Testeando parse() con opciones y valores...\n");

    parse(10, argv, &cfg);

    assert(cfg.modo == MODO_COMPRIMIR);
    assert(strcmp(cfg.file_in, "entrada.txt") == 0);
    assert(strcmp(cfg.file_out, "salida.mzi") == 0);
    assert(cfg.n_bits == 8);
    assert(strcmp(cfg.password, "clave secreta") == 0);

    printf("  [OK] Todas las opciones se asignaron correctamente.\n");
}

/*
 * Objetivo: Validar que el ultimo modo indicado gana y que las opciones
 *           repetidas sobrescriben el valor anterior.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_argumentos_repetidos(void) {
    char* argv[] = { "compresor", "-c", "-d", "-i", "primero.txt", "-i", "segundo.txt", NULL };
    t_config cfg = config_por_defecto();

    printf("Testeando parse() con argumentos repetidos...\n");

    parse(7, argv, &cfg);

    assert(cfg.modo == MODO_DESCOMPRIMIR);
    assert(strcmp(cfg.file_in, "segundo.txt") == 0);

    printf("  [OK] Prevalecio el ultimo valor indicado.\n");
}

/*
 * Objetivo: Validar que se ignoran las opciones desconocidas y los argumentos
 *           sueltos sin guion.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_argumentos_ignorados(void) {
    char* argv[] = { "compresor", "sinGuion", "-z", "-c", "otroSuelto", NULL };
    t_config cfg = config_por_defecto();

    printf("Testeando parse() con argumentos no reconocidos...\n");

    parse(5, argv, &cfg);

    assert(cfg.modo == MODO_COMPRIMIR);
    assert(cfg.file_in == NULL);
    assert(cfg.file_out == NULL);
    assert(cfg.n_bits == 4);

    printf("  [OK] Los argumentos no reconocidos se ignoraron.\n");
}

/*
 * Objetivo: Validar que solo se evalua la primera letra de cada opcion y que
 *           -n con un valor no numerico resulta en cero.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_formas_alternativas(void) {
    char* argv[] = { "compresor", "-comprimir", "-n", "abc", NULL };
    t_config cfg = config_por_defecto();

    printf("Testeando parse() con formas alternativas de las opciones...\n");

    parse(4, argv, &cfg);

    assert(cfg.modo == MODO_COMPRIMIR);
    assert(cfg.n_bits == 0);

    printf("  [OK] Se evaluo la primera letra y atoi() devolvio 0.\n");
}

int main(void) {
    printf("========================================\n");
    printf(" SUITE DE PRUEBAS: PARSEO DE ARGUMENTOS\n");
    printf("========================================\n\n");

    test_sin_argumentos();
    test_modos();
    test_opciones_con_valor();
    test_argumentos_repetidos();
    test_argumentos_ignorados();
    test_formas_alternativas();

    close_log();

    printf("\n========================================\n");
    printf(" Todas las pruebas finalizaron con exito.\n");
    printf("========================================\n");
    return 0;
}
