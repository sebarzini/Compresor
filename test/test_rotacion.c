#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rotacion.h"

/* 
 * NOTA: Asumimos que 'byte' está definido en "tipos_gen.h". 
 * Si no es así al compilar el test de forma aislada, puedes descomentar la siguiente línea:
 * typedef unsigned char byte;
 */

void test_rotar() {
    printf("Testeando funcion rotar()...\n");
    byte b = 0x01; // 0000 0001
    
    // Rotar a la izquierda (n > 0)
    assert(rotar(b, 1) == 0x02); // 0000 0010
    assert(rotar(b, 2) == 0x04); // 0000 0100
    assert(rotar(b, 8) == 0x01); // 8 posiciones (vuelta completa)
    assert(rotar(b, 9) == 0x02); // 9 posiciones equivalen a 1
    
    // Rotar a la derecha (n < 0)
    assert(rotar(0x02, -1) == 0x01); // 0000 0010 -> 0000 0001
    assert(rotar(0x01, -1) == 0x80); // 0000 0001 -> 1000 0000
    assert(rotar(0x80, -8) == 0x80); // -8 posiciones (vuelta completa)
    
    // Rotar 0 posiciones (caso límite)
    assert(rotar(0x55, 0) == 0x55);
    
    printf("  [OK] rotar() supero las pruebas.\n");
}

void test_listas() {
    printf("Testeando funciones de lista (crear, rotar_char, liberar, vaciar)...\n");
    
    // 1. Crear nodo en lista vacía
    t_lista_ptr lista = crear_nodo(NULL, 10);
    assert(lista != NULL);
    assert(lista->dato == 10);
    assert(lista->siguiente == lista); // Verifica circularidad
    assert(lista->anterior == lista);  // Verifica circularidad
    assert(cabecera_lista(lista) == 10);
    
    // NOTA: Segun la implementacion de rotacion.c, cola_lista devuelve lo mismo que cabecera_lista
    assert(cola_lista(lista) == 10); 

    // 2. Agregar más nodos (la función los inserta antes de 'lista')
    t_lista_ptr nodo2 = crear_nodo(lista, 20); // Se inserta entre lista->anterior y lista
    t_lista_ptr nodo3 = crear_nodo(lista, 30);
    
    // Verificamos los enlaces generados
    assert(lista->siguiente == nodo2);
    assert(nodo2->siguiente == nodo3);
    assert(nodo3->siguiente == lista);
    printf("Prueva 2 EXITOSA\n");
// 2.5 Verificar enlaces anteriores
    assert(lista->anterior == nodo3);
    assert(nodo3->anterior == nodo2);
    assert(nodo2->anterior == lista);
    printf("Prueva 2.5 EXITOSA\n");
    
    // 3. Testear rotar_char (movimiento por la lista)
    // Rotar 1 posición adelante (n > 0)
    t_lista_ptr rotado_der = rotar_char(lista, 1);
    assert(rotado_der == nodo2);
    
    // Rotar 2 posiciones adelante
    assert(rotar_char(lista, 2) == nodo3);
    
    // Rotar 1 posición hacia atrás (n < 0)
    printf("Dato anterior a rotar_char(lista, -1): %d\n", lista->dato);
    t_lista_ptr aux = lista->anterior;
    assert(aux == nodo3);
    printf("Dato anterior a rotar_char(lista, -1): %d\n", aux->dato);
    t_lista_ptr rotado_izq = rotar_char(lista, -1);
    assert(rotado_izq == nodo3);
    
    // Rotar 0 posiciones
    assert(rotar_char(lista, 0) == lista);

    // 4. Testear liberar_nodo
    t_lista_ptr sig = liberar_nodo(nodo2);
    assert(sig == nodo3); // Debe retornar el nodo siguiente al liberado
    assert(lista->siguiente == nodo3); // El enlace del previo debe haberse corregido
    assert(nodo3->anterior == lista);  // El enlace del siguiente debe haberse corregido

    // 5. Testear vaciar_lista
    vaciar_lista(lista); // Esto liberará los nodos restantes (10 y 30)
    
    // Si llegamos hasta aquí sin violaciones de segmento, la liberación fue exitosa.
    printf("  [OK] Funciones de listas superaron las pruebas.\n");
}

int main() {
    printf("========================================\n");
    printf(" Iniciando bateria de pruebas unitarias\n");
    printf("========================================\n\n");
    
    test_rotar();
    test_listas();
    
    printf("\n========================================\n");
    printf(" Todas las pruebas finalizaron con exito.\n");
    printf("========================================\n");
    
    return 0;
}
