#!/bin/bash
# Crear carpeta build, configurar y compilar en Linux/Mac
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
