#include <iostream>
#include <string>
#include "Trie.hpp"
#include "Patricia.hpp"
#include "Splay.hpp"
#include "Treap.hpp"



using namespace std;


int main() {


    // ARVORE TRIE
    Trie trie;


    cout << "\n\n   --- ÁRVORE TRIE ---   " << endl;

    trie.inserir("casa");
    trie.inserir("casal");
    trie.inserir("carro");

    // Imprime true/false ao invés de 1/0
    cout << boolalpha; 
    cout << "Busca 'casa': " << trie.buscar("casa") << endl;     // true
    cout << "Busca 'cas': " << trie.buscar("cas") << endl;       // false
    cout << "Comeca com 'ca': " << trie.comecaCom("ca") << endl; // true

    trie.remover("casa");
    cout << "Busca 'casa' apos remocao: " << trie.buscar("casa") << endl;  // false
    cout << "Busca 'casal' apos remocao de 'casa': " << trie.buscar("casal") << endl; // true



    cout << "\n\n   --- ÁRVORE PATRICIA ---   " << endl;



    // ARVORE PATRICIA
    Patricia patricia;

    
    patricia.inserir("comer");
    patricia.inserir("comida");
    patricia.inserir("com");

    // Imprime true/false ao invés de 1/0
    cout << boolalpha;
    cout << "Busca 'comer': " << patricia.buscar("comer") << endl;   // true
    cout << "Busca 'com': " << patricia.buscar("com") << endl;       // true
    cout << "Busca 'co': " << patricia.buscar("co") << endl;         // false

    patricia.remover("com");
    cout << "Busca 'com' apos remocao: " << patricia.buscar("com") << endl;     // false
    cout << "Busca 'comer' apos remocao de 'com': " << patricia.buscar("comer") << endl; // true


    // ARVORE SPLAY
    cout << "\n\n   --- ÁRVORE SPLAY ---   " << endl;
    Splay splay;

    splay.inserir(50);
    splay.inserir(30);
    splay.inserir(70);
    splay.inserir(20);
    splay.inserir(40);

    // Imprime true/false ao invés de 1/0
    cout << boolalpha;
    cout << "Busca 40: " << splay.buscar(40) << endl;   // true (e 40 deve virar a raiz)
    cout << "Busca 100: " << splay.buscar(100) << endl; // false (nao existe)

    cout << "Remove 30: " << splay.remover(30) << endl; // true
    cout << "Busca 30 apos remocao: " << splay.buscar(30) << endl; // false
    cout << "Busca 20 apos remocao de 30: " << splay.buscar(20) << endl; // true

    cout << "Remove 999 (nao existe): " << splay.remover(999) << endl; // false


    // ÁRVORE TREAP
    cout << "\n\n   --- ÁRVORE TREAP ---   " << endl;
    Treap treap;

    treap.inserir(50);
    treap.inserir(30);
    treap.inserir(70);
    treap.inserir(20);
    treap.inserir(40);
    treap.inserir(60);
    treap.inserir(80);

    // Imprime true/false ao invés de 1/0
    cout << boolalpha;
    cout << "Busca 40: " << treap.buscar(40) << endl;   // true
    cout << "Busca 100: " << treap.buscar(100) << endl; // false (nao existe)

    cout << "Remove 30 (tem filhos): " << treap.remover(30) << endl; // true
    cout << "Busca 30 apos remocao: " << treap.buscar(30) << endl;   // false
    cout << "Busca 20 apos remocao de 30: " << treap.buscar(20) << endl; // true
    cout << "Busca 40 apos remocao de 30: " << treap.buscar(40) << endl; // true

    cout << "Remove 999 (nao existe): " << treap.remover(999) << endl; // false

    treap.inserir(30); // reinsere, testando se a arvore continua consistente
    cout << "Busca 30 apos reinsercao: " << treap.buscar(30) << endl; // true

    
    return 0;
}