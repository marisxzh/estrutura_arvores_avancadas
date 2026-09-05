#include "Splay.hpp"

using namespace std;


// inicializa o nó com a chave recebida
// por padrão, o nó nasce sem pai e sem filhos
SplayNo::SplayNo(int valor) {
    chave = valor;
    esq = nullptr;
    dir = nullptr;
    pai = nullptr;
}


// inicia a árvore vazia, sem nenhum nó ainda
Splay::Splay() {
    // raiz é um ponteiro para o nó raiz da árvore, que começa como nullptr (árvore vazia)
    raiz = nullptr;
}


// inicia a limpeza a partir do nó raiz
Splay::~Splay() {
    destruirAux(raiz);
}


// função auxiliar para destruir a árvore recursivamente
void Splay::destruirAux(SplayNo* atual) {

    if (atual == nullptr) {
        return;
    }

    destruirAux(atual->esq);
    destruirAux(atual->dir);

    delete atual;
}



// rotação à direita
void Splay::rotacionarDireita(SplayNo* no) {

    // guarda o filho esquerdo de "no" antes de mexer nos ponteiros
    SplayNo* esquerdo = no->esq;

    // o filho direito do "esquerdo" vira o novo filho esquerdo de "no"
    no->esq = esquerdo->dir;
    if (esquerdo->dir != nullptr) {
        esquerdo->dir->pai = no;
    }

    // "esquerdo" assume o lugar de "no" em relação ao avô
    esquerdo->pai = no->pai;

    // se "no" era a raiz, "esquerdo" vira a nova raiz
    if (no->pai == nullptr) {
        raiz = esquerdo; 

    // se "no" era filho esquerdo do pai, "esquerdo" vira o novo filho esquerdo do pai
    } else if (no->pai->esq == no) {
        no->pai->esq = esquerdo;

    // se "no" era filho direito do pai, "esquerdo" vira o novo filho direito do pai
    } else {
        no->pai->dir = esquerdo;
    }

    // "no" vira filho direito de "esquerdo"
    esquerdo->dir = no;
    no->pai = esquerdo;
}


// rotação à esquerda
// o filho direito de 'no' sobe, 'no' desce e vira filho esquerdo dele
// mesmo processo da rotação à direita, mas invertido
void Splay::rotacionarEsquerda(SplayNo* no) {

    // guarda o filho direito de "no" antes de mexer nos ponteiros
    SplayNo* direito = no->dir;

    no->dir = direito->esq;
    if (direito->esq != nullptr) {
        direito->esq->pai = no;
    }

    direito->pai = no->pai;

    if (no->pai == nullptr) {
        raiz = direito;
    } else if (no->pai->esq == no) {
        no->pai->esq = direito;
    } else {
        no->pai->dir = direito;
    }

    direito->esq = no;
    no->pai = direito;
}


// move o nó até a raiz através de rotações sucessivas (zig / zig-zig / zig-zag)
void Splay::splay(SplayNo* no) {

    // enquanto o nó não for a raiz, continua subindo ele
    while (no->pai != nullptr) {

        // pega o pai e o avô do nó atual
        SplayNo* pai = no->pai;
        SplayNo* avo = pai->pai;

        // 1. zig -> pai é a raiz, uma rotação simples resolve
        if (avo == nullptr) {
            
            // se o nó é filho esquerdo do pai, faz rotação à direita
            if (pai->esq == no) {
                rotacionarDireita(pai);
            // se o nó é filho direito do pai, faz rotação à esquerda
            } else {
                rotacionarEsquerda(pai);
            }
        }
        
        // 2. zig-zig -> pai e nó estão do mesmo lado do avô, duas rotações na mesma direção
        else if (avo->esq == pai && pai->esq == no) {

            // direita-direita, rotaciona o avô, depois o pai
            rotacionarDireita(avo);
            rotacionarDireita(pai);

        }

        // 2. zig-zig -> pai e nó estão do mesmo lado do avô, duas rotações na mesma direção
        else if (avo->dir == pai && pai->dir == no) {
            
            // esquerda-esquerda, rotaciona o avô, depois o pai
            rotacionarEsquerda(avo);
            rotacionarEsquerda(pai);
        }

        //3. zig-zag -> pai e nó estão em lados opostos do avô, duas rotações em direções diferentes
        else if (avo->esq == pai && pai->dir == no) {
            //(esquerda-direita) rotaciona o pai, depois o avô
            rotacionarEsquerda(pai);
            rotacionarDireita(avo);
        }

        // 3. zig-zag -> pai e nó estão em lados opostos do avô, duas rotações em direções diferentes
        else {
            // (direita-esquerda) rotaciona o pai, depois o avô
            rotacionarDireita(pai);
            rotacionarEsquerda(avo);
        }
    }
}


// insere o valor na árvore, seguindo a lógica de BST, e depois faz o splay do nó inserido
void Splay::inserir(int valor) {

    // caso a árvore esteja vazia, o novo nó vira a raiz direto
    if (raiz == nullptr) {
        raiz = new SplayNo(valor);
        return;
    }

    // ponteiro para percorrer a árvore e encontrar o local de inserção
    SplayNo* atual = raiz;
    SplayNo* pai = nullptr;

    // desce a árvore, comparando a chave, até achar um lugar vazio
    while (atual != nullptr) {

        // guarda o pai antes de descer para o próximo nó
        pai = atual;

        // se o valor já existe, não insere duplicado, mas leva o nó existente à raiz
        if (valor == atual->chave) {
            
            splay(atual);
            return;
        }

        // se o valor for menor, desce para a esquerda
        else if (valor < atual->chave) {
            atual = atual->esq;
        }
        // se o valor for maior, desce para a direita
        else {
            atual = atual->dir;
        }
    }

    // cria o novo nó e liga ao pai encontrado
    SplayNo* novo = new SplayNo(valor);
    novo->pai = pai;

    // liga o novo nó como filho esquerdo ou direito do pai, dependendo da comparação
    if (valor < pai->chave) {
        pai->esq = novo;
    } else {
        pai->dir = novo;
    }

    // traz o nó recém-inserido até a raiz
    splay(novo);
}


// busca o valor na árvore; sempre faz o splay do último nó visitado, mesmo se não encontrar (propriedade da árvore splay)
bool Splay::buscar(int valor) {

    // ponteiro para percorrer a árvore, começando da raiz
    SplayNo* atual = raiz;
    // guarda o último nó visitado, mesmo em caso de falha
    SplayNo* ultimo = nullptr; 

    // desce a árvore, comparando a chave, até achar o valor ou chegar em nullptr
    while (atual != nullptr) {

        // guarda o último nó visitado
        ultimo = atual;

        // se encontrou o valor, faz o splay e retorna true
        if (valor == atual->chave) {
            splay(atual);
            return true;
        }

        // se o valor for menor, desce para a esquerda
        else if (valor < atual->chave) {
            atual = atual->esq;
        }

        // se o valor for maior, desce para a direita
        else {
            atual = atual->dir;
        }
    }

    // não encontrou -> faz o splay do último nó visitado (se a árvore não estava vazia)
    if (ultimo != nullptr) {
        splay(ultimo);
    }

    return false;
}


// remove o valor da árvore, usando splay para trazer o nó à raiz e depois juntar as subárvores
bool Splay::remover(int valor) {

    // primeiro, busca o valor; se não encontrar, retorna false
    if (!buscar(valor)) {
        return false; 
    }

    // se chegou aqui, 'buscar' encontrou o valor e o trouxe para a raiz

    // guarda a raiz antiga e suas subárvores
    SplayNo* antigaRaiz = raiz;
    SplayNo* esquerda = raiz->esq;
    SplayNo* direita = raiz->dir;

    // se houver subárvore esquerda, ela precisa ser trazida para a raiz e depois ligada à direita
    if (esquerda != nullptr) {
        // desliga a subárvore esquerda da raiz antiga
        esquerda->pai = nullptr; 

        // acha o maior valor da subárvore esquerda, e o traz para a raiz dela
        SplayNo* maiorEsquerda = esquerda;
        while (maiorEsquerda->dir != nullptr) {
            maiorEsquerda = maiorEsquerda->dir;
        }

        // faz o splay do maior nó da subárvore esquerda, que agora será a nova raiz
        raiz = esquerda; 
        splay(maiorEsquerda);

        // agora 'maiorEsquerda' é a raiz da subárvore esquerda, e não tem filho direito
        raiz->dir = direita;
        if (direita != nullptr) {
            direita->pai = raiz;
        }
    }
    else {
        // não havia subárvore esquerda -> a direita assume direto como nova raiz
        raiz = direita;
        if (raiz != nullptr) {
            raiz->pai = nullptr;
        }
    }

    delete antigaRaiz;
    return true;
}