#ifndef MTH_DEBUG
#define MTH_DEBUG

#include <stdio.h>

// ============================================================================
//   POSIBLES MEJORAS FUTURAS Y/O ARCHIVO DE LOG
// ============================================================================
// __FILE__ archivo de ejecucion
// __LINE__ linea de codigo en el archivo
// __DATE__ fecha de compilacion
// __TIME__ hora de compilacion
// __func__ o __FUNCTION__ nombre de la funcion en ejecucion actual

// ============================================================================
//   CONFIGURACIÓN: el modo debug se activa unicamente desde el build
//   (CMAKE_BUILD_TYPE=Debug define MODO_DEBUG). Nunca debe quedar activo en
//   una compilacion Release: la traza expone rutas internas del sistema de
//   archivos y detalles de ejecucion.
// ============================================================================

// ============================================================================
//   DEFINICIÓN DE MACROS DE DEPURACIÓN
// ============================================================================
#ifdef MODO_DEBUG

    #define DEBUG_PRINT(fmt, ...) printf("[DEBUG] " fmt, ##__VA_ARGS__)
    
    #define DEBUG_TRACE(fmt, ...) \
        printf("[TRACE] (%s:%d): " fmt, __FILE__, __LINE__, ##__VA_ARGS__)

    #define DEBUG_WARN_IF(condicion, fmt, ...) \
        do { if (condicion) { printf("[WARN] " fmt, ##__VA_ARGS__); } } while (0)

#else

    // Si MODO_DEBUG no está definido, las macros se transforman en (void)0.
    // Para el compilador, esto equivale a escribir un número literal o nada.
    // Lo ignora por completo en la mismísima fase de preprocesamiento.
    #define DEBUG_PRINT(fmt, ...)          ((void)0)
    #define DEBUG_TRACE(fmt, ...)          ((void)0)
    #define DEBUG_WARN_IF(condicion, fmt, ...) do { (void)0; } while (0)

#endif

#endif // MTH_DEBUG
