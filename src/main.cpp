#include <iostream>
#include <string>
#include "Trie.hpp"
#include "Patricia.hpp"


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

    return 0;
}