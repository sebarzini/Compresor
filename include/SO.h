#ifndef M_SO
#define M_SO

#include <stdio.h>

// Deteccion de plataforma mediante macros predefinidas del compilador
#if defined(_WIN32) || defined(_WIN64)
    #define PATH_SEP '\\'
    #define PATH_SEP_STR "\\"
    #define OS_NAME "Windows"
#elif defined(__linux__)
    #define PATH_SEP '/'
    #define PATH_SEP_STR "/"
    #define OS_NAME "Linux"
#else
    #define PATH_SEP '/'
    #define PATH_SEP_STR "/"
    #define OS_NAME "Unix-Like"
#endif

// Objetivo: Mostrar en consola la configuracion de plataforma detectada por el preprocesador
// Entrada: Ninguna
// Salida: Ninguna (Escribe informacion en stdout)
void imprimir_configuracion_sistema(void) {
    // Lectura de constantes definidas condicionalmente
    printf("Sistema Operativo: %s\n", OS_NAME);
    printf("Separador de carpetas: %c\n", PATH_SEP);
}

#endif