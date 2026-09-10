#include "Trie.hpp"

using namespace std;


// inicializa a letra como não sendo o fim de uma palavra por natureza
TrieNo::TrieNo() {
    fimpalavra = false;
}


// inicia a árvore com um nó raiz
Trie::Trie() {
    raiz = new TrieNo();
}


// insere a palavra letra por letra
void Trie::inserir(const string& palavra){

    // cria um ponteiro auxiliar, ele aponta pra o mesmo lugar que a raiz está apontando
    TrieNo* atual = raiz;


    // laço para passar linha por linha da palavra
    for (char letra : palavra) {


        // procura a letra no mapa de filhos do nó atual, se não encontrar, cria um novo nó
        if (atual->filho.find(letra) == atual->filho.end()) {
            atual->filho[letra] = new TrieNo();
        }

        // move o ponteiro atual para o próximo nó
        atual = atual->filho[letra];
    }


    // ao chegar no final da palavra, marca o nó atual como o fim de uma palavra
    atual->fimpalavra = true;

}


// busca a palavra letra por letra
bool Trie::buscar(const string& palavra) {

    // cria um ponteiro auxiliar, ele aponta pra o mesmo lugar que a raiz está apontando
    TrieNo* atual = raiz;

    // laço para buscar letra por letra da palavra
    for (char letra : palavra) {

        // procura a letra no mapa de filhos do nó atual, se não encontrar, retorna false
        if (atual->filho.find(letra) == atual->filho.end()) {
            return false;
        }

        // se achar, continua a busca -> move o ponteiro atual para o próximo nó
        atual = atual->filho[letra];
    }

    // retorna true se for o fim de uma palavra, false caso contrário
    return atual->fimpalavra; 

}


bool Trie::comecaCom(const string& prefixo) {

    // cria um ponteiro auxiliar, ele aponta pra o mesmo lugar que a raiz está apontando
    TrieNo* atual = raiz;

    // laço para buscar letra por letra do prefixo
    for (char letra : prefixo) {

        // procura a letra no mapa de filhos do nó atual, se não encontrar, retorna false
        if (atual->filho.find(letra) == atual->filho.end()) {
            return false;
        }

        // se achar, continua a busca -> move o ponteiro atual para o próximo nó
        atual = atual->filho[letra];
    }

    // retorna true se achar o prefixo na árvore
    return true; 

}


// função auxiliar para remover uma palavra da árvore
bool Trie::removerAux(TrieNo* atual, const string& palavra, int index) {

    // se o índice for igual ao tamanho da palavra, significa que chegamos ao final da palavra
    if (index == palavra.size()) {

        // se o nó atual não é o fim de uma palavra, a palavra não existe na árvore. Logo, não há nada a remover
        if (!atual->fimpalavra) {
            return false;
        }

        // marca o nó atual como não sendo mais o fim de uma palavra
        atual->fimpalavra = false;

        // se o nó atual não tem filhos, ele pode ser removido
        return atual->filho.empty();

    }

    // pega a letra atual da palavra
    char letra = palavra[index];

    // procura a letra no mapa de filhos do nó atual, se não encontrar, a palavra não existe na árvore
    if (atual->filho.find(letra) == atual->filho.end()) {
        return false;
    }

    // chama a função recursivamente para o próximo nó e próximo índice
    bool deveRemoverFilho = removerAux(atual->filho[letra], palavra, index + 1);

    // se o filho deve ser removido, remove-o do mapa de filhos do nó atual
    if (deveRemoverFilho) {
        delete atual->filho[letra];
        atual->filho.erase(letra);

        // retorna true se o nó atual não é mais o fim de uma palavra e não tem filhos
        return !atual->fimpalavra && atual->filho.empty();
    }

    return false;

}


// inicia a limpeza a partir do nó raiz
Trie::~Trie() {
    destruirAux(raiz);
}


// função auxiliar para destruir a árvore recursivamente
void Trie::destruirAux(TrieNo* atual) {

    if (atual == nullptr) {
        return;
    }

    // percorre todos os filhos do nó atual
    for (auto& par : atual->filho) {

        // chama a função recursivamente para cada filho
        destruirAux(par.second); 
    
    }

    // deleta o nó atual após limpar seus filhos
    delete atual; 

}



bool Trie::remover(const string& palavra) {

    return removerAux(raiz, palavra, 0);
}

