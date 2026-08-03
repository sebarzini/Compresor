#include "crypto.h"


byte* hash_pass(char* pass){

// Obtención del primo mapeado ($P$):
//      En función de la longitud X de la contraseña (1 < X < 32),
//      se obtiene un número primo $P$ desde una tabla predefinida e indexada
//      por X en código C.

    unsigned int len_pass = strlen(pass);
    unsigned int len_salida = get_primoA(len_pass);
    unsigned int primo = get_primoB(len_pass);
    unsigned int rotacion_inicial = 0;
    unsigned int rotacion;


// Se reserva memoria para el hash de salida, que tendrá una longitud de len bytes.
    
    byte* hash = (byte*)malloc(sizeof(byte) * len_salida);
    if (hash == NULL) {
        printf("Error al asignar memoria para el hash.\n");
        return NULL;
    }
    
// Creación del estado circular (9*X bytes):
//      Se inicializa un lista rotativa en RAM, que contendrá los caracteres de la contraseña y se rotará en cada iteración.
    t_lista_ptr lista = NULL;
    
// Modifico el valor de cada byte de la contraseña, rotándolo en función del primo y del índice,
//      y lo inserto en la lista circular.
    for (unsigned int indice = 0; indice < len_salida; indice++) {
        byte dato = pass[indice % len_pass];
        rotacion_inicial = (rotacion_inicial + dato) % len_salida;
        int rotacion = ((primo * dato)+ indice) % 8; // Rotación de 0 a 7 bits
        rotar( (byte)dato, rotacion); // Rotar el byte antes de insertarlo en la lista
        lista = crear_nodo(lista, dato);
    }

// Se realiza la rotación de la lista circular en rotacion_inicial.
        lista = rotar_char(lista, rotacion_inicial);

// Se extraen los bytes de la lista circular y se almacenan en el hash de salida.
    for (unsigned int indice = 0; indice < len_salida; indice++) {
        hash[indice] = lista->dato;
        rotacion = (primo * indice)% len_salida;
        lista = rotar_char(lista, rotacion); // Rotar la lista en cada iteración
    }

    vaciar_lista(lista);
    return hash;
} 

byte* random_bytes(int n){
    
    byte* bytes = (byte*)malloc(sizeof(byte) * n);
    if (bytes == NULL) {
        printf("Error al asignar memoria para los bytes aleatorios.\n");
        return NULL;
    }
    memset(bytes, 0, n); // Inicializa la memoria a cero

    for (int i = 0; i < n; i++) {
        bytes[i] = (byte)(rand() % 256); // Genera un byte aleatorio entre 0 y 255
    }

    return bytes;
}