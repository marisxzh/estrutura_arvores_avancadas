#ifndef SPLAY_HPP
#define SPLAY_HPP

using namespace std;


// estrutura do nó
struct SplayNo {

    // chave -> valor armazenado no nó, usado para ordenação (esquerda menor, direita maior)
    int chave;

    // ponteiros para os filhos e para o pai (necessário para as rotações do splay)
    SplayNo* esq;
    SplayNo* dir;
    SplayNo* pai;

    SplayNo(int valor);

};

// classe principal que vai gerenciar a árvore
class Splay {

    private:
        SplayNo* raiz;

        // rotações básicas, usadas como blocos de construção do splay
        void rotacionarDireita(SplayNo* no);
        void rotacionarEsquerda(SplayNo* no);

        // move o nó para a raiz através de uma sequência de rotações (zig / zig-zig / zig-zag)
        void splay(SplayNo* no);

        // auxiliar para o destrutor, que vai limpar a árvore recursivamente
        void destruirAux(SplayNo* atual);

        // [MÉTRICAS]
        long long comparacoes = 0;
        int alturaAux(SplayNo* no);

    public:

        // inicia a árvore vazia (sem nó raiz)
        Splay();

        // destrutor para liberar a memória alocada para os nós da árvore
        ~Splay();

        void inserir(int valor);

        // retorna true se o valor estiver na árvore, false caso contrário
        bool buscar(int valor);

        bool remover(int valor);

        // [MÉTRICAS]
        long long getComparacoes() const;
        int obterAltura();
        
};


#endif