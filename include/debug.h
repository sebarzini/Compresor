#ifndef M_DEBUG
#define M_DEBUG

#include <stdio.h>

// ============================================================================
//   CONFIGURACIÓN: COMENTA ESTA LÍNEA PARA APAGAR EL DEBUG
// ============================================================================
#define MODO_DEBUG 

// ============================================================================
//   DEFINICIÓN DE MACROS DE DEPURACIÓN
// ============================================================================
#ifdef MODO_DEBUG

    #define DEBUG_PRINT(fmt, ...) printf("[DEBUG] " fmt, ##__VA_ARGS__)
    
    #define DEBUG_TRACE(fmt, ...) \
        printf("[TRACE] (%s:%d): " fmt, __FILE__, __LINE__, ##__VA_ARGS__)

    #define DEBUG_WARN_IF(condicion, fmt, ...) \
        if (condicion) { printf("[WARN] " fmt, ##__VA_ARGS__); }

#else

    // Si MODO_DEBUG no está definido, las macros se transforman en (void)0.
    // Para el compilador, esto equivale a escribir un número literal o nada.
    // Lo ignora por completo en la mismísima fase de preprocesamiento.
    #define DEBUG_PRINT(fmt, ...)          ((void)0)
    #define DEBUG_TRACE(fmt, ...)          ((void)0)
    #define DEBUG_WARN_IF(condicion, fmt, ...) ((void)0)

#endif

#endif
