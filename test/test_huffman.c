#include "huffman.h"

void test_palabras() {
    printf("[TEST 1] Imprimir palabras\n");

    print_bin(0, 8);
    print_bin(2, 8);
    print_bin(4, 8);
    print_bin(64, sizeof(long)*8);
    print_bin(65, sizeof(long)*8);
    print_bin(66, sizeof(long)*8);
}

int main() {
    LIMPIAR_PANTALLA();
    printf("================================================================\n");
    printf("    PRUEBAS DE HUFFMAN\n");
    printf("================================================================\n\n");

    test_palabras();

    return 0;
}