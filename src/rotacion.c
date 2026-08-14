#include "rotacion.h"
#include "util.h"

t_lista_ptr rotar_char(t_lista_ptr lista, int n){
    t_lista_ptr aux = lista;
    int max = (n>0) ? n : -n;

    if (lista != NULL) {
        if (n == 0) return lista; // No hay rotación necesaria
        if (n > 0) {
            for (int i = 0; i < max; i++) {
                aux = aux->siguiente;
            }
        } else {
            for (int i = 0; i < max; i++) {
                aux = aux->anterior;
            }
        }
    }
    return aux;
}


byte rotar(byte b, int n){
    byte rotar = abs(n % 8);
    byte ret = b;
    if (n > 0){
        ret = (byte)(b << rotar) | (b >> (8 - rotar));
    } else {
        ret = (byte)(b >> rotar) | (b << (8 - rotar));
    }
    return ret;
}

void print_bin8(const char* texto, unsigned char num) {
    int i;
    printf("  %-22s | ", texto);
    for (i = 7; i >= 0; i--) {
        putchar((num & (1 << i)) ? '1' : '0');
        if (i == 4) putchar(' ');
    }
    printf(" (0x%02X / %3d)\n", num, num);
}

t_lista_ptr crear_nodo(t_lista_ptr lista, byte dato){
    t_lista_ptr nuevo_nodo = (t_lista_ptr)reservar_memoria(sizeof(struct t_lista), "el nuevo nodo");
    if (nuevo_nodo != NULL) {
        memset(nuevo_nodo, 0, sizeof(struct t_lista)); // Inicializa la memoria a cero
        // Inicializar el nuevo nodo
        nuevo_nodo->dato = dato;
        if (lista == NULL) {
            nuevo_nodo->anterior = nuevo_nodo;
            nuevo_nodo->siguiente = nuevo_nodo;
        } else {
            t_lista_ptr ant = lista->anterior;
            t_lista_ptr sig = lista;
            nuevo_nodo->siguiente = sig;
            nuevo_nodo->anterior = ant;
            sig->anterior = nuevo_nodo;
            ant->siguiente = nuevo_nodo;
        }
    }

    return nuevo_nodo;
}

t_lista_ptr crear_lista(void* p_arreglo, unsigned int cantidad){
    t_lista_ptr lista = NULL;
    byte* datos = (byte*)p_arreglo;
    unsigned int i;

    if (datos == NULL) {
        return NULL;
    }

    for (i = 0; i < cantidad; i++) {
        lista = crear_nodo(lista, datos[i]);
    }

    return lista;
}

t_lista_ptr liberar_nodo(t_lista_ptr nodo){
    t_lista_ptr ret = NULL;
    t_lista_ptr aux = NULL;

    if (nodo != NULL) {

        if (nodo->siguiente == nodo) {
            // Si es el único nodo en la lista, simplemente liberarlo
            nodo->anterior = NULL;
            nodo->siguiente = NULL;
            free(nodo);
            return NULL;
        }
        ret = nodo->siguiente;
        if (nodo->anterior != NULL) {
            aux = nodo->anterior;
            aux->siguiente = ret;
        }
        if (nodo->siguiente != NULL) {
            ret->anterior = nodo->anterior;
        }

        nodo->anterior = NULL;
        nodo->siguiente = NULL;
        nodo->dato = 0;
        free(nodo);
    }

    return ret;
}

void vaciar_lista(t_lista_ptr lista){
    t_lista_ptr aux = lista;

    while (aux != NULL){
        aux = liberar_nodo(aux);
    } 
}

byte cabecera_lista(t_lista_ptr lista){
    if (lista != NULL){
        return lista->dato;
    }
    return 0; // Valor predeterminado si la lista está vacía
}

void imprimir_lista(const char* etiqueta, t_lista_ptr lista, size_t limite){
    t_lista_ptr actual = lista;
    size_t impresos = 0;

    printf("  %-22s: ", (etiqueta != NULL) ? etiqueta : "Estado Lista");
    if (lista == NULL) {
        printf("VACIA\n");
        return;
    }

    do {
        printf("[0x%02X|%3d] -> ", actual->dato, actual->dato);
        actual = (t_lista_ptr)actual->siguiente;
        impresos++;
    } while (actual != lista && impresos < limite);

    printf((actual == lista) ? "(inicio)\n" : "...\n");
}

byte cola_lista(t_lista_ptr lista){
    t_lista_ptr aux = lista;
    if (aux != NULL){
        t_lista_ptr ultimo = aux->anterior;
        return ultimo->dato;
    }
    return 0; // Valor predeterminado si la lista está vacía
}