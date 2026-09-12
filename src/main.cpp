#include <iostream>
#include <vector>
#include "Dataset.hpp"
#include "Metricas.hpp"
#include "Experimentos.hpp"

using namespace std;


const vector<int> TAMANHOS = {1000, 10000, 100000, 1000000};
const vector<int> TAMANHOS_TRIE = {1000, 10000, 100000};
const unsigned int SEED = 42;
const string CAMINHO_HEADLINES = "input.csv"; // ajuste para o caminho real do seu arquivo


int main() {
    Metricas::Coletor coletor;

    cout << "Iniciando experimentos..." << endl;

    for (int tamanho : TAMANHOS_TRIE) {


        vector<string> dadosString = Dataset::carregarStrings(CAMINHO_HEADLINES, tamanho);
        
        if (!dadosString.empty()) {
            cout << "  Trie..." << endl;
            Experimentos::testarTrie(dadosString, coletor);
        
        } else {
            cout << "  Aviso: arquivo de headlines nao encontrado ou vazio, pulando grupo string." << endl;
        }
        
    }


    for (int tamanho : TAMANHOS) {
        cout << "Tamanho: " << tamanho << endl;

        vector<string> dadosString = Dataset::carregarStrings(CAMINHO_HEADLINES, tamanho);
        if (!dadosString.empty()) {
            cout << "  Patricia..." << endl;
            Experimentos::testarPatricia(dadosString, coletor);
        } else {
            cout << "  Aviso: arquivo de headlines nao encontrado ou vazio, pulando grupo string." << endl;
        }

        vector<int> dadosInt = Dataset::gerarInteiros(tamanho, SEED);
        cout << "  Splay..." << endl;
        Experimentos::testarSplay(dadosInt, coletor);
        cout << "  Treap..." << endl;
        Experimentos::testarTreap(dadosInt, coletor);

        vector<Dataset::Ponto> dadosPontos = Dataset::gerarPontos(tamanho, SEED);
        cout << "  KDTree..." << endl;
        Experimentos::testarKDTree(dadosPontos, coletor);
    }

    coletor.exportarCSV("resultados.csv");
    cout << "Concluido. Resultados em resultados.csv" << endl;

    return 0;
}