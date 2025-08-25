#!/bin/bash

# Script para compilar y ejecutar la PoC del ABB
# y guardar toda la salida en resultado.txt

SRC="/Users/alejandromedellin/Downloads/Entrega_EquipoB_Arboles/codigo/arbol_cpp.cpp"
EXE="arbol_cpp"
OUTPUT="resultado.txt"

# Limpiar archivo anterior
rm -f "$OUTPUT"

# Compilar
echo "Compilando $SRC..." | tee -a "$OUTPUT"
g++ -std=c++17 -Wall -O2 -finput-charset=UTF-8 -fexec-charset=UTF-8 "$SRC" -o "$EXE" 2>&1 | tee -a "$OUTPUT"

# Verificar si compiló
if [ $? -ne 0 ]; then
    echo "Error en compilación. Revisa tu código." | tee -a "$OUTPUT"
    exit 1
fi

# Ejecutar y guardar salida
echo "Ejecutando PoC..." | tee -a "$OUTPUT"
./"$EXE" 2>&1 | tee -a "$OUTPUT"

echo "¡Fin de la PoC! Salida guardada en $OUTPUT" | tee -a "$OUTPUT"
