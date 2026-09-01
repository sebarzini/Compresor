#include "archivo.h"

/**
 * Abre un archivo en modo de binario.
 *
 * @param path - Ruta del archivo a abrir.
 * @param escribir - Indica si se abre para escritura (true) o lectura (false).
 * @return FILE* - Puntero al archivo abierto.
 */
FILE* abrir_archivo(const char* path, boolean escribir) {
    if (path == NULL) {
        return NULL;
    }
    return fopen(path, escribir ? FOPEN_WRITE_BIN : FOPEN_READ_BIN);
}

/**
 * Cierra un archivo abierto previamente con abrir_archivo.
 *
 * @param archivo - Puntero al archivo a cerrar.
 */
void cerrar_archivo(FILE* archivo){
    if (archivo != NULL) {
        fclose(archivo);
    }
}


/**
 * Escribe un buffer de bytes en un archivo abierto en modo de binario.
 *
 * @param archivo - Puntero al archivo abierto para escritura.
 * @param buffer - Puntero al buffer de bytes a escribir.
 * @param len - Tamano del buffer en bytes.
 */
void escribir_file(FILE* archivo, byte* buffer, size_t len){
    
    if (archivo == NULL || buffer == NULL || len == 0) {
        return;
    } else {
        fwrite(buffer, 1, len, archivo);
    }
}

/**
 * Lee un archivo en modo de binario y devuelve un puntero a un buffer con
 * los bytes leidos.
 *
 * @param archivo - Puntero al archivo abierto para lectura.
 * @param byte* - Puntero al buffer de bytes leido.
 * @return len - Tamano del buffer leidos en bytes.
 */
size_t leer_file(FILE* archivo, byte* buffer){
    long current_pos;
    long end_pos;
    size_t to_read;
    size_t read_count;

    if (archivo == NULL || buffer == NULL) return 0;

/* Guardar posicion actual */
    current_pos = ftell(archivo);
    if (current_pos < 0) return 0;

    /* Calcular posicion final */
    if (fseek(archivo, 0, SEEK_END) != 0) return 0;
    end_pos = ftell(archivo);

    /* Validar y restaurar posicion inicial */
    if (fseek(archivo, current_pos, SEEK_SET) != 0) return 0;
    if (end_pos < 0 || end_pos < current_pos) return 0;

    /* Acotar tamano de lectura al menor entre lo restante y TAMANO_BUFFER */
    to_read = (size_t)(end_pos - current_pos);
    if (to_read == 0) return 0;

    to_read = (to_read > TAMANO_BUFFER) ? TAMANO_BUFFER : to_read;

    read_count = fread(buffer, 1, to_read, archivo);

    return read_count;
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
