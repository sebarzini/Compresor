#ifndef MTH_LOG
#define MTH_LOG

#ifndef MTH_LOG_PATH
    #define MTH_LOG_PATH "log.txt"
#endif  // MTH_LOG_PATH

#include <stdio.h>
#include <stdarg.h>

/* Compatibilidad para el nombre de función entre C89 y C99/C11 */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define LOG_CURRENT_FUNC __func__
#elif defined(__GNUC__) || defined(_MSC_VER)
    #define LOG_CURRENT_FUNC __FUNCTION__
#else
    #define LOG_CURRENT_FUNC "(unknown)"
#endif
/* Macro pública para capturar la línea y archivo exactos del invocador */
#define LOG(fmt, ...) \
    log_write_internal( __FILE__, \
                        __LINE__, \
                        __DATE__, \
                        __TIME__, \
                        LOG_CURRENT_FUNC, \
                        (fmt), \
                        ##__VA_ARGS__)
/* Función interna que procesa los metadatos, el mensaje variable y cierra el archivo */

void log_write_internal(const char *file,
                                  int line,
                                  const char *date,
                                  const char *time,
                                  const char *func,
                                  const char *fmt,
                                  ...);

void close_log();


#endif // MTH_LOG