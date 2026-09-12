#include "Treap.hpp"
// biblioteca para gerar números aleatórios
#include <cstdlib>
#include <ctime>

using namespace std;


// inicializa o nó com a chave e a prioridade recebidas
// por padrão, o nó nasce sem filhos
TreapNo::TreapNo(int chaveValor, int prioridadeValor) {
    chave = chaveValor;
    prioridade = prioridadeValor;
    esq = nullptr;
    dir = nullptr;
}


// inicia a árvore vazia, sem nenhum nó ainda
Treap::Treap() {
    raiz = nullptr;
    srand(time(nullptr)); // inicializa a semente do gerador aleatório, uma vez por árvore
}


// inicia a limpeza a partir do nó raiz
Treap::~Treap() {
    destruirAux(raiz);
}


// função auxiliar para destruir a árvore recursivamente
void Treap::destruirAux(TreapNo* no) {

    if (no == nullptr) {
        return;
    }

    destruirAux(no->esq);
    destruirAux(no->dir);

    delete no;

}


// rotação à direita: o filho esquerdo de 'no' sobe, 'no' desce e vira filho direito dele
// retorna o novo nó que deve ficar nessa posição da árvore
TreapNo* Treap::rotacionarDireita(TreapNo* no) {

    TreapNo* esquerdo = no->esq;

    // o filho direito do "esquerdo" vira o novo filho esquerdo de "no"
    no->esq = esquerdo->dir;

    // "no" vira filho direito de "esquerdo"
    esquerdo->dir = no;

    return esquerdo; // "esquerdo" é o novo topo desse trecho da árvore
}


// rotação à esquerda: o filho direito de 'no' sobe, 'no' desce e vira filho esquerdo dele
// mesmo processo da rotação à direita, mas invertido
TreapNo* Treap::rotacionarEsquerda(TreapNo* no) {

    TreapNo* direito = no->dir;

    no->dir = direito->esq;

    direito->esq = no;

    return direito;
}


// função auxiliar recursiva: desce como uma BST, insere, e corrige o heap subindo
TreapNo* Treap::inserirAux(TreapNo* no, int chave, int prioridade) {

    comparacoes++; // [MÉTRICAS]

    // 1. achou o lugar vazio -> cria o nó aqui
    if (no == nullptr) {
        return new TreapNo(chave, prioridade);
    }

    // 2. se a chave for menor, desce pela esquerda
    if (chave < no->chave) {
        // desce pela esquerda, e recebe de volta a subárvore esquerda já corrigida
        no->esq = inserirAux(no->esq, chave, prioridade);

        // se o filho esquerdo tem prioridade maior, ou seja, viola o heap -> rotaciona
        if (no->esq->prioridade > no->prioridade) {
            no = rotacionarDireita(no);
        }
    }
    // 3. se for maior, desce pela direita
    else if (chave > no->chave) {
        no->dir = inserirAux(no->dir, chave, prioridade);

        // se o filho direito tem prioridade maior, ou seja, viola o heap -> rotaciona
        if (no->dir->prioridade > no->prioridade) {
            no = rotacionarEsquerda(no);
        }
    }
    // se chave == no->chave, a chave já existe -> não faz nada (sem duplicatas)

    return no;
}


// insere a chave na árvore, sorteando uma prioridade aleatória internamente
void Treap::inserir(int chave) {

    comparacoes = 0; // [MÉTRICAS]
    int prioridade = rand();
    raiz = inserirAux(raiz, chave, prioridade);
}


// função auxiliar recursiva: desce como uma BST comum, ignorando completamente a prioridade
bool Treap::buscarAux(TreapNo* no, int chave) {

    comparacoes++; // [MÉTRICAS]

    // 1. chegou a um ponto vazio -> não encontrou
    if (no == nullptr) {
        return false;
    }

    // 2. se a chave for igual, encontrou
    if (chave == no->chave) {
        return true; // encontrou
    }

    // 3. se a chave for menor, desce pela esquerda
    if (chave < no->chave) {
        return buscarAux(no->esq, chave);
    }

    // 4. se for maior, desce pela direita (continua chamando a recursão)
    return buscarAux(no->dir, chave);
}


// busca a chave na árvore
bool Treap::buscar(int chave) {

    comparacoes = 0; // [MÉTRICAS]

    return buscarAux(raiz, chave);
}


// função auxiliar recursiva: localiza a chave e a remove, "empurrando-a" para baixo antes
TreapNo* Treap::removerAux(TreapNo* no, int chave) {

    comparacoes++; // [MÉTRICAS]

    // não encontrou a chave -> não há nada a remover
    if (no == nullptr) {
        return nullptr;
    }

    // se a chave for menor, desce pela esquerda
    if (chave < no->chave) {
        no->esq = removerAux(no->esq, chave);
    }
    // se for maior, desce pela direita
    else if (chave > no->chave) {
        no->dir = removerAux(no->dir, chave);
    }
    else {
        // encontrou o nó a ser removido

        if (no->esq == nullptr) {
            // sem filho esquerdo -> o filho direito assume o lugar (pode ser nullptr também)
            TreapNo* direito = no->dir;
            delete no;
            return direito;
        }

        if (no->dir == nullptr) {
            // sem filho direito -> o filho esquerdo assume o lugar
            TreapNo* esquerdo = no->esq;
            delete no;
            return esquerdo;
        }

        // tem os dois filhos -> rotaciona na direção do filho de MAIOR prioridade,
        // empurrando "no" para baixo, e continua tentando remover a partir daí
        if (no->esq->prioridade > no->dir->prioridade) {
            no = rotacionarDireita(no);
            no->dir = removerAux(no->dir, chave);
        }
        else {
            no = rotacionarEsquerda(no);
            no->esq = removerAux(no->esq, chave);
        }
    }

    return no;
}


// remove a chave da árvore, caso exista
bool Treap::remover(int chave) {

    comparacoes = 0; // [MÉTRICAS]

    if (!buscar(chave)) {
        return false; // não encontrou a chave -> não removeu
    }

    // chama a função auxiliar recursiva para remover a chave, e atualiza a raiz da árvore
    raiz = removerAux(raiz, chave);
    return true;
}


// [MÉTRICAS]
long long Treap::getComparacoes() const {
    return comparacoes;
}


int Treap::alturaAux(TreapNo* no) {
    if (no == nullptr) {
        return -1;
    }
    int alturaEsq = alturaAux(no->esq);
    int alturaDir = alturaAux(no->dir);
    return 1 + (alturaEsq > alturaDir ? alturaEsq : alturaDir);
}


int Treap::obterAltura() {
    return alturaAux(raiz);
}