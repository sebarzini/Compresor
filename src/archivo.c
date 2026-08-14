#include "archivo.h"

/**
 * Abre un archivo en modo de binario.
 *
 * @param path - Ruta del archivo a abrir.
 * @param escribir - Indica si se abre para escritura (true) o lectura (false).
 * @return FILE* - Puntero al archivo abierto.
 */
FILE* abrir_archivo(const char* path, boolean escribir) {
    FILE* archivo = NULL;

    if (path == NULL) {
        return NULL;
    }

    archivo = fopen(path, escribir ? FOPEN_WRITE_BIN : FOPEN_READ_BIN);
    if (archivo == NULL) {
        fprintf(stderr, "No se pudo abrir '%s' en modo %s: %s\n",
                path, escribir ? "escritura" : "lectura", strerror(errno));
    }

    return archivo;
}

/**
 * Cierra un archivo abierto previamente con abrir_archivo.
 *
 * @param archivo - Puntero al archivo a cerrar.
 * @return TRUE si se cerro correctamente, FALSE si hubo error de cierre.
 */
boolean cerrar_archivo(FILE* archivo){
    if (archivo == NULL) {
        return FALSE;
    }
    if (fclose(archivo) != 0) {
        fprintf(stderr, "Error al cerrar el archivo: %s\n", strerror(errno));
        return FALSE;
    }
    return TRUE;
}

/**
 * Escribe un buffer de bytes en un archivo abierto en modo de binario.
 *
 * @param archivo - Puntero al archivo abierto para escritura.
 * @param buffer - Puntero al buffer de bytes a escribir.
 * @param len - Tamano del buffer en bytes.
 * @return TRUE si se escribieron los len bytes, FALSE en caso de error.
 */
boolean escribir_file(FILE* archivo, byte* buffer, size_t len){
    size_t escritos = 0;

    if (archivo == NULL || buffer == NULL || len == 0) {
        return FALSE;
    }

    escritos = fwrite(buffer, 1, len, archivo);
    if (escritos != len) {
        fprintf(stderr, "Error de escritura: %lu de %lu bytes (%s)\n",
                (unsigned long)escritos, (unsigned long)len, strerror(errno));
        return FALSE;
    }

    return TRUE;
}

/**
 * Lee un archivo en modo de binario y devuelve un puntero a un buffer con
 * los bytes leidos.
 *
 * @param archivo - Puntero al archivo abierto para lectura.
 * @param len - Tamano del buffer en bytes.
 * @return byte* - Puntero al buffer de bytes leido.
 */
byte* leer_file(FILE* archivo, size_t* bytes_read, size_t len){
    byte* buffer = NULL;
    size_t to_read = len;
    size_t read_count = 0;

    if (bytes_read != NULL) {
        *bytes_read = 0;
    }

    if (archivo == NULL) {
        return NULL;
    }

    /* Si count es 0, calcula dinámicamente los bytes restantes hasta el EOF */
    if (to_read == 0) {
        long current_pos = ftell(archivo);
        if (current_pos < 0) return NULL;
        if (fseek(archivo, 0, SEEK_END) != 0) return NULL;
        long end_pos = ftell(archivo);
        if (end_pos < 0 || end_pos < current_pos) return NULL;
        if (fseek(archivo, current_pos, SEEK_SET) != 0) return NULL;
        to_read = (size_t)(end_pos - current_pos);
    }

    if (to_read == 0) {
        return NULL;
    }

    buffer = (unsigned char*)malloc(to_read);
    if (buffer == NULL) {
        return NULL;
    }

    read_count = fread(buffer, 1, to_read, archivo);

    if (bytes_read != NULL) {
        *bytes_read = read_count;
    }

    if (read_count != to_read && ferror(archivo) != 0) {
        fprintf(stderr, "Error de lectura tras %lu bytes: %s\n",
                (unsigned long)read_count, strerror(errno));
        free(buffer);
        if (bytes_read != NULL) {
            *bytes_read = 0;
        }
        return NULL;
    }

    return buffer;
}



/*
 * Verifica si un archivo existe en el sistema de archivos.
 *
 * @param path - Ruta del archivo a verificar.
 * @return true si el archivo existe, false en caso contrario.
 */

boolean existe_archivo(const char* path){
    struct stat st;
    if (path == NULL) {
        return 0;
    }
    if (stat(path, &st) != 0) {
        return 0; /* El archivo no existe o no se tiene acceso */
    }
    
    if (S_ISDIR(st.st_mode)) {
        return 0; /* Es un directorio */
    }
    
    return S_ISREG(st.st_mode) ? 1 : 0;
}
