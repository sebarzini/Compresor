#include "crypto.h"
#include "util.h"

/* Aplica el XOR de las cabeceras de ambas listas sobre el dato */
static byte mezclar_cabeceras(byte dato, t_lista_ptr listaPass, t_lista_ptr listaHash){
    return (byte)(dato ^ listaPass->dato ^ listaHash->dato);
}

/* Avanza ambas listas circulares en funcion de la semilla y de la longitud de la clave */
static void avanzar_listas(byte semilla, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass){
    *listaPass = rotar_char(*listaPass, semilla % get_primoA(lenPass));
    *listaHash = rotar_char(*listaHash, semilla % get_primoB(lenPass));
}

/* Recorre el buffer aplicando la transformacion byte a byte indicada */
static byte* aplicar_n(t_transformacion transformar, byte* buffer, int len,
                       t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass){
    byte* ret = (byte*)reservar_memoria(sizeof(byte) * (size_t)len, "el buffer codificado");
    if (ret == NULL) {
        return NULL;
    }
    for (int i = 0; i < len; i++){
        ret[i] = transformar(buffer[i], listaPass, listaHash, lenPass);
    }
    return ret;
}

t_lista_ptr getListaPass(char* pass){
    byte* campo = hash_pass(pass);
    t_lista_ptr ret = crear_lista(campo, (unsigned int)get_primoA(strlen(pass)));

    free(campo);
    return ret;
}

t_lista_ptr getListaHash(int len){
    byte* campo = random_bytes(len);
    t_lista_ptr ret = crear_lista(campo, (unsigned int)len);

    free(campo);
    return ret;
}

byte encode(byte dato, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass){
    byte ret = mezclar_cabeceras(dato, *listaPass, *listaHash);

    /* Al codificar, las rotaciones se derivan del byte ya cifrado */
    avanzar_listas(ret, listaPass, listaHash, lenPass);
    return ret;
}

byte decode(byte dato, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass){
    byte ret = mezclar_cabeceras(dato, *listaPass, *listaHash);

    /* Al decodificar, el byte cifrado es la entrada: con el se replican las rotaciones */
    avanzar_listas(dato, listaPass, listaHash, lenPass);
    return ret;
}

byte* encode_n(byte* buffer, int len, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass){
    return aplicar_n(encode, buffer, len, listaPass, listaHash, lenPass);
}

byte* decode_n(byte* buffer, int len, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenpass){
    return aplicar_n(decode, buffer, len, listaPass, listaHash, lenpass);
}

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
    
    byte* hash = (byte*)reservar_memoria(sizeof(byte) * len_salida, "el hash");
    if (hash == NULL) {
        return NULL;
    }
    
// Creación del estado circular (9*X bytes):
//      Se inicializa un lista rotativa en RAM, que contendrá los caracteres de la contraseña y se rotará en cada iteración.
    t_lista_ptr lista = NULL;
    rotacion_inicial = 0; // Inicializamos la rotación inicial a cero
    
// Modifico el valor de cada byte de la contraseña, rotándolo en función del primo y del índice,
//      y lo inserto en la lista circular.
    for (unsigned int indice = 0; indice < len_salida; indice++) {
        byte dato = pass[indice % len_pass]; //Obtengo el byte de la contraseña, repitiéndolo si es necesario
        rotacion_inicial ^= dato;
        rotacion = ((primo * dato)+ indice) % 8; // Rotación de 0 a 7 bits
        dato = rotar(dato, rotacion); // Rotar el byte antes de insertarlo en la lista
        lista = crear_nodo(lista, dato);
    }

    rotacion_inicial = rotacion_inicial % len_salida; // Aseguramos que la rotación inicial esté dentro del rango de la lista
    // Se realiza la rotación de la lista circular en rotacion_inicial.
        lista = rotar_char(lista, rotacion_inicial);

// Se extraen los bytes de la lista circular y se almacenan en el hash de salida.
    for (unsigned int indice = 0; indice < len_salida; indice++) {
        rotacion = (primo * indice)% len_salida;
        lista = rotar_char(lista, rotacion); // Rotar la lista en cada iteración
        hash[indice] = lista->dato;
    }

    vaciar_lista(lista);
    return hash;
} 

byte* random_bytes(int n){
    
    byte* bytes = (byte*)reservar_memoria(sizeof(byte) * (size_t)n, "los bytes aleatorios");
    if (bytes == NULL) {
        return NULL;
    }
    memset(bytes, 0, n); // Inicializa la memoria a cero

    for (int i = 0; i < n; i++) {
        bytes[i] = get_random_byte();
    }

    return bytes;
}