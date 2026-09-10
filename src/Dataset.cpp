#include "Dataset.hpp"
#include <fstream>
#include <sstream>
#include <random>
#include <unordered_set>

using namespace std;

namespace Dataset {

    // carrega strings a partir do arquivo CSV de headlines (formato: publish_date,headline_text)
    vector<string> carregarStrings(const string& caminhoArquivo, int quantidade) {

        vector<string> resultado;
        ifstream arquivo(caminhoArquivo);

        if (!arquivo.is_open()) {
            // arquivo não encontrado -> retorna vazio, quem chamar deve checar isso
            return resultado;
        }

        string linha;

        // pula a primeira linha (cabeçalho: publish_date,headline_text)
        getline(arquivo, linha);

        while (getline(arquivo, linha) && (int)resultado.size() < quantidade) {

            // encontra a posição da primeira vírgula, que separa data de headline
            size_t posVirgula = linha.find(',');

            if (posVirgula == string::npos) {
                continue; // linha malformada, sem vírgula -> ignora
            }

            // pega tudo depois da vírgula (o texto da headline)
            string headline = linha.substr(posVirgula + 1);

            if (!headline.empty()) {
                resultado.push_back(headline);
            }
        }

        arquivo.close();
        return resultado;
    }


    // gera 'quantidade' inteiros aleatórios, sem repetição, usando a seed informada
    vector<int> gerarInteiros(int quantidade, unsigned int seed) {

        vector<int> resultado;
        unordered_set<int> jaUsados;

        mt19937 gerador(seed);
        uniform_int_distribution<int> distribuicao(1, quantidade * 10);

        while ((int)resultado.size() < quantidade) {
            int valor = distribuicao(gerador);

            if (jaUsados.find(valor) == jaUsados.end()) {
                jaUsados.insert(valor);
                resultado.push_back(valor);
            }
        }

        return resultado;
    }


    // gera 'quantidade' pontos 2D aleatórios, usando a seed informada
    vector<Ponto> gerarPontos(int quantidade, unsigned int seed) {

        vector<Ponto> resultado;

        mt19937 gerador(seed);
        uniform_int_distribution<int> distribuicao(1, quantidade * 10);

        for (int i = 0; i < quantidade; i++) {
            Ponto p;
            p.x = distribuicao(gerador);
            p.y = distribuicao(gerador);
            resultado.push_back(p);
        }

        return resultado;
    }

}