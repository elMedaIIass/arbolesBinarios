"""
Demostración para Equipo B – Árboles Binarios (ABB)
Corre PoC y benchmarks de Python.
"""
import subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
COD = ROOT / "codigo"

def main():
    print("Demostración – ABB (Python)")
    subprocess.run([sys.executable, str(COD / "arbol_python.py")], check=False)
    print("\nPara C++:")
    print("  g++ -O2 -std=c++17 codigo/arbol_cpp.cpp -o arbol_cpp && ./arbol_cpp")
    print("\nFin demo.")

if __name__ == "__main__":
    main()
