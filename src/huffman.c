#include "huffman.h"

void print_bin(unsigned long numero, int bits) {
int total_bits_long;
    int i;
    unsigned long mascara;

    total_bits_long = (int)(sizeof(long) * 8);

    /* Validacion de limites para la cantidad de bits a mostrar */
    if (bits <= 0) {
        printf("\n");
        return;
    }
    if (bits > total_bits_long) {
        bits = total_bits_long;
    }

    /* Muestra bit por bit desde el mas significativo del rango solicitado hasta el bit 0 */
    for (i = bits - 1; i >= 0; i--) {
        mascara = 1UL << i;
        putchar(numero & mascara ? '1' : '0');
    }
    putchar('\n');
}


void operacion(long palabra, int n_bits){
    print_bin(palabra, n_bits);
}
