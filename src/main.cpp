#include <iostream>
#include <string>
#include "Trie.hpp"


using namespace std;


int main() {
    Trie trie;

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

    return 0;
}