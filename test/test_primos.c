#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "primos.h"

#define CANT_PRIMOS 25
#define LARGO_HASH  32

/*
 * Objetivo: Determinar si un numero es primo (referencia independiente de la tabla).
 * Entrada : n (numero a evaluar).
 * Salida  : 1 si es primo, 0 en caso contrario.
 */
static int es_primo(int n) {
    int d;
    if (n < 2) return 0;
    for (d = 2; d * d <= n; d++) {
        if (n % d == 0) return 0;
    }
    return 1;
}

/*
 * Objetivo: Validar que ambas tablas devuelven primos menores a 100 de forma estable.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_primos_valores(void) {
    unsigned int n;

    printf("Testeando get_primoA() y get_primoB()...\n");

    for (n = 0; n < CANT_PRIMOS; n++) {
        int a = get_primoA(n);
        int b = get_primoB(n);

        assert(a > 1 && a < 100);
        assert(b > 1 && b < 100);
        assert(es_primo(a));
        assert(es_primo(b));

        /* Deterministas: la misma entrada devuelve siempre el mismo primo */
        assert(get_primoA(n) == a);
        assert(get_primoB(n) == b);
    }

    /* La lista A esta ordenada de forma ascendente */
    for (n = 1; n < CANT_PRIMOS; n++) {
        assert(get_primoA(n) > get_primoA(n - 1));
    }

    printf("  [OK] Las tablas devuelven primos validos y estables.\n");
}

/*
 * Objetivo: Validar que las tablas son biyectivas entre si (misma coleccion, otro orden).
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_primos_permutacion(void) {
    unsigned int i;
    unsigned int j;
    int encontrados = 0;
    int distintos = 0;

    printf("Testeando la relacion entre las dos tablas de primos...\n");

    for (i = 0; i < CANT_PRIMOS; i++) {
        int visto = 0;
        for (j = 0; j < CANT_PRIMOS; j++) {
            if (get_primoB(j) == get_primoA(i)) visto = 1;
        }
        if (visto) encontrados++;
        if (get_primoA(i) != get_primoB(i)) distintos++;
    }

    /* Todos los primos de A estan en B */
    assert(encontrados == CANT_PRIMOS);
    /* Pero el orden es diferente en la mayoria de los indices */
    assert(distintos > CANT_PRIMOS / 2);

    printf("  [OK] B es una permutacion de A con orden distinto.\n");
}

/*
 * Objetivo: Validar el ciclado modulo 25 de los indices, incluidos valores grandes.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_primos_ciclado(void) {
    unsigned int n;

    printf("Testeando el ciclado de indices...\n");

    for (n = 0; n < CANT_PRIMOS; n++) {
        assert(get_primoA(n + CANT_PRIMOS) == get_primoA(n));
        assert(get_primoB(n + CANT_PRIMOS) == get_primoB(n));
        assert(get_primoA(n + (CANT_PRIMOS * 100)) == get_primoA(n));
        assert(get_primoB(n + (CANT_PRIMOS * 100)) == get_primoB(n));
    }

    /* Valores extremos no deben salirse de la tabla */
    assert(get_primoA(4294967295u) > 1);
    assert(get_primoB(4294967295u) > 1);

    printf("  [OK] Los indices ciclan correctamente sobre las tablas.\n");
}

/*
 * Objetivo: Validar el hash determinista: longitud, terminador, rango imprimible
 *           y sensibilidad a la entrada.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_hash_determinista(void) {
    char salida1[LARGO_HASH + 1];
    char salida2[LARGO_HASH + 1];
    char salida3[LARGO_HASH + 1];
    char corto[2];
    int i;
    int diferencias = 0;

    printf("Testeando get_deterministic_hash()...\n");

    assert(get_deterministic_hash("clave", LARGO_HASH, salida1) == salida1);
    get_deterministic_hash("clave", LARGO_HASH, salida2);

    /* Determinismo: la misma entrada produce la misma salida */
    assert(strcmp(salida1, salida2) == 0);
    assert(strlen(salida1) == (size_t)LARGO_HASH);

    /* Todos los caracteres estan en el rango ASCII imprimible ('!' a '~') */
    for (i = 0; i < LARGO_HASH; i++) {
        assert(salida1[i] >= 33 && salida1[i] <= 126);
    }

    /* Sensibilidad: un cambio minimo en la entrada cambia la salida */
    get_deterministic_hash("clavf", LARGO_HASH, salida3);
    for (i = 0; i < LARGO_HASH; i++) {
        if (salida1[i] != salida3[i]) diferencias++;
    }
    assert(diferencias > 0);

    /* Cadena vacia y longitud minima siguen siendo validas */
    get_deterministic_hash("", LARGO_HASH, salida2);
    assert(strlen(salida2) == (size_t)LARGO_HASH);
    get_deterministic_hash("clave", 1, corto);
    assert(strlen(corto) == 1);
    assert(corto[0] == salida1[0]);

    printf("  [OK] get_deterministic_hash() es estable y sensible a la entrada.\n");
}

/*
 * Objetivo: Validar la generacion de cadenas aleatorias imprimibles.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_random_string(void) {
    char salida[LARGO_HASH + 1];
    char otra[LARGO_HASH + 1];
    int i;
    int diferencias = 0;

    printf("Testeando get_random_string()...\n");

    srand(1234);

    assert(get_random_string(LARGO_HASH, salida) == salida);
    assert(strlen(salida) == (size_t)LARGO_HASH);
    for (i = 0; i < LARGO_HASH; i++) {
        assert(salida[i] >= 33 && salida[i] <= 126);
    }

    /* Dos llamadas consecutivas no deberian generar la misma cadena */
    get_random_string(LARGO_HASH, otra);
    for (i = 0; i < LARGO_HASH; i++) {
        if (salida[i] != otra[i]) diferencias++;
    }
    assert(diferencias > 0);

    /* Longitud cero: solo el terminador */
    get_random_string(0, salida);
    assert(salida[0] == '\0');

    printf("  [OK] get_random_string() genera cadenas validas.\n");
}

/*
 * Objetivo: Validar que get_random_byte() cubre el rango de un byte y varia.
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_random_byte(void) {
    int vistos[256];
    int i;
    int distintos = 0;

    printf("Testeando get_random_byte()...\n");

    memset(vistos, 0, sizeof(vistos));
    srand(4321);

    for (i = 0; i < 4096; i++) {
        unsigned char b = get_random_byte();
        if (!vistos[b]) {
            vistos[b] = 1;
            distintos++;
        }
    }

    /* Con 4096 muestras se espera cubrir gran parte del rango 0-255 */
    assert(distintos > 200);

    printf("  [OK] get_random_byte() genero %d valores distintos.\n", distintos);
}

int main(void) {
    printf("========================================\n");
    printf(" SUITE DE PRUEBAS: MODULO PRIMOS\n");
    printf("========================================\n\n");

    test_primos_valores();
    test_primos_permutacion();
    test_primos_ciclado();
    test_hash_determinista();
    test_random_string();
    test_random_byte();

    printf("\n========================================\n");
    printf(" Todas las pruebas finalizaron con exito.\n");
    printf("========================================\n");
    return 0;
}
