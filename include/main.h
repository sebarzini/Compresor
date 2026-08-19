#ifndef MTH_MAIN_H
#define MTH_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "Log.h"
#include "SO.h"
#include "tipos_gen.h"

#define MIN_BITS 1
#define MAX_BITS 16
#define MAX_PASS_LEN 256

typedef enum {
    MODO_NINGUNO,
    MODO_COMPRIMIR,
    MODO_DESCOMPRIMIR,
    MODO_AYUDA,
    MODO_ABOUT
} t_modo;

typedef struct {
    t_modo modo;
    int n_bits;              /* Opcional: defecto 4 */
    const char* password;    /* Opcional: defecto NULL */
    const char* file_in;     /* Obligatorio */
    const char* file_out;    /* Opcional: defecto NULL */
} t_config;

void mostrar_about() {
    char* titulo = "COMPRESOR EN C - MITHOS";
    char* version = "v1.0.0 (2026)";
    char* autor = "Por: Barzini Sebastian Cruz";
    char* mail = "mail: sebarzini@gmail.com";
    LOG("Iniciando About");
    LIMPIAR_PANTALLA();
    
    printf("========================================\n");
    // %28s centra el texto en una pantalla estandar de DOS
    printf("%28s\n", titulo); 
    printf("%25s\n", version);
    printf("----------------------------------------\n");
    printf("%26s\n", autor);
    printf("%26s\n", mail);
    printf("\n   Desarrollado en ANSI C para MS-DOS\n");
    printf("========================================\n");
    printf("\nPresione cualquier tecla para volver...\n");
    getchar();
    LOG("Terminado About");
}

void mostrar_ayuda() {
    LOG("Iniciando la ayuda");
    LIMPIAR_PANTALLA();
    printf("Uso: compresor [MODO] [OPCIONES]\n\n");
    printf("Modos principales (uno requerido):\n");
    printf("  -c               Comprimir archivo\n");
    printf("  -d               Descomprimir archivo\n");
    printf("  -h               Muestra esta pantalla de ayuda\n");
    printf("  -a               Muestra los creditos y version (About)\n\n");
    printf("Opciones:\n");
    printf("  -i <archivo>     Archivo de entrada (requerido para -c y -d)\n");
    printf("  -o <archivo>     Archivo de salida (opcional: por defecto <entrada>.mzi\n");
    printf("  -n <bits>        Tamano de palabra en bits (opcional: defecto %d, rango %d-%d)\n", 4, MIN_BITS, MAX_BITS);
    printf("  -p <clave>       Clave de cifrado (opcional: si no se provee, no se encripta)\n");
    LOG("Terminado la ayuda");
}

/* Devuelve el valor asociado a una opcion, o NULL si el usuario no lo proporciono.
   Avanza el indice solo cuando existe un argumento siguiente. */
static const char* valor_opcion(int argc, char* argv[], int* i, char opcion) {
    if (*i + 1 >= argc) {
        printf("Error: la opcion -%c requiere un valor.\n", opcion);
        return NULL;
    }
    (*i)++;
    return argv[*i];
}

boolean parse(int argc, char* argv[], t_config* cfg){
    LOG("Iniciando parseo de argumentos");
    int i;
    const char* valor;

    for (i = 1; i < argc; i++) {
        if (argv[i][0] != '-' || argv[i][1] == '\0') {
            printf("Error: argumento no reconocido '%s'.\n", argv[i]);
            return FALSE;
        }
        switch (argv[i][1]) {
            case 'c':
                cfg->modo = MODO_COMPRIMIR;
                break;
            case 'd':
                cfg->modo = MODO_DESCOMPRIMIR;
                break;
            case 'h':
                cfg->modo = MODO_AYUDA;
                break;
            case 'a':
                cfg->modo = MODO_ABOUT;
                break;
            case 'i':
                valor = valor_opcion(argc, argv, &i, 'i');
                if (valor == NULL) return FALSE;
                cfg->file_in = valor;
                break;
            case 'o':
                valor = valor_opcion(argc, argv, &i, 'o');
                if (valor == NULL) return FALSE;
                cfg->file_out = valor;
                break;
            case 'n':
                valor = valor_opcion(argc, argv, &i, 'n');
                if (valor == NULL) return FALSE;
                cfg->n_bits = atoi(valor);
                if (cfg->n_bits < MIN_BITS || cfg->n_bits > MAX_BITS) {
                    printf("Error: -n debe estar entre %d y %d.\n", MIN_BITS, MAX_BITS);
                    return FALSE;
                }
                break;
            case 'p':
                valor = valor_opcion(argc, argv, &i, 'p');
                if (valor == NULL) return FALSE;
                if (valor[0] == '\0' || strlen(valor) > MAX_PASS_LEN) {
                    printf("Error: la clave debe tener entre 1 y %d caracteres.\n", MAX_PASS_LEN);
                    return FALSE;
                }
                cfg->password = valor;
                break;
            default:
                printf("Error: opcion desconocida '%s'.\n", argv[i]);
                return FALSE;
        }
    }

    if ((cfg->modo == MODO_COMPRIMIR || cfg->modo == MODO_DESCOMPRIMIR) &&
        cfg->file_in == NULL) {
        printf("Error: -i <archivo> es obligatorio para -c y -d.\n");
        return FALSE;
    }

    LOG("Terminado parseo de argumentos");
    return TRUE;
}


void comprimir(t_config cfg){
 //   FILE* archivo_in = NULL;
  //  size_t bytes_leidos = 0;

    LOG("Iniciando la compresion");
    printf("Comprimir: %s\n", cfg.file_in);
    /* Recorrer archivo de entrada */
    LOG("Abriendo archivo %s", cfg.file_in);
    /*      Contabilizar repeticiones de simbolos */
//        archivo_in = abrir_archivo(cfg.file_in);
 //       while (bytes_leidos = leer_archivo(archivo_in) > 0) {
            LOG("Contabilizando repeticiones de simbolos");
  //      }
    /* Armar canonico de huffman */
    LOG("Armando arbol de huffman");
    /* Si tiene password */
    LOG("Controlo la existencia de password");
    /*      Genero hash de pass y hash crypto */
        LOG("Genero hash de pass y hash crypto");
        /*      Encripto y guardo el hash en el archivo de salida */
        LOG("Encripto y guardo el hash en el archivo de salida");
        /* Guardo el arbol en el archivo (encriptado si hay pass)*/
        LOG("Guardo el arbol en el archivo de salida");
    /* Recorrer archivo de entrada */
    LOG("Abriendo archivo de salida");
    /*      Voy cargando buffer de entrada */
        LOG("Cargo el buffer de entrada");
        /*      Claculando el CRC */
        LOG("Calculo el CRC");
        /*      Cuando el buffer se llena, voy comprimiendo y pasando al buffer de salida */
        LOG("Comprimiendo y pasando al buffer de salida");
        /*      Cuando el buffer de salida se llena, voy guardandolo en disco (encriptado si hay pass) */
        LOG("Grabo el buffer en el archivo de salida y libero");
    /* Cuando termina el archivo grabo el buffer de salida (con el ultimo padding) */
    LOG("Grabo en el archivo de salida lo que queda en el buffer y padding");
    /* Grabo el CRC en el archivo de salida */
    LOG("Guardo el CRC en el archivo de salida");
    LOG("Terminado la compresion");
    //cerrar_archivo(archivo_in);
}

void descomprimir(t_config cfg){
    LOG("Iniciando la descompresion");
    printf("Descomprimir: %s\n", cfg.file_in);
    /* Abrir archivo de entrada */
    /* Ver si ingresaron password   */
    /*      Si ingresaron password, saco, decripto el hash */
    /* Recorrer archivo de entrada */
    /*      Voy cargando buffer de entrada */
    /*      Cuando el buffer se llena, voy descomprimiendo y pasando al buffer de salida */
    /*      Claculando el CRC */
    /*      Cuando el buffer de salida se llena, voy guardandolo en disco */
    /* Cuando termina el archivo grabo el buffer de salida (con el ultimo padding) */
    /* Comprubo el CRC*/
    /*      Si no coincide, elimino el archivo temporal */
    /*      limpio memoria de descompresion (RAM)*/
    /*      Notifico al usuario del error*/
    /*      Cerramos la aplicacion*/
    /* Cerramos el archivo y renombramos el archivo temporal*/
    /* Limpiamos la memoria*/
    /* terminamos la aplicacion de forma segura*/
    LOG("Terminado la descompresion");
}

#endif /* MTH_MAIN_H */