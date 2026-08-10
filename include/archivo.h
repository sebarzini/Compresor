#ifndef M_ARCHIVO

#define M_ARCHIVO

#include "tipos_gen.h"
#include "SO.h"

FILE* abrir_archivo(const char* path, boolean escribir);
void cerrar_archivo(FILE* archivo);
void escribir_file(FILE* archivo, byte* buffer, size_t len);
byte* leer_file(FILE* archivo, size_t* bytes_read, size_t len);
boolean existe_archivo(const char* path);

#endif