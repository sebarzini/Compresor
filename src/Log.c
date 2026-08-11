# include "Log.h"

static FILE *log_file = NULL;

static void abrir_log() {
    if (log_file == NULL) {
        log_file = fopen(MTH_LOG_PATH, "w");
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
    fprintf(log_file, "[%s %s] [%s:%d | %s()] ", date, time, nombre_archivo(file), line, func);

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