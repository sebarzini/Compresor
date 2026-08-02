#include "SO.h"
#include "debug.h"

int main(){
    LIMPIAR_PANTALLA();

    printf("============================================================================\n");
    printf("      COMIENZA EJECUCION TEST DE DEBUG\n");
    printf("============================================================================\n");

    printf("\n\nPrueva de DEBUG_PRINT: DEBERIA APARECER\n");
    DEBUG_PRINT("Prueva de DEBUG_PRINT ... Pasada %i...%i...%i\n", 3, 2, 1);

    printf("\n\nPrueva de DEBUG_TRACE: DEBERIA APARECER\n");
    DEBUG_TRACE("Prueva de DEBUG_TRACE ... Pasada %i...%i...%i\n", 3, 2, 1);

    printf("\n\nPrueva de DEBUG_TRACE: DEBERIA APARECER\n");
    DEBUG_WARN_IF(5==5, "Prueva de DEBUG_TRACE ... Pasada %i...%i...%i\n", 5, 5, 1);
    printf("\n\nPrueva de DEBUG_TRACE: NO DEBERIA APARECER (por condicion)\n");
    DEBUG_WARN_IF(5==6, "Prueva de DEBUG_TRACE ... Pasada %i...%i...%i\n", 5, 6, 1);

    printf("\n\n\n");
    printf("============================================================================\n");
    printf("      FINALIZO EJECUCION TEST DE DEBUG\n");
    printf("============================================================================\n");

}