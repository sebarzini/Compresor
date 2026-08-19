#include "crypto.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <bcrypt.h>
#else
#include <errno.h>
#endif

boolean bytes_aleatorios_seguros(byte* out, size_t len){
    if (out == NULL || len == 0) {
        return FALSE;
    }

#if defined(_WIN32) || defined(_WIN64)
    return BCryptGenRandom(NULL, out, (ULONG)len,
                           BCRYPT_USE_SYSTEM_PREFERRED_RNG) == 0 ? TRUE : FALSE;
#else
    {
        FILE* urandom = fopen("/dev/urandom", "rb");
        size_t leidos;

        if (urandom == NULL) {
            return FALSE;
        }
        leidos = fread(out, 1, len, urandom);
        fclose(urandom);
        return (leidos == len) ? TRUE : FALSE;
    }
#endif
}

t_lista_ptr getListaPass(char* pass){
    t_lista_ptr ret = NULL;
    byte* campo;
    int len;

    if (pass == NULL || pass[0] == '\0') {
        return NULL;
    }

    campo = hash_pass(pass);
    if (campo == NULL) {
        return NULL;
    }

    len = get_primoA(strlen(pass));

    for (int i = 0; i < len; i++){
        ret = crear_nodo (ret, campo[i]);
    }
    /* El material derivado de la clave se borra antes de liberarlo */
    memset(campo, 0, (size_t)len);
    free(campo);
    return ret;
}

t_lista_ptr getListaHash(int len){
    t_lista_ptr ret = NULL;
    byte* campo;

    if (len <= 0) {
        return NULL;
    }

    campo = random_bytes(len);
    if (campo == NULL) {
        return NULL;
    }

    for (int i = 0; i < len; i++){
        ret = crear_nodo (ret, campo[i]);
    }
    memset(campo, 0, (size_t)len);
    free(campo);
    return ret;
}

byte encode(byte dato, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass){

    byte ret = 0;
    if (listaPass == NULL || listaHash == NULL ||
        *listaPass == NULL || *listaHash == NULL) {
        return dato;
    }
    byte a = (*listaPass)->dato;
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
    if (listaPass == NULL || listaHash == NULL ||
        *listaPass == NULL || *listaHash == NULL) {
        return dato;
    }
    int rotacionA = dato % get_primoA(lenPass);
    int rotacionB = dato % get_primoB(lenPass);
    
    // XOR con las cabeceras.
    byte a = (*listaPass)->dato;
    byte b = (*listaHash)->dato;
    ret = dato;
    ret ^= a;
    ret ^= b;
 
    // rotar lista de pass
    *listaPass = rotar_char(*listaPass, rotacionA);
    *listaHash = rotar_char(*listaHash, rotacionB);
    
    return ret;
}

byte* encode_n(byte* buffer, int len, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenPass){
    if (buffer == NULL || len <= 0) {
        return NULL;
    }
    byte* ret = (byte*)malloc(sizeof(byte) * (size_t)len);
    if (ret == NULL) {
        printf("Error al asignar memoria para el buffer codificado.\n");
        return NULL;
    }
    for (int i = 0; i < len; i++){
        ret[i] = encode(buffer[i], listaPass, listaHash, lenPass);
    }
    return ret;
}

byte* decode_n(byte* buffer, int len, t_lista_ptr* listaPass, t_lista_ptr* listaHash, unsigned int lenpass){
    if (buffer == NULL || len <= 0) {
        return NULL;
    }
    byte* ret = (byte*)malloc(sizeof(byte) * (size_t)len);
    if (ret == NULL) {
        printf("Error al asignar memoria para el buffer codificado.\n");
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

    if (pass == NULL || pass[0] == '\0') {
        return NULL; /* Sin clave no hay hash: evita strlen(NULL) y el modulo por cero */
    }

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

/* Bytes aleatorios de calidad criptografica: rand() es predecible (semilla
   derivada del reloj) y no sirve para material de clave. Si el sistema no
   puede proveer entropia, la funcion falla en lugar de degradarse. */
byte* random_bytes(int n){
    byte* bytes;

    if (n <= 0) {
        return NULL;
    }

    bytes = (byte*)malloc(sizeof(byte) * (size_t)n);
    if (bytes == NULL) {
        printf("Error al asignar memoria para los bytes aleatorios.\n");
        return NULL;
    }
    memset(bytes, 0, (size_t)n);

    if (!bytes_aleatorios_seguros(bytes, (size_t)n)) {
        printf("Error: no se pudo obtener entropia segura del sistema.\n");
        free(bytes);
        return NULL;
    }

    return bytes;
}