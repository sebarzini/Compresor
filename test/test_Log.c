#include "../include/Log.h"

int main() {
    LOG("Hello, world!");
    LOG("This is a log message. %i", 42);
    LOG("Another log message. %s", "Hello");
    LOG("Yet another log message. %f", 3.14);
    return 0;
}