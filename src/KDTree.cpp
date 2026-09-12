#include "KDTree.hpp"
#include <cmath>

using namespace std;


// inicializa o nó com as coordenadas recebidas
// por padrão, o nó nasce sem filhos
KDNo::KDNo(int xValor, int yValor) {
    x = xValor;
    y = yValor;
    esq = nullptr;
    dir = nullptr;
}


// inicia a árvore vazia, sem nenhum nó ainda
KDTree::KDTree() {
    raiz = nullptr;
}


// inicia a limpeza a partir do nó raiz
KDTree::~KDTree() {
    destruirAux(raiz);
}


// função auxiliar para destruir a árvore recursivamente
void KDTree::destruirAux(KDNo* no) {

    if (no == nullptr) {
        return;
    }

    destruirAux(no->esq);
    destruirAux(no->dir);

    delete no;
}


// função auxiliar recursiva: desce alternando o eixo de comparação a cada nível
KDNo* KDTree::inserirAux(KDNo* no, int x, int y, int profundidade) {

    comparacoes++; // [MÉTRICAS]

    // 1. achou o lugar vazio -> cria o nó aqui
    if (no == nullptr) {
        return new KDNo(x, y);
    }

    // profundidade par -> compara por X; profundidade ímpar -> compara por Y
    bool comparaPorX = (profundidade % 2 == 0);

    // se for par (compara por X), decide se vai para a esquerda ou direita
    if (comparaPorX) {
        if (x < no->x) {
            no->esq = inserirAux(no->esq, x, y, profundidade + 1);
        } else {
            no->dir = inserirAux(no->dir, x, y, profundidade + 1);
        }
    }
    // se for ímpar (compara por Y), decide se vai para a esquerda ou direita
    else {
        if (y < no->y) {
            no->esq = inserirAux(no->esq, x, y, profundidade + 1);
        } else {
            no->dir = inserirAux(no->dir, x, y, profundidade + 1);
        }
    }

    return no;
}


// insere o ponto (x, y) na árvore, começando na profundidade 0
void KDTree::inserir(int x, int y) {
    comparacoes = 0; // [MÉTRICAS]
    raiz = inserirAux(raiz, x, y, 0);
}


// função auxiliar recursiva: desce alternando o eixo de comparação, procurando o ponto exato
bool KDTree::buscarAux(KDNo* no, int x, int y, int profundidade) {

    comparacoes++; // [MÉTRICAS]

    // não encontrou -> chegou a um ponto vazio
    if (no == nullptr) {
        return false;
    }

    // encontrou o ponto exato (compara as duas coordenadas, não só uma)
    if (no->x == x && no->y == y) {
        return true;
    }

    // mesma questão do inserir
    bool comparaPorX = (profundidade % 2 == 0);

    // faz o suposto caminho da inserção, mas não cria nada, só procura o ponto exato
    if (comparaPorX) {
        if (x < no->x) {
            return buscarAux(no->esq, x, y, profundidade + 1);
        } else {
            return buscarAux(no->dir, x, y, profundidade + 1);
        }
    }
    else {
        if (y < no->y) {
            return buscarAux(no->esq, x, y, profundidade + 1);
        } else {
            return buscarAux(no->dir, x, y, profundidade + 1);
        }
    }
}


// busca o ponto (x, y) na árvore
bool KDTree::buscar(int x, int y) {

    comparacoes = 0; // [MÉTRICAS]

    return buscarAux(raiz, x, y, 0);
}


// encontra, dentro da subárvore, o nó com menor valor no eixo indicado (0 = X, 1 = Y)
KDNo* KDTree::encontrarMinimo(KDNo* no, int eixoAlvo, int profundidade) {

    comparacoes++; // [MÉTRICAS]

    // se achar um nó nulo, retorna nulo
    if (no == nullptr) {
        return nullptr;
    }

    // verifica qual eixo estamos comparando neste nível da árvore
    int eixoAtual = profundidade % 2;

    // se o eixo atual É o eixo que queremos minimizar (comparar x ou y), só precisa olhar a subárvore esquerda (menor valor sempre à esquerda)
    if (eixoAtual == eixoAlvo) {
        if (no->esq == nullptr) {
            return no;
        }
        // se houver filho esquerdo, continua descendo por ele
        return encontrarMinimo(no->esq, eixoAlvo, profundidade + 1);
    }

    // se o eixo atual NÃO é o eixo que queremos minimizar, o mínimo pode estar dos dois lados
    // (a esquerda/direita aqui só reflete o OUTRO eixo, não dá pista sobre o eixoAlvo)
    KDNo* minEsq = encontrarMinimo(no->esq, eixoAlvo, profundidade + 1);
    KDNo* minDir = encontrarMinimo(no->dir, eixoAlvo, profundidade + 1);

    // assume que o nó atual é o menor, e compara com os mínimos das subárvores esquerda e direita
    KDNo* menor = no;

    // função lambda para pegar o valor do nó no eixo desejado, evitando duplicação de código
    // Ela recebe um nó n e devolve só a coordenada que nos interessa: se eixoAlvo == 0 (X), devolve n->x; senão, devolve n->y. Isso evita repetir esse if/else várias vezes nas linhas seguintes — criamos essa "mini-função" uma vez, e usamos várias vezes como valorNoEixo(algumNo).
    auto valorNoEixo = [eixoAlvo](KDNo* n) {
        return (eixoAlvo == 0) ? n->x : n->y;
    };

    // compara os três nós (atual, mínimo da esquerda, mínimo da direita) e retorna o menor
    if (minEsq != nullptr && valorNoEixo(minEsq) < valorNoEixo(menor)) {
        menor = minEsq;
    }
    if (minDir != nullptr && valorNoEixo(minDir) < valorNoEixo(menor)) {
        menor = minDir;
    }

    return menor;
}


// função auxiliar recursiva: localiza o ponto e o remove, usando o mínimo do eixo como substituto
KDNo* KDTree::removerAux(KDNo* no, int x, int y, int profundidade) {

    comparacoes++; // [MÉTRICAS]

    if (no == nullptr) {
        return nullptr;
    }

    int eixoAtual = profundidade % 2;

    if (no->x == x && no->y == y) {
        // encontrou o ponto a remover

        if (no->dir != nullptr) {
            // busca o mínimo no eixo atual, dentro da subárvore direita
            KDNo* minimo = encontrarMinimo(no->dir, eixoAtual, profundidade + 1);

            // copia as coordenadas do mínimo para o nó atual
            no->x = minimo->x;
            no->y = minimo->y;

            // remove o ponto duplicado (o "mínimo" original) da subárvore direita
            no->dir = removerAux(no->dir, minimo->x, minimo->y, profundidade + 1);
        }
        else if (no->esq != nullptr) {
            // não há filho direito, mas há esquerdo -> mesmo truque, usando a subárvore esquerda
            KDNo* minimo = encontrarMinimo(no->esq, eixoAtual, profundidade + 1);

            no->x = minimo->x;
            no->y = minimo->y;

            // a subárvore esquerda, já sem o "minimo", passa a ser a nova subárvore direita
            no->dir = removerAux(no->esq, minimo->x, minimo->y, profundidade + 1);
            no->esq = nullptr;
        }
        else {
            // é uma folha -> remove direto
            delete no;
            return nullptr;
        }

        return no;
    }

    // não é o ponto procurado -> continua descendo, alternando eixo, igual à busca
    bool comparaPorX = (eixoAtual == 0);
    if (comparaPorX) {
        // se for par (compara por X), decide se vai para a esquerda ou direita
        if (x < no->x) {
            no->esq = removerAux(no->esq, x, y, profundidade + 1);
        } else {
            no->dir = removerAux(no->dir, x, y, profundidade + 1);
        }
    }
    else {
        // se for ímpar (compara por Y), decide se vai para a esquerda ou direita
        if (y < no->y) {
            no->esq = removerAux(no->esq, x, y, profundidade + 1);
        } else {
            no->dir = removerAux(no->dir, x, y, profundidade + 1);
        }
    }

    return no;
}


// remove o ponto (x, y) da árvore, caso exista
bool KDTree::remover(int x, int y) {

    comparacoes = 0; // [MÉTRICAS]

    if (!buscar(x, y)) {
        return false;
    }

    raiz = removerAux(raiz, x, y, 0);
    return true;
}


// função auxiliar recursiva: mantém o melhor candidato encontrado até agora (por referência)
void KDTree::vizinhoMaisProximoAux(KDNo* no, int x, int y, int profundidade, KDNo*& melhor, double& melhorDistancia) {

    comparacoes++; // [MÉTRICAS]

    // se achar nulo, retorna (não há nada a fazer)
    if (no == nullptr) {
        return;
    }

    // calcula a distância entre o ponto buscado e o nó atual
    double dx = no->x - x;
    double dy = no->y - y;
    double distanciaAtual = sqrt(dx * dx + dy * dy);

    // se ainda não há melhor candidato, ou se o nó atual é mais próximo, atualiza o melhor
    if (melhor == nullptr || distanciaAtual < melhorDistancia) {
        melhor = no;
        melhorDistancia = distanciaAtual;
    }

    // decide qual eixo comparar neste nível da árvore
    bool comparaPorX = (profundidade % 2 == 0);

    // decide o "lado bom" (onde a navegação normal mandaria ir) e o "lado ruim" (o outro)
    KDNo* ladoBom;
    KDNo* ladoRuim;
    int diferencaEixo; // distância até a linha de corte deste nível

    // o lado bom é o que está na direção do ponto buscado, e o lado ruim é o outro
    // se diferencaEixo < 0, o ponto buscado está à esquerda, então ladoBom = no->esq e ladoRuim = no->dir; caso contrário, ladoBom = no->dir e ladoRuim = no->esq
    if (comparaPorX) {
        diferencaEixo = x - no->x;
        ladoBom = (diferencaEixo < 0) ? no->esq : no->dir;
        ladoRuim = (diferencaEixo < 0) ? no->dir : no->esq;
    } else {
        diferencaEixo = y - no->y;
        ladoBom = (diferencaEixo < 0) ? no->esq : no->dir;
        ladoRuim = (diferencaEixo < 0) ? no->dir : no->esq;
    }

    // sempre explora o lado bom primeiro
    vizinhoMaisProximoAux(ladoBom, x, y, profundidade + 1, melhor, melhorDistancia);

    // só explora o lado ruim SE houver chance de existir algo mais próximo ali
    // (ou seja, se a distância até a linha de corte for menor que a melhor distância já encontrada)
    if (abs(diferencaEixo) < melhorDistancia) {
        vizinhoMaisProximoAux(ladoRuim, x, y, profundidade + 1, melhor, melhorDistancia);
    }
}


// retorna o ponto mais próximo de (x, y), ou nullptr se a árvore estiver vazia
KDNo* KDTree::vizinhoMaisProximo(int x, int y) {

    comparacoes = 0; // [MÉTRICAS]

    KDNo* melhor = nullptr;
    double melhorDistancia = 0.0;

    vizinhoMaisProximoAux(raiz, x, y, 0, melhor, melhorDistancia);

    return melhor;
}



// função auxiliar recursiva: acumula no vetor todos os pontos dentro do retângulo dado
void KDTree::buscarRegiaoAux(KDNo* no, int xMin, int xMax, int yMin, int yMax, int profundidade, std::vector<KDNo*>& resultado) {

    comparacoes++; // [MÉTRICAS]

    if (no == nullptr) {
        return;
    }

    // verifica se o próprio nó está dentro da região
    if (no->x >= xMin && no->x <= xMax && no->y >= yMin && no->y <= yMax) {
        resultado.push_back(no);
    }

    bool comparaPorX = (profundidade % 2 == 0);

    // decide se precisa explorar a esquerda e/ou a direita
    if (comparaPorX) {
        if (xMin <= no->x) {
            buscarRegiaoAux(no->esq, xMin, xMax, yMin, yMax, profundidade + 1, resultado);
        }
        if (xMax >= no->x) {
            buscarRegiaoAux(no->dir, xMin, xMax, yMin, yMax, profundidade + 1, resultado);
        }
    }
    else {
        if (yMin <= no->y) {
            buscarRegiaoAux(no->esq, xMin, xMax, yMin, yMax, profundidade + 1, resultado);
        }
        if (yMax >= no->y) {
            buscarRegiaoAux(no->dir, xMin, xMax, yMin, yMax, profundidade + 1, resultado);
        }
    }
}


// retorna todos os pontos dentro do retângulo [xMin,xMax] x [yMin,yMax]
vector<KDNo*> KDTree::buscarRegiao(int xMin, int xMax, int yMin, int yMax) {

    comparacoes = 0; // [MÉTRICAS]

    vector<KDNo*> resultado;
    buscarRegiaoAux(raiz, xMin, xMax, yMin, yMax, 0, resultado);
    return resultado;
}


// [MÉTRICAS]
long long KDTree::getComparacoes() const {
    return comparacoes;
}


int KDTree::alturaAux(KDNo* no) {
    if (no == nullptr) {
        return -1;
    }
    int alturaEsq = alturaAux(no->esq);
    int alturaDir = alturaAux(no->dir);
    return 1 + (alturaEsq > alturaDir ? alturaEsq : alturaDir);
}


int KDTree::obterAltura() {
    return alturaAux(raiz);
}
