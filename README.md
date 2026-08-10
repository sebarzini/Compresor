# Compilador / Compresor en C

Este proyecto es un compresor/encriptador de alto rendimiento desarrollado puramente en ANSI C. 

## 🚀 Características y Objetivos
- **Multiplataforma:** Diseñado para compilar y funcionar tanto en Linux como en Windows.
- **Seguridad e Integridad:** Utiliza firmas CRC-32 (IEEE 802.3) para validar la integridad del archivo.
- **Formato propio:** Genera archivos binarios con extensión `.MZI` / `.huff`.
- **Modularidad:** El código está separado lógicamente en `src/`, `include/` y `test/`.

## 🛠️ Requisitos
- Compilador de C (GCC / MinGW / MSVC).
- [CMake](https://cmake.org/) (versión 3.15 o superior).
- Opcional: Valgrind y GDB para pruebas de memoria en Linux.

## ⚙️ Compilación

El proyecto utiliza CMake para facilitar la compilación en cualquier sistema operativo.

### En Linux (usando CMake)
    ./compilar.sh

### En Windows (usando CMake)
    -compi.bat

🧪 Pruebas
Los tests unitarios se encuentran en la carpeta test/. Una vez compilado el proyecto, puedes ejecutar los binarios de prueba generados en tu carpeta build/.