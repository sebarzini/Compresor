#include "main.h"

int main(int argc, char* argv[]) {
    t_config cfg = { MODO_NINGUNO, 4, NULL, NULL, NULL };

    LIMPIAR_PANTALLA();
    printf("Iniciando programa\n");
    LOG("Programa iniciado");

    parse(argc, argv, &cfg);

    LOG("Modo: %d", cfg.modo);
    LOG("N bits: %d", cfg.n_bits);
    LOG("Password: %s", cfg.password);
    LOG("File in: %s", cfg.file_in);
    LOG("File out: %s", cfg.file_out);

    if ((cfg.modo == MODO_NINGUNO)||(cfg.modo == MODO_AYUDA)) {     mostrar_ayuda();
    } else if (cfg.modo == MODO_ABOUT) {                            mostrar_about();
    } else if (cfg.modo == MODO_COMPRIMIR) {                        comprimir(cfg);
    } else if (cfg.modo == MODO_DESCOMPRIMIR) {                     descomprimir(cfg);
    }

    printf("Finalizando programa\n");
    LOG("Programa finalizado");
    close_log();
    return EXIT_SUCCESS; 
}
