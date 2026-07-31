#include "primos.h"
#include <stdlib.h>

/* Variables y funciones estaticas para el generador determinista (LCG) aislado del rand() global */
static unsigned long lcg_seed = 1;

static void local_srand(unsigned long seed) {
    lcg_seed = seed;
}

static unsigned long local_rand(void) {
    lcg_seed = lcg_seed * 1103515245 + 12345;
    return (unsigned long)((lcg_seed / 65536) % 32768);
}

/* 25 numeros primos menores a 100 en orden ascendente */
static const int PRIMES_A[25] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 
    43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
};

/* Los mismos 25 primos ordenados de forma pseudoaleatoria */
static const int PRIMES_B[25] = {
    47, 73, 11, 89, 3, 61, 19, 43, 79, 5, 31, 97, 13, 
    67, 23, 59, 2, 83, 7, 53, 29, 71, 17, 37, 41
};

unsigned char get_random_byte(void) {
    return (unsigned char)(rand() % 256);
}

char* get_deterministic_hash(const char *input, int x, char *out) {
    unsigned long hash = 5381;
    int c;
    int i;

    /* Algoritmo de hash djb2 para convertir la cadena de entrada en una semilla numerica */
    while ((c = *input++)) {
        hash = ((hash << 5) + hash) + c; 
    }
    
    local_srand(hash);

    /* Generacion de caracteres en rango ASCII imprimible (33 '!' a 126 '~') para legibilidad del string en C */
    for (i = 0; i < x; i++) {
        out[i] = (char)(33 + (local_rand() % 94));
    }
    out[x] = '\0';

    return out;
}

char* get_random_string(int y, char *out) {
    int i;
    for (i = 0; i < y; i++) {
        out[i] = (char)(33 + (rand() % 94));
    }
    out[y] = '\0';

    return out;
}

int get_primoA(unsigned int n) {
    return PRIMES_A[n % 25];
}

int get_primoB(unsigned int n) {
    return PRIMES_B[n % 25];
}