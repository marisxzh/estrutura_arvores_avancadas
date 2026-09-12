#include "Patricia.hpp"

using namespace std;


// inicializa o nó com o trecho de string recebido
// por padrão, todo nó nasce sem ser fim de palavra
PatriciaNo::PatriciaNo(const string& lbl) {
    label = lbl;
    finalPalavra = false;
}


// inicia a árvore com um nó raiz, cujo label é vazio
// a raiz nunca representa uma palavra em si, só o ponto de partida
Patricia::Patricia() {
    raiz = new PatriciaNo("");
}


// inicia a limpeza a partir do nó raiz
Patricia::~Patricia() {
    destruirAux(raiz);
}


// mesma lógica que a trie
// função auxiliar para destruir a árvore recursivamente
void Patricia::destruirAux(PatriciaNo* atual) {

    if (atual == nullptr) {
        return;
    }

    // percorre todos os filhos do nó atual
    for (auto& par : atual->filhos) {

        // chama a função recursivamente para cada filho
        destruirAux(par.second);

    }

    // deleta o nó atual após limpar seus filhos
    delete atual;

}


// insere a palavra na árvore, separando por trechos (quando necessário)
void Patricia::inserir(const string& palavra) {
    
    comparacoes = 0; // [MÉTRICAS]

    // ponteiro para "andar" pela árvore
    PatriciaNo* atual = raiz;
    // marca quanto da palavra já foi processada
    size_t posicao = 0;

    // laço roda enquanto tiver coisa para inserir
    while (posicao < palavra.size()) {

        comparacoes++; // [MÉTRICAS]

        // pega o caracter da posicaoição atual e usa para a busca do filho
        char proximo = palavra[posicao];

        // 1. se não existe esse caminho ainda (palavra) cria um novo nó com o restante da palavra 
        if (atual->filhos.find(proximo) == atual->filhos.end()) {

            // substr -> pega da [posicao] até o final
            PatriciaNo* novo = new PatriciaNo(palavra.substr(posicao));
            // como esse nó contem o final da palavra ele marca como finalPalavra = true
            novo->finalPalavra = true;
            // registra esse nó novo como filho do nó atual, na posição do caractere [proximo] do mapa.
            atual->filhos[proximo] = novo;
            return;
        }

        // se chegou até aqui existe uma palavra anterior (um filho para ele)
        // pegar o ponteiro para oo filho
        PatriciaNo* filho = atual->filhos[proximo];
        
        // copia label desse filho para um lugar temporário
        string label = filho->label; 

        // conta quantos caracteres do label batem com o restante da palavra (prefixo comum)
        size_t i = 0;
        // se ainda há caracteres para comparar (tanto do label quanto da palavra) e se eles são iguais
        while (i < label.size() && posicao + i < palavra.size() && label[i] == palavra[posicao + i]) {
            comparacoes++; // [MÉTRICAS]
            i++;
        }

        // 2. se o label bateu com toda a palavra que já havia (são iguais)
        if (i == label.size()) {
            
            // avança todo o tamanho do label, já que ele está igual ao prefixo
            posicao += label.size();

            // verifica se a palavra acabou aqui
            if (posicao == palavra.size()) {
                // se tiver acabado, agora, filho também é uma palavra valida, marca e termina a função
                filho->finalPalavra = true;
                return;
            }

            // se a palavra (label) não acabou, atribui o valor de filho para atual e continua
            atual = filho;
            continue;
        }

        // 3. se divergiu no meio do label, ou seja, precisa quebrar a palavra

        // cria um nó novo no "meio" da palavra 
        PatriciaNo* meio = new PatriciaNo(label.substr(0, i));

        // o nó antigo fica só com o restante do label, após o pont o de quebra
        filho->label = label.substr(i);

        // o nó do meio "adota" o antigo filho
        meio->filhos[filho->label[0]] = filho;

        // liga o nó do meio no lugar onde o filho antigo estava
        atual->filhos[proximo] = meio;

        posicao += i;

        if (posicao == palavra.size()) {
            // a palavra termina exatamente no ponto de quebra
            meio->finalPalavra = true;
        } else {
            // cria um novo ramo para o restante da palavra
            PatriciaNo* novo = new PatriciaNo(palavra.substr(posicao));
            novo->finalPalavra = true;
            meio->filhos[palavra[posicao]] = novo;
        }

        return;
    }
}


// busca a palavra na árvore, comprimindo o caminho por trechos (labels)
bool Patricia::buscar(const string& palavra) {

    comparacoes = 0; // [MÉTRICAS]

    PatriciaNo* atual = raiz;
    size_t pos = 0; // quanto da "palavra" já foi consumido

    while (pos < palavra.size()) {
        char proximo = palavra[pos];

        comparacoes++; // [MÉTRICAS]

        // procura o filho que começa com essa letra
        if (atual->filhos.find(proximo) == atual->filhos.end()) {
            return false; // não existe esse caminho -> palavra não está na árvore
        }

        PatriciaNo* filho = atual->filhos[proximo];
        const string& label = filho->label; // aqui pode ser referência, pois não vamos alterar nada

        // conta quantos caracteres do label batem com o restante da palavra
        size_t i = 0;
        while (i < label.size() && pos + i < palavra.size() && label[i] == palavra[pos + i]) {
            comparacoes++; // [MÉTRICAS]
            i++;
        }

        if (i < label.size()) {
            // divergiu no meio do label -> palavra não existe
            return false;
        }

        // label bateu inteiro -> consome e desce
        pos += label.size();
        atual = filho;
    }

    // chegamos ao fim da palavra: só é válido se o nó marcar fim de palavra
    return atual->finalPalavra;
}


// função auxiliar para remover uma palavra da árvore
bool Patricia::removerAux(PatriciaNo* atual, const string& palavra, size_t pos) {

    comparacoes++; // [MÉTRICAS]

    // chegamos ao fim da palavra buscada
    if (pos == palavra.size()) {

        if (!atual->finalPalavra) {
            return false; // a palavra não existe na árvore
        }

        atual->finalPalavra = false;

        // se o nó não tem filhos, ele pode ser removido pelo pai
        return atual->filhos.empty();
    }

    char proximo = palavra[pos];

    auto it = atual->filhos.find(proximo);
    if (it == atual->filhos.end()) {
        return false; // não existe esse caminho -> palavra não existe
    }

    PatriciaNo* filho = it->second;
    string& label = filho->label;

    // conta quantos caracteres do label batem com o restante da palavra
    size_t i = 0;
    while (i < label.size() && pos + i < palavra.size() && label[i] == palavra[pos + i]) {
        comparacoes++; // [MÉTRICAS]
        i++;
    }

    if (i < label.size()) {
        return false; // divergiu no meio -> palavra não existe
    }

    // chama recursivamente, avançando pelo tamanho do label inteiro
    bool deveRemoverFilho = removerAux(filho, palavra, pos + label.size());

    if (deveRemoverFilho) {
        delete filho;
        atual->filhos.erase(proximo);
        return !atual->finalPalavra && atual->filhos.empty();
    }

    // compactação: se o filho não é fim de palavra e sobrou só 1 neto, funde os dois nós
    if (!filho->finalPalavra && filho->filhos.size() == 1) {
        auto itNeto = filho->filhos.begin();
        PatriciaNo* neto = itNeto->second;

        filho->label += neto->label;          // concatena os labels
        filho->finalPalavra = neto->finalPalavra;
        filho->filhos.erase(itNeto);

        // adota os filhos do neto (se houver)
        for (auto& par : neto->filhos) {
            filho->filhos[par.first] = par.second;
        }

        delete neto;
    }

    return false;
}


bool Patricia::remover(const string& palavra) {
    comparacoes = 0; // [MÉTRICAS]

    return removerAux(raiz, palavra, 0);
}


// [MÉTRICAS]
long long Patricia::getComparacoes() const {
    return comparacoes;
}


int Patricia::alturaAux(PatriciaNo* atual) {
    if (atual == nullptr || atual->filhos.empty()) {
        return 0;
    }

    int maior = 0;
    for (auto& par : atual->filhos) {
        int alturaFilho = alturaAux(par.second);
        if (alturaFilho > maior) {
            maior = alturaFilho;
        }
    }
    return maior + 1;
}


int Patricia::obterAltura() {
    return alturaAux(raiz);
}