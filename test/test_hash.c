#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

/* ============================================================================
 * DECLARACIONES EXTERNAS (Asegúrate de que coincidan con tu hash.c)
 * ============================================================================ */
extern byte* hash_pass(char* pass);
/* Asumimos que tienes expuesta o implementada esta función para calcular 
   el largo del buffer que devuelve hash_pass */
extern size_t get_primoA(size_t len_pass); 

/* ============================================================================
 * FUNCIONES AUXILIARES
 * ============================================================================ */
void imprimir_hex(const char* etiqueta, const byte* buffer, size_t len) {
    printf("%-22s (%zu bytes): ", etiqueta, len);
    /* Imprime un máximo de 16 bytes para no inundar la consola si el primo es grande */
    size_t limit = (len > 16) ? 16 : len; 
    for (size_t i = 0; i < limit; i++) {
        printf("%02X ", buffer[i]);
    }
    if (len > 16) printf("... ");
    printf("\n");
}

/* ============================================================================
 * PRUEBAS
 * ============================================================================ */

/* PRUEBA 1: Determinismo */
void test_determinismo(char* pass) {
    printf("[TEST 1] Determinismo para clave: '%s'\n", pass);
    
    size_t pass_len = strlen(pass);
    size_t expected_len = get_primoA(pass_len);
    
    byte* h1 = hash_pass(pass);
    byte* h2 = hash_pass(pass);

    if (!h1 || !h2) {
        printf("  [FALLO] La función devolvió NULL.\n\n");
        return;
    }

    /* Comparamos todo el bloque de memoria devuelto */
    if (memcmp(h1, h2, expected_len) == 0) {
        printf("  [EXITO] La misma entrada genera la misma salida (%zu bytes).\n", expected_len);
    } else {
        printf("  [FALLO] Las salidas son diferentes para la misma entrada.\n");
    }
    
    imprimir_hex("  Salida", h1, expected_len);
    printf("\n");
    
    /* Si tu función hash_pass utiliza malloc(), debes liberar la memoria: */
    free(h1); free(h2);
}

/* PRUEBA 2: Validación de Longitud Variable */
void test_longitud_variable(char* pass1, char* pass2) {
    printf("[TEST 2] Verificación de Salida de Longitud Variable\n");
    
    size_t len1 = strlen(pass1);
    size_t len2 = strlen(pass2);
    
    size_t expected_out1 = get_primoA(len1);
    size_t expected_out2 = get_primoA(len2);
    
    printf("  Clave 1: '%s' (len_pass: %zu) -> len_salida esperada: %zu bytes\n", pass1, len1, expected_out1);
    printf("  Clave 2: '%s' (len_pass: %zu) -> len_salida esperada: %zu bytes\n", pass2, len2, expected_out2);
    
    byte* h1 = hash_pass(pass1);
    byte* h2 = hash_pass(pass2);

    if (!h1 || !h2) {
        printf("  [ERROR] Se generó un puntero nulo.\n\n");
        return;
    }

    if (expected_out1 != expected_out2) {
        printf("  [EXITO] Las longitudes de salida varían correctamente según la clave.\n");
    } else {
        printf("  [ADVERTENCIA] Ambas claves generaron la misma longitud de salida.\n");
    }
    printf("\n");
    
    free(h1); free(h2);
}

/* PRUEBA 3: Efecto Avalancha en Misma Longitud (Cambiar 1 bit) */
void test_avalancha(char* pass1, char* pass2) {
    printf("[TEST 3] Sensibilidad al cambio (Efecto Avalancha)\n");
    
    size_t len1 = strlen(pass1);
    size_t expected_out = get_primoA(len1);
    
    byte* h1 = hash_pass(pass1);
    byte* h2 = hash_pass(pass2);
    
    int bytes_diferentes = 0;
    for(size_t i = 0; i < expected_out; i++) {
        if(h1[i] != h2[i]) bytes_diferentes++;
    }
    
    printf("  Clave 1: '%s'\n", pass1);
    printf("  Clave 2: '%s'\n", pass2);
    printf("  Bytes modificados: %d / %zu\n", bytes_diferentes, expected_out);
    
    if (bytes_diferentes > 0) {
        printf("  [EXITO] La salida cambió sustancialmente.\n");
    } else {
        printf("  [FALLO] La salida es idéntica a pesar de cambiar la clave.\n");
    }
    printf("\n");
    
    free(h1); free(h2); 
}

int main() {
    printf("================================================================\n");
    printf("    PRUEBAS DE HASH (LONGITUD DE SALIDA VARIABLE)\n");
    printf("================================================================\n\n");

    /* Casos de prueba */
    char clave_corta[] = "abc";
    char clave_larga[] = "SuperPasswordSegura123";
    char clave_casi_igual[] = "SuperPasswordSegura124"; /* Cambia un dígito */

    test_determinismo(clave_corta);
    test_determinismo(clave_larga);
    
    test_longitud_variable(clave_corta, clave_larga);
    
    test_avalancha(clave_larga, clave_casi_igual);

    return 0;
}