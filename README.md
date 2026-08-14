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
    compi.bat

## 🔐 Notas de seguridad
- La clave (`-p`) **nunca** se escribe en el log: solo se registra si fue provista o no.
- El archivo de log se crea con permisos `0600` (solo el propietario puede leerlo).
- El material aleatorio de cifrado proviene del generador del sistema
  (`/dev/urandom` / `BCryptGenRandom`); si no hay entropia disponible la operacion falla.
- Las macros de traza (`DEBUG_*`) solo se activan en builds `Debug`.
- **Pendiente:** pasar la clave por linea de comandos la deja visible en la lista de
  procesos (`ps`) y en el historial del shell. Conviene leerla por entrada interactiva
  o desde una variable de entorno.
- El esquema de cifrado propio (XOR + rotaciones) no equivale a un cifrado autenticado
  estandar (p. ej. AES-GCM) y no deberia usarse para proteger datos sensibles.

🧪 Pruebas
Los tests unitarios se encuentran en la carpeta test/. Una vez compilado el proyecto, puedes ejecutar los binarios de prueba generados en tu carpeta build/.
