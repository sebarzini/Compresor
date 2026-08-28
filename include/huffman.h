#include <stdio.h>
#include "tipos_gen.h"
#include "Log.h"
#include "SO.h"

void operacion(unsigned long palabra, int n_bits);
void print_bin(unsigned long numero, int bits);
void ejecutar(unsigned long numero, int bits, void (*operacion)(unsigned long, int));
byte bit(byte b, int n);
