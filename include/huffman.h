#include <stdio.h>
#include "tipos_gen.h"
#include "Log.h"
#include "SO.h"

byte bit(byte b, int n);
void operacion(LONG64 palabra, int n_bits);
void print_bin(LONG64 numero, int bits);
void ejecutar(LONG64 numero, int bits, void (*operacion)(LONG64, int));
void procesar(const char* archivo_in, const char* archivo_out);