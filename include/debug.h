#ifndef M_DEBUG
#define M_DEBUG

#include <stdio.h>

void log(char* arg,char* arg1, char* data){
    printf("[DEBUG] %s - %s: %s\n", arg, arg1, data);
}

void log(char* arg,char* arg1, int data){
    printf("[DEBUG] %s - %s: %d\n", arg, arg1, data);
}

void log(char* arg,char* arg1, unsigned long data){
    printf("[DEBUG] %s - %s: %lu\n", arg, arg1, data);
}

void log(char* arg, unsigned int arg1, char* data){
    printf("[DEBUG] %s - %u: %s\n", arg, arg1, data);
}
#endif
