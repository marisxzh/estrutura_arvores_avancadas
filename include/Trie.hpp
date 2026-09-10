#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>
#include <unordered_map>

using namespace std;

// estrutura do nó
struct TrieNo {

    // cria o filho só quando necessário
    unordered_map<char, TrieNo*> filho;

    // se for o fim de uma palavra o valor é true, mas o valor atribuido inicialmente é false
    bool fimpalavra;

    TrieNo();

};

// classe principal que vai gerenciar a árvore
class Trie {

    // ponteiro para o nó raiz
    // privado pois não queremos que o usuário da classe tenha acesso a ele
    private:
        TrieNo* raiz;

        // auxiliar para a função de remover, que vai percorrer a árvore recursivamente
        bool removerAux(TrieNo* atual, const string& palavra, int index);

        // auxiliar para o destrutor, que vai limpar a árvore recursivamente 
        void destruirAux(TrieNo* atual);

    // métodos para inserir, buscar e remover palavras da árvore
    public:

        // iniciar a arvore com um nó raiz
        Trie();

        // destrutor para liberar a memória alocada para os nós da árvore
        ~Trie();

        void inserir(const string& palavra);

        // retorna true se a palavra estiver na árvore, false caso contrário
        bool buscar(const string& palavra);
        // busca se existe alguma palavra na árvore que comece com o prefixo dado
        bool comecaCom(const string& prefixo);
        
        bool remover(const string& palavra);

        
};


#endif