#include "tipos_gen.h"
#include "rotacion.h"
#include "primos.h"


#define RANDOM_INIT srand(time(NULL));

byte* hash_pass(char* pass);
byte* random_bytes(int n);