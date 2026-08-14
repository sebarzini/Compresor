#include "util.h"

void* reservar_memoria(size_t len, const char* contexto) {
    void* bloque = NULL;

    if (len == 0) {
        return NULL;
    }

    bloque = malloc(len);
    if (bloque == NULL) {
        printf("Error al asignar memoria para %s.\n", (contexto != NULL) ? contexto : "el bloque solicitado");
    }

    return bloque;
}

char caracter_imprimible(unsigned long valor) {
    /* Rango ASCII imprimible (33 '!' a 126 '~') para legibilidad del string en C */
    return (char)(33 + (valor % 94));
}

void imprimir_hex(const char* etiqueta, const byte* buffer, size_t len, size_t limite) {
    size_t a_imprimir = (len > limite) ? limite : len;
    size_t i;

    printf("%-22s (%zu bytes): ", etiqueta, len);
    if (buffer == NULL) {
        printf("(nulo)\n");
        return;
    }
    for (i = 0; i < a_imprimir; i++) {
        printf("%02X ", buffer[i]);
    }
    if (len > limite) {
        printf("... ");
    }
    printf("\n");
}
