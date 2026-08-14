#ifndef MTH_ARCHIVO

#define MTH_ARCHIVO

#include <errno.h>

#include "tipos_gen.h"
#include "SO.h"

FILE* abrir_archivo(const char* path, boolean escribir);
boolean cerrar_archivo(FILE* archivo);
boolean escribir_file(FILE* archivo, byte* buffer, size_t len);
byte* leer_file(FILE* archivo, size_t* bytes_read, size_t len);
boolean existe_archivo(const char* path);

#endif // MTH_ARCHIVO