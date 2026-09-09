#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <vector>

using namespace std;

// estrutura do nó
struct KDNo {

    // coordenadas do ponto armazenado
    int x;
    int y;

    // ponteiros para os filhos (sem "pai" — igual à Treap, rotações/remoção serão recursivas)
    KDNo* esq;
    KDNo* dir;

    KDNo(int xValor, int yValor);

};

// classe principal que vai gerenciar a árvore
class KDTree {

    private:
        KDNo* raiz;

        // funções auxiliares recursivas
        KDNo* inserirAux(KDNo* no, int x, int y, int profundidade);
        bool buscarAux(KDNo* no, int x, int y, int profundidade);
        KDNo* removerAux(KDNo* no, int x, int y, int profundidade);
        void destruirAux(KDNo* no);

        // encontra, dentro de uma subárvore, o nó com menor valor num eixo específico
        // (necessário para a remoção de nós com dois filhos)
        KDNo* encontrarMinimo(KDNo* no, int eixoAlvo, int profundidade);

        // vizinho mais próximo (busca espacial)
        void vizinhoMaisProximoAux(KDNo* no, int x, int y, int profundidade, KDNo*& melhor, double& melhorDistancia);

        // busca por região retangular (busca espacial)
        void buscarRegiaoAux(KDNo* no, int xMin, int xMax, int yMin, int yMax, int profundidade, std::vector<KDNo*>& resultado);

    public:

        // inicia a árvore vazia (sem nó raiz)
        KDTree();

        // destrutor para liberar a memória alocada para os nós da árvore
        ~KDTree();

        void inserir(int x, int y);

        bool buscar(int x, int y);

        bool remover(int x, int y);

        // retorna o ponto mais próximo de (x, y), ou nullptr se a árvore estiver vazia
        KDNo* vizinhoMaisProximo(int x, int y);

        // retorna todos os pontos dentro do retângulo [xMin,xMax] x [yMin,yMax]
        vector<KDNo*> buscarRegiao(int xMin, int xMax, int yMin, int yMax);

};

#endif