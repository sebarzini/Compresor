#include "main.h"

int main(int argc, char* argv[]) {
    t_config cfg = { MODO_NINGUNO, 4, NULL, NULL, NULL };
    boolean ok = TRUE;

    LIMPIAR_PANTALLA();
    printf("Iniciando programa\n");
    LOG("Programa iniciado");

    if (!parse(argc, argv, &cfg)) {
        LOG("Argumentos invalidos: se aborta la ejecucion");
        mostrar_ayuda();
        close_log();
        return EXIT_FAILURE;
    }

    LOG("Modo: %d", cfg.modo);
    LOG("N bits: %d", cfg.n_bits);
    LOG("Password: %s", cfg.password != NULL ? "(provista)" : "(no provista)");
    LOG("File in: %s", cfg.file_in != NULL ? cfg.file_in : "(ninguno)");
    LOG("File out: %s", cfg.file_out != NULL ? cfg.file_out : "(ninguno)");

    if ((cfg.modo == MODO_NINGUNO)||(cfg.modo == MODO_AYUDA)) {     mostrar_ayuda();
    } else if (cfg.modo == MODO_ABOUT) {                            mostrar_about();
    } else if (cfg.modo == MODO_COMPRIMIR) {                        ok = comprimir(cfg);
    } else if (cfg.modo == MODO_DESCOMPRIMIR) {                     ok = descomprimir(cfg);
    }

    printf("Finalizando programa\n");
    LOG("Programa finalizado");
    if (!close_log()) {
        ok = FALSE;
    }
    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
