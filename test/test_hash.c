#include "crypto.h"

/* ============================================================================
 * FUNCIONES AUXILIARES
 * ============================================================================ */

void imprimir_lista(const char* etiqueta, t_lista_ptr lista, size_t limit) {
    size_t count = 0;
    printf("%-22s: ", etiqueta);
    while (lista != NULL && count < limit) {
        printf("- %02X ", (byte)lista->dato);
        lista = lista->siguiente;
        count++;
    }
    printf("\n");
}

void imprimir_hex(const char* etiqueta, const byte* buffer, size_t len, size_t ptrint_limit) {
    printf("%-22s (%zu bytes): ", etiqueta, len);
    /* Imprime un máximo de ptrint_limit bytes para no inundar la consola si el primo es grande */
    size_t limit = (len > ptrint_limit) ? ptrint_limit : len; 
    for (size_t i = 0; i < limit; i++) {
        printf("%02X ", buffer[i]);
    }
    if (len > ptrint_limit) printf("... ");
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
    byte* h3 = hash_pass(pass);

    if (!h1 || !h2 || !h3) {
        printf("  [FALLO] La función devolvió NULL.\n\n");
        return;
    }

    /* Comparamos todo el bloque de memoria devuelto */
    if (memcmp(h1, h2, expected_len) == 0 && memcmp(h2, h3, expected_len) == 0) {
        printf("  [EXITO] La misma entrada genera la misma salida (%zu bytes).\n", expected_len);
    } else {
        printf("  [FALLO] Las salidas son diferentes para la misma entrada.\n");
    }
    
    imprimir_hex("  Salida 1:", h1, expected_len, 20);
    imprimir_hex("  Salida 2:", h2, expected_len, 20);
    imprimir_hex("  Salida 3:", h3, expected_len, 20);
    printf("\n");
    
    free(h1);
    free(h2);
    free(h3);
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
    imprimir_hex("  Salida 1:", h1, expected_out1, 20);
    imprimir_hex("  Salida 2:", h2, expected_out2, 20);
    printf("\n");
    
    free(h1);
    free(h2);
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
    
    imprimir_hex("  Salida 1:", h1, expected_out, 20);
    imprimir_hex("  Salida 2:", h2, expected_out, 20);
    printf("\n");
   free(h1);
   free(h2); 
}

void test_aleatorio() {
    printf("[TEST 4] Generación de Hash Aleatorio\n");
    byte* random_hash1 = random_bytes(16);
    byte* random_hash2 = random_bytes(16);
    byte* random_hash3 = random_bytes(16);

    byte* random_hash4 = random_bytes(32);
    byte* random_hash5 = random_bytes(32);
    byte* random_hash6 = random_bytes(32);

    imprimir_hex("  Hash Aleatorio:", random_hash1, 16, 20);
    imprimir_hex("  Hash Aleatorio:", random_hash2, 16, 20);
    imprimir_hex("  Hash Aleatorio:", random_hash3, 16, 20);
    printf("\n");
    printf("\n");
    imprimir_hex("  Hash Aleatorio:", random_hash4, 32, 20);
    imprimir_hex("  Hash Aleatorio:", random_hash5, 32, 20);
    imprimir_hex("  Hash Aleatorio:", random_hash6, 32, 20);
    printf("\n");

    free(random_hash1);
    free(random_hash2);
    free(random_hash3);
    free(random_hash4);
    free(random_hash5);
    free(random_hash6);
}

void test_encode_decode(char* pass) {
    printf("[TEST 5] Codificación y Decodificación\n");
    
    size_t len = strlen(pass);
    size_t hash_len = get_primoB(len);
    char MSG[] = "Aplicacion";
    
    t_lista_ptr listaPass = getListaPass(pass);
    t_lista_ptr listaHash = getListaHash(hash_len);
    t_lista_ptr listaPass2 = getListaPass(pass);
    t_lista_ptr listaHash2 = listaHash;

    printf("\n\n");
    printf("Mensaje original: %s\n", MSG);
    imprimir_hex("  MSG  Original:", (byte*)MSG, strlen(MSG), 20);

    byte* encoded = encode_n((byte*)MSG, strlen(MSG), &listaPass, &listaHash, strlen(pass));
    imprimir_hex("Mensaje codificado: ", encoded, strlen(MSG), 20);
    
    byte* decoded = decode_n(encoded, strlen(MSG), &listaPass2, &listaHash2, strlen(pass));
    imprimir_hex("  Hash Decodificado:", decoded, strlen(MSG), 20);

    if (memcmp(MSG, decoded, strlen(MSG)) == 0) {
        printf("  [EXITO] La decodificación recuperó correctamente el mensaje original.\n");
    } else {
        printf("  [FALLO] La decodificación NO recuperó el mensaje original.\n");
    }
    
    printf("\n\n");
    vaciar_lista(listaPass);
    vaciar_lista(listaPass2);
    vaciar_lista(listaHash);
    
    free(encoded);
    free(decoded);
}

int main() {
    printf("================================================================\n");
    printf("    PRUEBAS DE CRYPTO (LONGITUD DE SALIDA FIJA)\n");
    printf("================================================================\n\n");

    /* Casos de prueba */
    char clave_corta[] = "abc";
    char clave_larga[] = "SuperPasswordSegura123";
    char clave_casi_igual[] = "SuperPasswordSegura124"; /* Cambia un dígito */

    test_determinismo(clave_corta);
    test_determinismo(clave_larga);
    
    test_longitud_variable(clave_corta, clave_larga);
    
    test_avalancha(clave_larga, clave_casi_igual);

    test_aleatorio();

    test_encode_decode(clave_larga);
    return 0;
}