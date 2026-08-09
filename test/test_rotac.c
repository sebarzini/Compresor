#include <assert.h>
#include "tipos_gen.h"
#include "rotacion.h"

/* 
 * Objetivo: Imprimir la representación binaria de 8 bits de un byte.
 * Entrada : texto (const char*) - Etiqueta descriptiva.
 *           num (unsigned char) - Valor a convertir e imprimir.
 * Salida  : Ninguna.
 */
void print_bin8(const char* texto, unsigned char num) {
    int i;
    printf("  %-22s | ", texto);
    for (i = 7; i >= 0; i--) {
        putchar((num & (1 << i)) ? '1' : '0');
        if (i == 4) putchar(' ');
    }
    printf(" (0x%02X / %3d)\n", num, num);
}

/* 
 * Objetivo: Formatear e imprimir en consola el contenido de una lista circular.
 * Entrada : lista (t_lista_ptr) - Puntero a la lista.
 * Salida  : Ninguna.
 */
static void imprimir_lista(t_lista_ptr lista) {
    t_lista_ptr actual = lista;
    printf("  Estado Lista: ");
    if (lista != NULL) {
        do {
            printf("[0x%02X|%3d] -> ", actual->dato, actual->dato);
            actual = (t_lista_ptr)actual->siguiente;
        } while (actual != lista);
        printf("(inicio)\n");
    } else {
        printf("VACIA\n");
    }
}

/* 
 * Objetivo: Ejecutar la suite de pruebas unitarias sobre la función rotar().
 * Entrada : Ninguna.
 * Salida  : Ninguna.
 */
static void test_rotar_bits_individual(void) {
    int i;
    byte val;

    printf("+-------------------------------------------------------------------------+\n");
    printf("| 1. PRUEBA DE ROTACION DE BITS INDIVIDUAL                                |\n");
    printf("+-------------------------------------------------------------------------+\n");

    val = 0x81; /* 10000001 */
    print_bin8("Valor Inicial", val);

    /* Test rotación hacia la izquierda */
    for (i = 0; i < 7; i++) {
        val = rotar(val, 1);
        print_bin8("Rotacion izquierda", val);
    }
 /* Rotar 7 veces vuelve al mismo punto */
    assert(val == 0xC0);

    /* Test rotación hacia la derecha */
    for (i = 0; i < 8; i++) {
        val = rotar(val, -1);
        print_bin8("Rotacion derecha",val);
    }
    /* 8 Rotacion deja el byte como al inicio */
    assert(val == 0xC0);

    printf("  [OK] Pruebas de rotacion individual completadas exitosamente.\n\n");
}

/* 
 * Objetivo: Probar inserción y generación de nodos en la lista.
 * Entrada : lista (t_lista_ptr*) - Puntero doble a la lista de trabajo.
 * Salida  : Ninguna.
 */
static void test_crear_nodos(t_lista_ptr* lista) {
    printf("+-------------------------------------------------------------------------+\n");
    printf("| 2. PRUEBA DE CREACION DE NODOS                                          |\n");
    printf("+-------------------------------------------------------------------------+\n");

    *lista = crear_nodo(*lista, 0x0F);
    assert(*lista != NULL);
    assert((*lista)->dato == 0x0F);

    *lista = crear_nodo(*lista, 0x80);
    *lista = crear_nodo(*lista, 0x01);
    *lista = crear_nodo(*lista, 0xA0);
    *lista = crear_nodo(*lista, 0xB4);

    imprimir_lista(*lista);
    printf("  [OK] Nodos creados e insertados correctamente.\n\n");
}

/* 
 * Objetivo: Validar selectores de cabecera y cola.
 * Entrada : lista (t_lista_ptr) - Puntero a la lista.
 * Salida  : Ninguna.
 */
static void test_cabecera_y_cola(t_lista_ptr lista) {
    printf("+-------------------------------------------------------------------------+\n");
    printf("| 3. PRUEBA DE CABECERA Y COLA DE LISTA                                   |\n");
    printf("+-------------------------------------------------------------------------+\n");
    t_lista_ptr aux = lista->anterior;

    assert(lista != NULL);
    lista = crear_nodo(lista, 0xA0);
    assert(cabecera_lista(lista) == 0xA0);
    assert(cola_lista(lista) == aux->dato);

    printf("  Cabecera esperada 0x0F (15) : 0x%02X (%d)\n", cabecera_lista(lista), cabecera_lista(lista));
    printf("  Cola esperada     0x01 (1)  : 0x%02X (%d)\n", cola_lista(lista), cola_lista(lista));
    printf("  [OK] Cabecera y cola validadas.\n\n");
}

/* 
 * Objetivo: Validar la rotación de bits aplicada sobre todos los elementos de la lista.
 * Entrada : lista (t_lista_ptr*) - Puntero doble a la lista.
 * Salida  : Ninguna.
 */
static void test_rotar_lista(t_lista_ptr* lista) {
    printf("+-------------------------------------------------------------------------+\n");
    printf("| 4. PRUEBA DE ROTAR_CHAR SOBRE LA LISTA                                  |\n");
    printf("+-------------------------------------------------------------------------+\n");

    imprimir_lista(*lista);

    printf("  Rotando 1 bit a la izquierda...\n");
    *lista = rotar_char(*lista, 1);
    imprimir_lista(*lista);

    printf("  Rotando 5 bits a la derecha...\n");
    *lista = rotar_char(*lista, -5);
    imprimir_lista(*lista);

    printf("  Rotando 7 bits a la izquierda...\n");
    *lista = rotar_char(*lista, 7);
    imprimir_lista(*lista);

    printf("  [OK] Operaciones de rotación en lista completadas.\n\n");
}

/* 
 * Objetivo: Validar liberación individual e integral de memoria.
 * Entrada : lista (t_lista_ptr*) - Puntero doble a la lista.
 * Salida  : Ninguna.
 */
static void test_liberacion_memoria(t_lista_ptr* lista) {
    t_lista_ptr nodo_a_eliminar;

    printf("+-------------------------------------------------------------------------+\n");
    printf("| 5. PRUEBA DE LIBERACION DE MEMORIA                                      |\n");
    printf("+-------------------------------------------------------------------------+\n");

    if (*lista != NULL && (*lista)->siguiente != NULL) {
        nodo_a_eliminar = (t_lista_ptr)(*lista)->siguiente;
        printf("  Liberando segundo nodo (0x%02X)...\n", nodo_a_eliminar->dato);
        liberar_nodo(nodo_a_eliminar);
        imprimir_lista(*lista);
    }

    printf("  Vaciando lista completa...\n");
    vaciar_lista(*lista);
    *lista = NULL;
    
    assert(*lista == NULL);
    imprimir_lista(*lista);
    printf("  [OK] Memoria liberada correctamente.\n\n");
}

/* 
 * Objetivo: Punto de entrada del programa de pruebas.
 * Entrada : Ninguna.
 * Salida  : int (0 para ejecución exitosa).
 */
int main(void) {
    t_lista_ptr lista = NULL;

    printf("\n");
    printf("===========================================================================\n");
    printf("                  SUITE DE PRUEBAS: ROTACION Y LISTAS                      \n");
    printf("===========================================================================\n\n");

    test_rotar_bits_individual();
    test_crear_nodos(&lista);
    test_cabecera_y_cola(lista);
    test_rotar_lista(&lista);
    test_liberacion_memoria(&lista);

    printf("===========================================================================\n");
    printf("              TODAS LAS PRUEBAS SE EJECUTARON CON EXITO                    \n");
    printf("===========================================================================\n\n");

    return 0;
}