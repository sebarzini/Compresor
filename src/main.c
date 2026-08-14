#include "main.h"

int main(int argc, char* argv[]) {
    t_config cfg = { MODO_NINGUNO, 4, NULL, NULL, NULL };

    LIMPIAR_PANTALLA();
    printf("Iniciando programa\n");
    LOG("Programa iniciado");

    if (!parse(argc, argv, &cfg)) {
        LOG("Argumentos invalidos");
        mostrar_ayuda();
        close_log();
        return EXIT_FAILURE;
    }

    LOG("Modo: %d", cfg.modo);
    LOG("N bits: %d", cfg.n_bits);
    /* La clave nunca se registra: solo se deja constancia de su presencia. */
    LOG("Password: %s", (cfg.password != NULL) ? "[provista]" : "[ninguna]");
    LOG("File in: %s", (cfg.file_in != NULL) ? cfg.file_in : "(ninguno)");
    LOG("File out: %s", (cfg.file_out != NULL) ? cfg.file_out : "(ninguno)");

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
