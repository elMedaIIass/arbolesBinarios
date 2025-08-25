#!/bin/bash

# Script para compilar y ejecutar la PoC del ABB automáticamente

# Nombre del archivo fuente
SRC="arbol_cpp.cpp"

# Nombre del ejecutable
EXE="arbol_cpp"

# Compilar
echo "Compilando $SRC..."
g++ -std=c++17 -Wall -O2 -finput-charset=UTF-8 -fexec-charset=UTF-8 "$SRC" -o "$EXE"

# Verificar si compiló
if [ $? -ne 0 ]; then
    echo "Error en compilación. Revisa tu código."
    exit 1
fi

# Ejecutar
echo "Ejecutando PoC..."
./"$EXE"

echo "¡Fin de la PoC!"
