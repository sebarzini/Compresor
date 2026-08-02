#include "rotacion.h"

t_lista_ptr rotar_char(t_lista_ptr lista, int n){
    t_lista_ptr aux = lista;
    int i;

    if (lista != NULL) {
        for (i = abs(n); i > 0; i--) {
            if (n > 0) aux = aux->siguiente;
            else aux = aux->anterior;
        }
    }
    return aux;
}


byte rotar(byte b, int n){
    byte rotar = n % 8;
    byte ret = b;
    if (n > 0){
        ret = (b << rotar) | (b >> (8 - rotar));
    } else {
        ret = (b >> (-n % 8)) | (b << (8 - (-n % 8)));
    }
    return ret;
}

t_lista_ptr crear_nodo(t_lista_ptr lista, byte dato){
    t_lista_ptr nuevo_nodo = (t_lista_ptr)malloc(sizeof(struct t_lista));
    if (nuevo_nodo != NULL) {
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
    } else {
        printf("Error al asignar memoria para el nuevo nodo.\n");
    }

    return nuevo_nodo;
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
    if (lista != NULL) return lista->dato;
    return 0; // Valor predeterminado si la lista está vacía
}

byte cola_lista(t_lista_ptr lista){
    t_lista_ptr aux = lista;
    if (aux != NULL) return aux->dato;
    return 0; // Valor predeterminado si la lista está vacía
}