#include "huffman.h"

void test_print_palabras() {
    printf("[TEST 1] Imprimir palabras\n");

    operacion(0, 8);
    print_bin(2, 8);
    operacion(4, 8);
    print_bin(64, sizeof(LONG64)*8);
    operacion(65, sizeof(LONG64)*8);
    print_bin(66, sizeof(LONG64)*8);
}

void test_separacion() {
    printf("\n\n[TEST 2] Separacion palabras\n");
    ejecutar(4563, 8, operacion);
    ejecutar(4563, 4, operacion);
}

int main() {
    LIMPIAR_PANTALLA();
    printf("=================================\n");
    printf("    PRUEBAS DE HUFFMAN\n");
    printf("=================================\n\n");

    test_print_palabras();

    test_separacion();
    return 0;
}