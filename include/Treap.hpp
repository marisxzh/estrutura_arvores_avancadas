#ifndef TREAP_HPP
#define TREAP_HPP

using namespace std;


// estrutura do nó
struct TreapNo {

    // chave -> valor armazenado, usado para ordenação (esquerda menor, direita maior), igual a uma BST
    int chave;

    // prioridade -> valor aleatório, usado para decidir a forma da árvore (pai sempre maior que os filhos)
    int prioridade;

    // ponteiros para os filhos (sem "pai", pois as rotações aqui serão recursivas)
    TreapNo* esq;
    TreapNo* dir;

    TreapNo(int chaveValor, int prioridadeValor);

};

// classe principal que vai gerenciar a árvore
class Treap {

    private:
        TreapNo* raiz;

        // rotações, iguais em princípio às da Splay, mas retornando o novo topo (sem mexer em "pai")
        TreapNo* rotacionarDireita(TreapNo* no);
        TreapNo* rotacionarEsquerda(TreapNo* no);

        // funções auxiliares recursivas
        TreapNo* inserirAux(TreapNo* no, int chave, int prioridade);
        TreapNo* removerAux(TreapNo* no, int chave);
        bool buscarAux(TreapNo* no, int chave);
        void destruirAux(TreapNo* no);

        // [MÉTRICAS]
        long long comparacoes = 0;
        int alturaAux(TreapNo* no);

    public:

        // inicia a árvore vazia (sem nó raiz)
        Treap();

        // destrutor para liberar a memória alocada para os nós da árvore
        ~Treap();

        void inserir(int chave);

        bool buscar(int chave);

        bool remover(int chave);

        // [MÉTRICAS]
        long long getComparacoes() const;
        int obterAltura();

};

#endif