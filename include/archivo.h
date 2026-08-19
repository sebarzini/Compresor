#ifndef MTH_ARCHIVO

#define MTH_ARCHIVO
#define TAMANO_BUFFER 1024

#include "tipos_gen.h"
#include "SO.h"

/* Limite de una lectura en memoria (64 MiB) para no reservar buffers
   arbitrariamente grandes a partir del tamano de un archivo no confiable */
#ifndef MAX_LECTURA_BYTES
#define MAX_LECTURA_BYTES ((size_t)64 * 1024 * 1024)
#endif

FILE* abrir_archivo(const char* path, boolean escribir);
void cerrar_archivo(FILE* archivo);
void escribir_file(FILE* archivo, byte* buffer, size_t len);
byte* leer_file(FILE* archivo);
boolean existe_archivo(const char* path);

#endif // MTH_ARCHIVO