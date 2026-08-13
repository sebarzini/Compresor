#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "Log.h"
#include "SO.h"

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
}

void mostrar_ayuda() {
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
    printf("  -n <bits>        Tamano de palabra en bits (opcional: defecto %d)\n", 4);
    printf("  -p <clave>       Clave de cifrado (opcional: si no se provee, no se encripta)\n");
}

void parse(int argc, char* argv[], t_config* cfg){
    int i;
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
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
                    cfg->file_in = argv[++i];
                    break;
                case 'o':
                    cfg->file_out = argv[++i];
                    break;
                case 'n':
                    cfg->n_bits = atoi(argv[++i]);
                    break;
                case 'p':
                    cfg->password = argv[++i];
                    break;
                default:
                    break;
            }
        }
    }
}
