#ifndef MTH_CRYPTO
#define MTH_CRYPTO

#include "tipos_gen.h"
#include "rotacion.h"
#include "primos.h"


#define RANDOM_INIT srand(time(NULL));

byte* hash_pass(char* pass);
byte* random_bytes(int n);

t_lista_ptr getListaPass(char* pass);
t_lista_ptr getListaHash(int len);
byte encode(byte dato, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass);
byte decode(byte dato, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenpass);
byte* encode_n(byte* buffer, int len, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass);
byte* decode_n(byte* buffer, int len, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenpass);
#endif // MTH_CRYPTO