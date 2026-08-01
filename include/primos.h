#ifndef MTH_PRIMOS_H
#define MTH_PRIMOS_H

/* Objetivo: Devuelve un byte aleatorio.
   Entrada: Ninguna (requiere inicializacion previa de srand() en el programa principal).
   Salida: Un valor entero sin signo de 8 bits (0 a 255). */
unsigned char get_random_byte(void);

/* Objetivo: Generar una cadena determinista de longitud X con caracteres mezclados, basada en una cadena de entrada.
   Entrada: input (cadena base), x (longitud deseada), out (buffer pre-asignado de tamaño x + 1).
   Salida: Puntero al buffer out con caracteres ASCII imprimibles pseudoaleatorios. */
char* get_deterministic_hash(const char *input, int x, char *out);

/* Objetivo: Generar una cadena de caracteres aleatoria de longitud Y.
   Entrada: y (longitud deseada), out (buffer pre-asignado de tamaño y + 1).
   Salida: Puntero al buffer out con caracteres ASCII imprimibles aleatorios. */
char* get_random_string(int y, char *out);

/* Objetivo: Obtener un numero primo menor a 100 asociado a un numero de entrada (lista 1).
   Entrada: n (numero entero cualquiera).
   Salida: Un numero primo predefinido, constante para el mismo valor de n. */
int get_primoA(unsigned int n);

/* Objetivo: Obtener un numero primo menor a 100 asociado a un numero de entrada (lista 2).
   Entrada: n (numero entero cualquiera).
   Salida: Un numero primo predefinido, constante para el mismo valor de n, diferente al de get_primoA. */
int get_primoB(unsigned int n);

#endif