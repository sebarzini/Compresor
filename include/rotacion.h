#ifndef MTH_ROTACION_H
#define MTH_ROTACION_H

#include "tipos_gen.h"


struct t_lista{
    void* anterior;
    byte dato;
    void* siguiente;
};

typedef struct t_lista* t_lista_ptr;

byte rotar(byte b, int n);
t_lista_ptr rotar_char(t_lista_ptr lista, int n);

void print_bin8(const char* texto, unsigned char num);
t_lista_ptr crear_nodo(t_lista_ptr nodo, byte dato);
t_lista_ptr liberar_nodo(t_lista_ptr nodo);
void vaciar_lista(t_lista_ptr lista);
byte cabecera_lista(t_lista_ptr lista);
byte cola_lista(t_lista_ptr lista);
t_lista_ptr crear_lista(void* p_arreglo, unsigned int cantidad);

#endif // MTH_ROTACION_H
