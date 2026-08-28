#include "huffman.h"

byte bit(byte b, int n){
    return (b >> n) & 1;
}

/* CONCEPTO */
void print_bin(LONG64 numero, int bits) {
    int total_bits_long;
    int i;
    LONG64 mascara;

    total_bits_long = (int)(sizeof(LONG64) * 8);

    /* Validacion de limites para la cantidad de bits a mostrar */
    if (bits <= 0) return;
    if (bits > total_bits_long) bits = total_bits_long;

    /* Muestra bit por bit desde el mas significativo del rango solicitado hasta el bit 0 */
    for (i = bits - 1; i >= 0; i--) {
        mascara = 1UL << i;
        putchar(numero & mascara ? '1' : '0');
        if ((i>0)&&(i % 4 == 0)){
            putchar(' ');
                if (i % 8 == 0){
                    putchar('-');
                    putchar(' ');
                }
        }
    }
    putchar('\n');
}


/* CONCEPTO */
void operacion(LONG64 palabra, int n_bits){
    print_bin(palabra, n_bits);
}

/* CONCEPTO */
void ejecutar(LONG64 numero, int bits, void (*operacion)(LONG64, int)) {
    LONG64 ret = 0;
    int i_ret = 0;
    int total_bits_long;
    int i;
    LONG64 mascara;

    total_bits_long = (int)(sizeof(LONG64) * 8);

    /* Validacion de limites para la cantidad de bits a mostrar */
    if (bits <= 0) return;
    if (bits > total_bits_long) bits = total_bits_long;

    /* Muestra bit por bit desde el mas significativo del rango solicitado hasta el bit 0 */
    LOG("numero: %lu - bits: %d", numero, bits);
    for (i = sizeof(LONG64)*8 - 1; i >= 0; i--) {
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

