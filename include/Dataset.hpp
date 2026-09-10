#ifndef DATASET_HPP
#define DATASET_HPP

#include <string>
#include <vector>

using namespace std;

// funções para gerar/carregar os datasets compartilhados entre estruturas do mesmo grupo
namespace Dataset {

    // carrega strings a partir do arquivo CSV de headlines (formato: publish_date,headline_text)
    // retorna até 'quantidade' headlines (ou todas, se o arquivo tiver menos que isso)
    vector<string> carregarStrings(const string& caminhoArquivo, int quantidade);

    // gera 'quantidade' inteiros aleatórios, sem repetição, usando a seed informada
    vector<int> gerarInteiros(int quantidade, unsigned int seed);

    // par simples para representar um ponto 2D
    struct Ponto {
        int x;
        int y;
    };

    // gera 'quantidade' pontos 2D aleatórios, usando a seed informada
    vector<Ponto> gerarPontos(int quantidade, unsigned int seed);

}

#endif