#ifndef METRICAS_HPP
#define METRICAS_HPP

#include <string>
#include <vector>


using namespace std;

namespace Metricas {

    // um registro de resultado de uma única operação medida
    struct Registro {
        string estrutura;    // nome da estrutura (ex: "Trie", "Patricia")
        int tamanhoEntrada;       // quantos elementos a estrutura tinha no momento da medição
        string operacao;     // "inserir", "buscar" ou "remover"
        double tempoMs;           // tempo gasto, em milissegundos
        long long comparacoes;    // número de comparações/nós visitados
        int alturaArvore;         // altura da árvore no momento da medição
    };

    // acumula os registros ao longo dos experimentos
    class Coletor {

        private:
            vector<Registro> registros;

        public:
            void adicionar(const Registro& r);

            // exporta todos os registros acumulados para um arquivo CSV
            void exportarCSV(const 
    string& caminhoArquivo);
    };

}

#endif