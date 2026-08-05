#include "tipos_gen.h"
#include "rotacion.h"

static void imprimir_lista(t_lista_ptr lista) {
    t_lista_ptr actual = lista;
    printf("Lista: ");
    if (lista != NULL) {
        do {
            printf(" [0x%02X (%d)] -", actual->dato, actual->dato);
            actual = (t_lista_ptr)actual->siguiente;
        } while (actual != lista);
    } else {
        printf("Lista vacia\n");
    }
    printf("\n\n");
}

int main(void) {
    t_lista_ptr n1 = NULL;
    t_lista_ptr n2 = NULL;
    t_lista_ptr n3 = NULL;
    t_lista_ptr lista = NULL;
    byte valor_rotado;

    printf("=== PRUEBAS DE FUNCIONES DE LISTA ===\n\n");

    /* 1. Prueba de rotar bits individual */
    printf("--- Test: rotar() ---\n");
    printf("Valor esperado: 0x03 (3)\n");
    valor_rotado = rotar(0x81, 1); /* 10000001 rotado 1 bit a la izq = 00000011 (0x03) */
    printf("Rotar 0x81 (129) por 1 bit: 0x%02X (%d)\n\n", valor_rotado, valor_rotado);
    printf("Valor esperado: 0x06 (6)\n");
    valor_rotado = rotar(valor_rotado, 1); /* 00000011 rotado 1 bit a la izq = 00000110 (0x06) */
    printf("Rotar 0x03 (3) por 1 bit: 0x%02X (%d)\n\n", valor_rotado, valor_rotado);
    printf("Valor esperado: 0x0C (12)\n");
    valor_rotado = rotar(valor_rotado, 1); /* 00000110 rotado 1 bit a la izq = 00001100 (0x0C) */
    printf("Rotar 0x06 (6) por 1 bit: 0x%02X (%d)\n\n", valor_rotado, valor_rotado);

    /* 2. Prueba de crear_nodo */
    printf("--- Test: crear_nodo() ---\n");

    lista = crear_nodo(lista, 0x0F); /* Nodo inicial: 15 */
    n1 = lista; /* Guardar referencia al primer nodo */
    printf("--- Test: nodo(1) = %u ---\n", n1->dato);

    lista = crear_nodo(lista, 0x80);   /* Segundo nodo: 128 */
    n2 = lista; /* Guardar referencia al segundo nodo */
    printf("--- Test: nodo(2) = %u ---\n", n2->dato);

    lista = crear_nodo(lista, 0x01);   /* Tercer nodo: 1 */
    n3 = lista; /* Guardar referencia al tercer nodo */
    printf("--- Test: nodo(3) = %u ---\n", n3->dato);

    imprimir_lista(lista);
    printf("\n");

    /* 3. Prueba de cabecera_lista y cola_lista */
    printf("--- Test: cabecera_lista() y cola_lista() ---\n");
    printf("Cabecera esperada 0x0F (15): 0x%02X (%d)\n", cabecera_lista(lista), cabecera_lista(lista));
    printf("Cola esperada 0x01 (1):      0x%02X (%d)\n\n", cola_lista(lista), cola_lista(lista));

    /* 4. Prueba de rotar_char sobre la lista */
    printf("--- Test: rotar_char() ---\n");
    printf("Rotando todos los elementos de la lista...3 veces\n");
    imprimir_lista(lista);
    printf("Rotando 1 bit a la izquierda\n");
    lista = rotar_char(lista, 1);
    imprimir_lista(lista);
    printf("Rotando 5 bit a la derecha\n");
    lista = rotar_char(lista, -5);
    imprimir_lista(lista);
    printf("Rotando 7 bit a la izquierda\n");
    lista = rotar_char(lista, 7);
    imprimir_lista(lista);
    printf("\n");

    /* 5. Prueba de liberar_nodo */
    printf("--- Test: liberar_nodo() ---\n");
    printf("Liberando nodo central (n2)...\n");
    liberar_nodo(n2);
    imprimir_lista(lista);
 
    /* 6. Prueba de vaciar_lista */
    printf("--- Test: vaciar_lista() ---\n");
    vaciar_lista(lista);
    lista = NULL; // Asegurarse de que la lista esté vacía
    printf("Lista vaciada correctamente.\n");

    return 0;
}