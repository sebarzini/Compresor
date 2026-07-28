#!/bin/bash
# Crear carpeta build, configurar y compilar en Linux/Mac
cmake -B build -S . && cmake --build build
