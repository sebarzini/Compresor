#include "crypto.h"

/* Construye una lista circular con los bytes de campo; NULL si algun nodo falla */
static t_lista_ptr lista_desde_bytes(const byte* campo, int len){
    t_lista_ptr ret = NULL;
    int i;

    for (i = 0; i < len; i++){
        t_lista_ptr nueva = crear_nodo(ret, campo[i]);
        if (nueva == NULL) {
            vaciar_lista(ret);
            return NULL;
        }
        ret = nueva;
    }

    return ret;
}

t_lista_ptr getListaPass(char* pass){
    t_lista_ptr ret = NULL;
    byte* campo = NULL;
    int len = 0;

    if (pass == NULL || pass[0] == '\0') {
        fprintf(stderr, "getListaPass: la clave no puede ser vacia.\n");
        return NULL;
    }

    campo = hash_pass(pass);
    if (campo == NULL) {
        return NULL;
    }

    len = get_primoA(strlen(pass));
    ret = lista_desde_bytes(campo, len);
    free(campo);

    if (ret == NULL) {
        fprintf(stderr, "getListaPass: no se pudo construir la lista de clave.\n");
    }

    return ret;
}

t_lista_ptr getListaHash(int len){
    t_lista_ptr ret = NULL;
    byte* campo = NULL;

    if (len <= 0) {
        fprintf(stderr, "getListaHash: longitud invalida (%d).\n", len);
        return NULL;
    }

    campo = random_bytes(len);
    if (campo == NULL) {
        return NULL;
    }

    ret = lista_desde_bytes(campo, len);
    free(campo);

    if (ret == NULL) {
        fprintf(stderr, "getListaHash: no se pudo construir la lista de hash.\n");
    }

    return ret;
}

byte encode(byte dato, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass){

    byte ret = 0;
    byte a;

    if (listaPass == NULL || listaHash == NULL ||
        *listaPass == NULL || *listaHash == NULL) {
        fprintf(stderr, "encode: listas de estado invalidas.\n");
        return dato;
    }

    a = (*listaPass)->dato;
    byte b = (*listaHash)->dato;
    
    // XOR con las cabeceras.
    ret = dato;
    ret ^= a;
    ret ^= b;
    int rotacionA = ret % get_primoA(lenPass);
    int rotacionB = ret % get_primoB(lenPass);

    // rotar listas
    *listaPass = rotar_char(*listaPass, rotacionA);
    *listaHash = rotar_char(*listaHash, rotacionB);
    return ret;
}

byte decode(byte dato, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass){
    byte ret = 0;
    byte a;
    byte b;
    int rotacionA;
    int rotacionB;

    if (listaPass == NULL || listaHash == NULL ||
        *listaPass == NULL || *listaHash == NULL) {
        fprintf(stderr, "decode: listas de estado invalidas.\n");
        return dato;
    }

    rotacionA = dato % get_primoA(lenPass);
    rotacionB = dato % get_primoB(lenPass);

    // XOR con las cabeceras.
    a = (*listaPass)->dato;
    b = (*listaHash)->dato;
    ret = dato;
    ret ^= a;
    ret ^= b;
 
    // rotar lista de pass
    *listaPass = rotar_char(*listaPass, rotacionA);
    *listaHash = rotar_char(*listaHash, rotacionB);
    
    return ret;
}

byte* encode_n(byte* buffer, int len, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass){
    byte* ret = NULL;

    if (buffer == NULL || len <= 0 ||
        listaPass == NULL || listaHash == NULL ||
        *listaPass == NULL || *listaHash == NULL) {
        fprintf(stderr, "encode_n: argumentos invalidos.\n");
        return NULL;
    }

    ret = (byte*)malloc(sizeof(byte) * (size_t)len);
    if (ret == NULL) {
        fprintf(stderr, "Error al asignar memoria para el buffer codificado.\n");
        return NULL;
    }
    for (int i = 0; i < len; i++){
        ret[i] = encode(buffer[i], listaPass, listaHash, lenPass);
    }
    return ret;
}

byte* decode_n(byte* buffer, int len, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenpass){
    byte* ret = NULL;

    if (buffer == NULL || len <= 0 ||
        listaPass == NULL || listaHash == NULL ||
        *listaPass == NULL || *listaHash == NULL) {
        fprintf(stderr, "decode_n: argumentos invalidos.\n");
        return NULL;
    }

    ret = (byte*)malloc(sizeof(byte) * (size_t)len);
    if (ret == NULL) {
        fprintf(stderr, "Error al asignar memoria para el buffer decodificado.\n");
        return NULL;
    }

    for (int i = 0; i < len; i++){
        ret[i] = decode(buffer[i], listaPass, listaHash, lenpass);
    }
    return ret;
}

byte* hash_pass(char* pass){

// Obtención del primo mapeado ($P$):
//      En función de la longitud X de la contraseña (1 < X < 32),
//      se obtiene un número primo $P$ desde una tabla predefinida e indexada
//      por X en código C.

    unsigned int len_pass;
    unsigned int len_salida;
    unsigned int primo;
    unsigned int rotacion_inicial = 0;
    unsigned int rotacion;
    byte* hash;

    if (pass == NULL || pass[0] == '\0') {
        fprintf(stderr, "hash_pass: la clave no puede ser vacia.\n");
        return NULL;
    }

    len_pass = (unsigned int)strlen(pass);
    len_salida = (unsigned int)get_primoA(len_pass);
    primo = (unsigned int)get_primoB(len_pass);

// Se reserva memoria para el hash de salida, que tendrá una longitud de len bytes.

    hash = (byte*)malloc(sizeof(byte) * len_salida);
    if (hash == NULL) {
        fprintf(stderr, "Error al asignar memoria para el hash.\n");
        return NULL;
    }
    
// Creación del estado circular (9*X bytes):
//      Se inicializa un lista rotativa en RAM, que contendrá los caracteres de la contraseña y se rotará en cada iteración.
    t_lista_ptr lista = NULL;
    t_lista_ptr nueva = NULL;
    rotacion_inicial = 0; // Inicializamos la rotación inicial a cero
    
// Modifico el valor de cada byte de la contraseña, rotándolo en función del primo y del índice,
//      y lo inserto en la lista circular.
    for (unsigned int indice = 0; indice < len_salida; indice++) {
        byte dato = pass[indice % len_pass]; //Obtengo el byte de la contraseña, repitiéndolo si es necesario
        rotacion_inicial ^= dato;
        rotacion = ((primo * dato)+ indice) % 8; // Rotación de 0 a 7 bits
        dato = rotar(dato, rotacion); // Rotar el byte antes de insertarlo en la lista
        nueva = crear_nodo(lista, dato);
        if (nueva == NULL) {
            fprintf(stderr, "hash_pass: fallo la creacion del estado circular.\n");
            vaciar_lista(lista);
            free(hash);
            return NULL;
        }
        lista = nueva;
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
    byte* bytes = NULL;

    if (n <= 0) {
        fprintf(stderr, "random_bytes: cantidad invalida (%d).\n", n);
        return NULL;
    }

    bytes = (byte*)malloc(sizeof(byte) * (size_t)n);
    if (bytes == NULL) {
        fprintf(stderr, "Error al asignar memoria para los bytes aleatorios.\n");
        return NULL;
    }
    memset(bytes, 0, (size_t)n); // Inicializa la memoria a cero

    for (int i = 0; i < n; i++) {
        bytes[i] = (byte)(rand() % 256); // Genera un byte aleatorio entre 0 y 255
    }

    return bytes;
}