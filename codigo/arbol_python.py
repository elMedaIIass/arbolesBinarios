"""
Proyecto: Árbol Binario de Búsqueda (ABB) – Implementación manual vs lista ordenada + bisect
Lenguaje: Python 3
Operaciones: insertar, buscar, eliminar, recorridos
PoC: Directorio de contactos (nombres) ordenado alfabéticamente
Comparación de rendimiento: inserción y búsqueda de 1000 elementos
"""
from bisect import bisect_left, insort
import time
from pathlib import Path

class Node:
    __slots__=("key","left","right")
    def __init__(self, key):
        self.key=key; self.left=None; self.right=None

class BST:
    def __init__(self):
        self.root=None
    def insert(self, key):
        def _ins(n,k):
            if not n: return Node(k)
            if k<n.key: n.left=_ins(n.left,k)
            elif k>n.key: n.right=_ins(n.right,k)
            return n
        self.root=_ins(self.root,key)
    def find(self, key):
        n=self.root
        while n:
            if key==n.key: return True
            n = n.left if key<n.key else n.right
        return False
    def _min_node(self,n):
        while n and n.left: n=n.left
        return n
    def erase(self,key):
        def _del(n,k):
            if not n: return n
            if k<n.key: n.left=_del(n.left,k)
            elif k>n.key: n.right=_del(n.right,k)
            else:
                if not n.left: return n.right
                if not n.right: return n.left
                m=self._min_node(n.right)
                n.key=m.key
                n.right=_del(n.right,m.key)
            return n
        self.root=_del(self.root,key)
    def inorder(self):
        res=[]
        def _in(n):
            if not n: return
            _in(n.left); res.append(n.key); _in(n.right)
        _in(self.root); return res
    def preorder(self):
        res=[]
        def _pre(n):
            if not n: return
            res.append(n.key); _pre(n.left); _pre(n.right)
        _pre(self.root); return res
    def postorder(self):
        res=[]
        def _post(n):
            if not n: return
            _post(n.left); _post(n.right); res.append(n.key)
        _post(self.root); return res

def leer_nombres():
    ruta = Path(__file__).resolve().parent.parent / "documentacion" / "dataset_nombres.txt"
    if ruta.exists():
        return [x.strip() for x in ruta.read_text(encoding="utf-8").splitlines() if x.strip()]
    return ["Carlos","Ana","Diego","Elena","Bruno","Fabián","Laura","Miguel","Sofía"]

def poc_directorio():
    print("=== PoC ABB (Python) ===")
    nombres = leer_nombres()
    tree = BST()
    for n in nombres: tree.insert(n)

    print("\nInorden (alfabetico):", tree.inorder())
    print("Preorden:", tree.preorder())
    print("Postorden:", tree.postorder())

    print("\nBuscar 'Laura':", "SI" if tree.find("Laura") else "NO")
    print("Eliminar 'Diego'")
    tree.erase("Diego")
    print("Inorden tras eliminar:", tree.inorder())

def benchmark():
    N=1000
    keys=[f"Nombre_{i}" for i in range(N)]

    tree = BST()
    t1=time.time()
    for k in keys: tree.insert(k)
    t2=time.time()
    t_manual_insert = int((t2-t1)*1e6)

    t1=time.time()
    ok = tree.find("Nombre_777")
    t2=time.time()
    t_manual_find = int((t2-t1)*1e6)

    # Referencia: lista ordenada + bisect (como "set" ordenado sencillo)
    arr=[]
    t1=time.time()
    for k in keys: insort(arr, k)
    t2=time.time()
    t_list_insert = int((t2-t1)*1e6)

    t1=time.time()
    i = bisect_left(arr, "Nombre_777")
    ok2 = (i < len(arr) and arr[i]=="Nombre_777")
    t2=time.time()
    t_list_find = int((t2-t1)*1e6)

    print("\n== Benchmark (microsegundos) ==")
    print("BST manual - insertar 1000:", t_manual_insert)
    print("Lista ordenada (bisect) - insertar 1000:", t_list_insert)
    print("BST manual - buscar uno:", t_manual_find)
    print("Lista ordenada (bisect) - buscar uno:", t_list_find)

if __name__=="__main__":
    poc_directorio()
    benchmark()
    print("\nFin PoC ABB (Python)")
