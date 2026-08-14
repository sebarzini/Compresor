# include "Log.h"

static FILE *log_file = NULL;
static int log_deshabilitado = 0;

/* Abre el log una unica vez; si falla avisa por stderr y deshabilita el log
   para no reintentar en cada mensaje. */
static void abrir_log(void) {
    if (log_file != NULL || log_deshabilitado) {
        return;
    }

    log_file = fopen(MTH_LOG_PATH, "w");
    if (log_file == NULL) {
        log_deshabilitado = 1;
        fprintf(stderr, "No se pudo abrir el log '%s': %s. Log deshabilitado.\n",
                MTH_LOG_PATH, strerror(errno));
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

    if (fmt == NULL) {
        return;
    }

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

    if (fflush(log_file) != 0 || ferror(log_file) != 0) {
        fprintf(stderr, "Error al escribir en el log '%s': %s. Log deshabilitado.\n",
                MTH_LOG_PATH, strerror(errno));
        clearerr(log_file);
        fclose(log_file);
        log_file = NULL;
        log_deshabilitado = 1;
    }
}

boolean close_log(void) {
    boolean ok = TRUE;

    if (log_file != NULL) {
        if (fclose(log_file) != 0) {
            fprintf(stderr, "Error al cerrar el log '%s': %s\n",
                    MTH_LOG_PATH, strerror(errno));
            ok = FALSE;
        }
        log_file = NULL;
    }

    return ok;
}