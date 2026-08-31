#ifndef MTH_ARCHIVO

#define MTH_ARCHIVO
#define TAMANO_BUFFER 1024
#define LEER_ARCHIVO(archivo, buffer) fread(buffer, 1, TAMANO_BUFFER, archivo)

#include "tipos_gen.h"
#include "SO.h"

FILE* abrir_archivo(const char* path, boolean escribir);
void cerrar_archivo(FILE* archivo);
void escribir_file(FILE* archivo, byte* buffer, size_t len);
size_t leer_file(FILE* archivo, byte* buffer);
boolean existe_archivo(const char* path);

#endif // MTH_ARCHIVO