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


void operacion(unsigned long palabra, int n_bits){
    print_bin(palabra, n_bits);
}

void ejecutar(unsigned long numero, int bits, void (*operacion)(unsigned long, int)) {
    unsigned long ret = 0;
    int i_ret = 0;
    int total_bits_long;
    int i;
    unsigned long mascara;

    total_bits_long = (int)(sizeof(long) * 8);

    /* Validacion de limites para la cantidad de bits a mostrar */
    if (bits <= 0) return;
    if (bits > total_bits_long) bits = total_bits_long;

    /* Muestra bit por bit desde el mas significativo del rango solicitado hasta el bit 0 */
    LOG("numero: %lu - bits: %d", numero, bits);
    for (i = sizeof(long)*8 - 1; i >= 0; i--) {
        LOG("i: %lu", i);
        mascara = 1UL << i;
        LOG("mascara: %lu", mascara);
        ret +=(numero & mascara ? 1 : 0);
        LOG("ret: %lu", ret);
        i_ret++;
        if (i_ret == bits){
            printf("i: %d - ", i);
            operacion(ret, bits);
            i_ret = 0;
            ret = 0;
        }
        ret = ret << 1;
    }
}

