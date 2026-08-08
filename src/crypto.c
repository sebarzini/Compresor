#include "crypto.h"
/*
boolean pass_check(char* pass, byte* hash){
    unsigned int len_pass = strlen(pass);
    unsigned int len_hash = get_primoA(len_pass);
    boolean resultado = FALSE;

    byte* hash_calculado = hash_pass(pass);
    if (hash_calculado == NULL) {
        printf("Error al calcular el hash de la contraseña.\n");
        return 0; // Retorna falso si hay un error
    }

    resultado = (memcmp(hash_calculado, hash, len_hash) == 0);
    free(hash_calculado);
    return resultado;
}
*/
t_lista_ptr getListaPass(char* pass){
    t_lista_ptr ret = NULL;
    byte* campo = hash_pass(pass);
    int len = get_primoA(strlen(pass));

    for (int i = 0; i < len; i++){
        ret = crear_nodo (ret, campo[i]);
    }
    free(campo);
    return ret;
}

t_lista_ptr getListaHash(int len){
    t_lista_ptr ret = NULL;
    byte* campo = random_bytes(len);

    for (int i = 0; i < len; i++){
        ret = crear_nodo (ret, campo[i]);
    }
    free(campo);
    return ret;
}

byte encode(byte dato, t_lista_ptr* listaPass, t_lista_ptr* listaHash){
    byte ret = 0;
    byte b = (*listaHash)->dato;
    byte a = (*listaPass)->dato;
    
    // XOR con las cabeceras.
    ret = dato ^ a ^ b;
    int rotacionA = ret%11;

    // rotar lista de pass
//    *listaPass = rotar_char(*listaPass, rotacionA);
printf(">> Rotando lista de pass %d posiciones [%i](%i - %i).\n", rotacionA, dato, a, b);
    // rotar lista de Hash
    *listaHash = rotar_char(*listaHash, -ret%5);
    return ret;
}

byte decode(byte dato, t_lista_ptr* listaPass, t_lista_ptr* listaHash){
    byte ret = 0;
    int rotacionA = -(dato%11);
    
    // rotar lista de pass
    //*listaPass = rotar_char(*listaPass, rotacionA);
    // rotar lista de Hash
    *listaHash = rotar_char(*listaHash, dato%5);
    // XOR con las cabeceras.
    byte a = (*listaPass)->dato;
    byte b = (*listaHash)->dato;
    ret = dato ^ a ^ b;
   
    printf("<< Rotando lista de pass %d posiciones [%i](%i - %i).\n", rotacionA, ret, a, b);
    return ret;
}

byte* encode_n(byte* buffer, int len, t_lista_ptr* listaPass, t_lista_ptr* listaHash){
    byte* ret = (byte*)malloc(sizeof(byte) * len);
    if (ret == NULL) {
        printf("Error al asignar memoria para el buffer codificado.\n");
        return NULL;
    }
    for (int i = 0; i < len; i++){
        ret[i] = encode(buffer[i], listaPass, listaHash);
    }
    return ret;
}

byte* decode_n(byte* buffer, int len, t_lista_ptr* listaPass, t_lista_ptr* listaHash){
    byte* ret = (byte*)malloc(sizeof(byte) * len);
    if (ret == NULL) {
        printf("Error al asignar memoria para el buffer codificado.\n");
        return NULL;
    }

    for (int i = 0; i < len; i++){
        ret[i] = decode(buffer[i], listaPass, listaHash);
    }
    return ret;
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
        int rotacion = ((primo * dato)+ indice) % 8; // Rotación de 0 a 7 bits
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