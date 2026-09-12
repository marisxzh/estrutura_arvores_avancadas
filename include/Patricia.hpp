#ifndef PATRICIA_HPP
#define PATRICIA_HPP

#include <string>
#include <unordered_map>

using namespace std;

// estrutura do nó
struct PatriciaNo {

    // label -> trecho da chave armazenado neste nó/aresta
    string label;

    // filhos -> ponteiros para os filhos do nó, indexados pelo primeiro caractere do label do filho
    unordered_map<char, PatriciaNo*> filhos;

    // indica se o nó marca o fim de uma palavra válida
    bool finalPalavra;

    PatriciaNo(const string& lbl);

};

// classe principal que vai gerenciar a árvore
class Patricia {

    private:
        PatriciaNo* raiz;

        // auxiliares recursivos (vamos implementar nas próximas etapas)
        void destruirAux(PatriciaNo* atual);


        bool removerAux(PatriciaNo* atual, const string& palavra, size_t pos);

        // [MÉTRICAS]
        long long comparacoes = 0;
        int alturaAux(PatriciaNo* atual);

    public:

        // inicia a árvore com um nó raiz vazio
        Patricia();

        // destrutor para liberar a memória alocada para os nós da árvore
        ~Patricia();

        void inserir(const string& palavra);

        bool buscar(const string& palavra);

        bool remover(const string& palavra);

        // [MÉTRICAS]
        long long getComparacoes() const;
        int obterAltura();

};

#endif