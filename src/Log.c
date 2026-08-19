#if !defined(_WIN32) && !defined(_WIN64) && !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif

# include "Log.h"

#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#define MTH_OPEN(ruta) _open((ruta), _O_WRONLY | _O_CREAT | _O_TRUNC, _S_IREAD | _S_IWRITE)
#define MTH_FDOPEN(fd) _fdopen((fd), "w")
#else
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#define MTH_OPEN(ruta) open((ruta), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)
#define MTH_FDOPEN(fd) fdopen((fd), "w")
#endif

static FILE *log_file = NULL;

/* El log puede contener rutas y metadatos del usuario: se crea accesible
   unicamente por su propietario (0600). */
static void abrir_log() {
    int fd;

    if (log_file != NULL) {
        return;
    }

    fd = MTH_OPEN(MTH_LOG_PATH);
    if (fd < 0) {
        return;
    }

    log_file = MTH_FDOPEN(fd);
    if (log_file == NULL) {
#if defined(_WIN32) || defined(_WIN64)
        _close(fd);
#else
        close(fd);
#endif
    }
}

static const char* nombre_archivo(const char* ruta) {
    const char* nombre = ruta;

    if (ruta == NULL) {
        return "";
    }

    /* Recorre la cadena buscando el último separador '/' o '\' */
    while (*ruta != '\0') {
        if (*ruta == '/' || *ruta == '\\') {
            nombre = ruta + 1;
        }
        ruta++;
    }

    return nombre;
}
void log_write_internal(const char *file,
                                  int line,
                                  const char *date,
                                  const char *time,
                                  const char *func,
                                  const char *fmt,
                                  ...) {
    va_list args;

    if (log_file == NULL) {
        abrir_log();
    }
    if (log_file == NULL) {
        return;
    }
    

    /* 1. Escritura de metadatos */
    fprintf(log_file, "[%s %s] [%-12.12s: %-4.4d | %-12.12s] ", date, time, nombre_archivo(file), line, func);

    /* 2. Escritura de los argumentos y comentarios variables */
    va_start(args, fmt);
    vfprintf(log_file, fmt, args);
    va_end(args);

    /* 3. Salto de línea final y cierre del descriptor */
    fprintf(log_file, "\n");
    fflush(log_file);
}

void close_log() {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}