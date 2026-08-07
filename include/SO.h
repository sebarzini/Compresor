#ifndef M_SO
#define M_SO

#include <stdio.h>
#include <stdlib.h> // Para system()
#include "tipos_gen.h"

// ============================================================================
//   CONSTANTES MULTIPLATAFORMA (Iguales en Windows y Linux)
// ============================================================================
// Modos de apertura binaria universales
#define FOPEN_READ_BIN  "rb"
#define FOPEN_WRITE_BIN "wb"
#define FOPEN_APPEND_BIN "ab"

// ============================================================================
//   DETECCIÓN Y CONFIGURACIÓN ESPECÍFICA DE CADA S.O.
// ============================================================================
#if defined(_WIN32) || defined(_WIN64)
    #include <direct.h> // Para _mkdir en Windows

    #define PATH_SEP '\\'
    #define PATH_SEP_STR "\\"
    #define OS_NAME "Windows"
    #define NEWLINE "\r\n"
    #define LIMPIAR_PANTALLA() system("cls")

#elif defined(__linux__) || defined(__APPLE__)
    #include <sys/stat.h> // Para mkdir en Linux/Unix

    #define PATH_SEP '/'
    #define PATH_SEP_STR "/"
    #define OS_NAME "Linux/Unix"
    #define NEWLINE "\n"
    #define LIMPIAR_PANTALLA() system("clear")

#else
    #define PATH_SEP '/'
    #define PATH_SEP_STR "/"
    #define OS_NAME "Desconocido"
    #define NEWLINE "\n"
    #define LIMPIAR_PANTALLA() printf("\n--- Pantalla Limpia ---\n")
#endif

// ============================================================================
//   FUNCIONES DEL MÓDULO
// ============================================================================

// Objetivo: Crear un directorio (carpeta) adaptándose al SO
// Entrada: Ruta de la carpeta a crear
// Salida: true si se creó con éxito, false en caso de error
inline boolean crear_directorio(const char *ruta) {
#if defined(_WIN32) || defined(_WIN64)
    return _mkdir(ruta) == 0;
#elif defined(__linux__) || defined(__APPLE__)
    return mkdir(ruta, 0777) == 0;
#else
    return false; 
#endif
}

// Objetivo: Mostrar en consola la configuración de plataforma detectada
void imprimir_configuracion_sistema(void) {
    printf("Sistema Operativo: %s\n", OS_NAME);
    printf("Separador de carpetas: %c\n", PATH_SEP);
}

#endif
