#ifndef MTH_UTIL
#define MTH_UTIL

#include "tipos_gen.h"

/* Objetivo: Reservar memoria informando por consola si la reserva falla.
   Entrada: len (bytes a reservar), contexto (texto descriptivo para el mensaje de error).
   Salida: Puntero al bloque reservado, o NULL si no hubo memoria disponible. */
void* reservar_memoria(size_t len, const char* contexto);

/* Objetivo: Mapear un valor cualquiera a un caracter ASCII imprimible ('!' a '~').
   Entrada: valor (numero a mapear).
   Salida: Caracter imprimible correspondiente. */
char caracter_imprimible(unsigned long valor);

/* Objetivo: Volcar en consola el contenido hexadecimal de un buffer.
   Entrada: etiqueta (texto descriptivo), buffer, len (bytes del buffer),
            limite (maximo de bytes a imprimir).
   Salida: Ninguna. */
void imprimir_hex(const char* etiqueta, const byte* buffer, size_t len, size_t limite);

#endif // MTH_UTIL
