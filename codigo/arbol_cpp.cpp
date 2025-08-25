#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>

using namespace std;

/*
  Proyecto: Árbol Binario de Búsqueda (ABB) – Implementación manual vs std::set
  Equipo B: Árboles Binarios
  Operaciones: insertar, buscar, eliminar, recorridos (inorden, preorden, postorden)
  PoC: Directorio de contactos (nombres) ordenado alfabéticamente
  Comparación de rendimiento: inserción y búsqueda de 1000 elementos
*/

struct Node{
    string key;
    Node *left, *right;
    Node(const string& k): key(k), left(nullptr), right(nullptr) {}
};

class BST {
    Node* root=nullptr;

    Node* insertRec(Node* n, const string& k){
        if(!n) return new Node(k);
        if(k < n->key) n->left = insertRec(n->left, k);
        else if(k > n->key) n->right = insertRec(n->right, k);
        return n;
    }
    Node* minNode(Node* n){
        while(n && n->left) n = n->left;
        return n;
    }
    Node* eraseRec(Node* n, const string& k){
        if(!n) return n;
        if(k < n->key) n->left = eraseRec(n->left, k);
        else if(k > n->key) n->right = eraseRec(n->right, k);
        else {
            if(!n->left){ Node* r=n->right; delete n; return r; }
            if(!n->right){ Node* l=n->left; delete n; return l; }
            Node* m = minNode(n->right);
            n->key = m->key;
            n->right = eraseRec(n->right, m->key);
        }
        return n;
    }
    bool findRec(Node* n, const string& k){
        if(!n) return false;
        if(k==n->key) return true;
        return k < n->key ? findRec(n->left,k) : findRec(n->right,k);
    }
    void inorderRec(Node* n){
        if(!n) return;
        inorderRec(n->left); cout<<n->key<<" "; inorderRec(n->right);
    }
    void preorderRec(Node* n){
        if(!n) return;
        cout<<n->key<<" "; preorderRec(n->left); preorderRec(n->right);
    }
    void postorderRec(Node* n){
        if(!n) return;
        postorderRec(n->left); postorderRec(n->right); cout<<n->key<<" ";
    }
    void freeRec(Node* n){
        if(!n) return;
        freeRec(n->left); freeRec(n->right); delete n;
    }
public:
    ~BST(){ freeRec(root); }
    void insert(const string& k){ root = insertRec(root,k); }
    void erase(const string& k){ root = eraseRec(root,k); }
    bool find(const string& k){ return findRec(root,k); }
    void inorder(){ inorderRec(root); cout<<"\n"; }
    void preorder(){ preorderRec(root); cout<<"\n"; }
    void postorder(){ postorderRec(root); cout<<"\n"; }
};

vector<string> leerNombres(const string& ruta){
    vector<string> v; ifstream in(ruta); string s;
    while(getline(in, s)){ if(!s.empty()) v.push_back(s); }
    return v;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << "=== PoC Arbol Binario de Busqueda (C++) ===\n";

    string rutaDataset = "../documentacion/dataset_nombres.txt";
    vector<string> nombres = leerNombres(rutaDataset);
    if(nombres.empty()){
        nombres = {"Carlos","Ana","Diego","Elena","Bruno","Fabian","Laura","Miguel","Sofia"};
    }

    // PoC: directorio (solo nombres, simulando contactos)
    BST tree;
    for(auto& n: nombres) tree.insert(n);

    cout << "\nInorden (alfabetico): ";
    tree.inorder();
    cout << "Preorden: ";
    tree.preorder();
    cout << "Postorden: ";
    tree.postorder();

    // Operaciones: buscar y eliminar
    cout << "\nBuscar 'Laura': " << (tree.find("Laura") ? "SI" : "NO") << "\n";
    cout << "Eliminar 'Diego'\n";
    tree.erase("Diego");
    cout << "Inorden tras eliminar: ";
    tree.inorder();

    // Comparación vs std::set
    const int N = 1000;
    vector<string> add;
    add.reserve(N);
    for(int i=0;i<N;i++) add.push_back("Nombre_"+to_string(i));

    // Insert BST manual
    auto t1 = chrono::high_resolution_clock::now();
    for(auto& s : add) tree.insert(s);
    auto t2 = chrono::high_resolution_clock::now();
    auto t_manual_insert = chrono::duration_cast<chrono::microseconds>(t2-t1).count();

    // Insert std::set
    set<string> st;
    t1 = chrono::high_resolution_clock::now();
    for(auto& s : add) st.insert(s);
    t2 = chrono::high_resolution_clock::now();
    auto t_set_insert = chrono::duration_cast<chrono::microseconds>(t2-t1).count();

    // Buscar en ambos
    string target = "Nombre_777";
    t1 = chrono::high_resolution_clock::now();
    bool f1 = tree.find(target);
    t2 = chrono::high_resolution_clock::now();
    auto t_manual_find = chrono::duration_cast<chrono::microseconds>(t2-t1).count();

    t1 = chrono::high_resolution_clock::now();
    bool f2 = st.find(target)!=st.end();
    t2 = chrono::high_resolution_clock::now();
    auto t_set_find = chrono::duration_cast<chrono::microseconds>(t2-t1).count();

    cout << "\n== Benchmark (microsegundos) ==\n";
    cout << "BST manual - insertar 1000: " << t_manual_insert << "\n";
    cout << "std::set    - insertar 1000: " << t_set_insert << "\n";
    cout << "BST manual - buscar uno: " << t_manual_find << "\n";
    cout << "std::set    - buscar uno: " << t_set_find << "\n";

    cout << "\nFin PoC ABB (C++)\n";
    return 0;
}
