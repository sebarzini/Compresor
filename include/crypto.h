#ifndef MTH_CRYPTO
#define MTH_CRYPTO

#include "tipos_gen.h"
#include "rotacion.h"
#include "primos.h"


/* Rellena out con len bytes del generador de entropia del sistema
   (/dev/urandom o BCryptGenRandom). Devuelve FALSE si no hay entropia. */
boolean bytes_aleatorios_seguros(byte* out, size_t len);

byte* hash_pass(char* pass);
byte* random_bytes(int n);

t_lista_ptr getListaPass(char* pass);
t_lista_ptr getListaHash(int len);
byte encode(byte dato, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass);
byte decode(byte dato, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenpass);
byte* encode_n(byte* buffer, int len, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass);
byte* decode_n(byte* buffer, int len, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenpass);
#endif // MTH_CRYPTO