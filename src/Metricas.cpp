#include "Metricas.hpp"
#include <fstream>

using namespace std;


namespace Metricas {

    void Coletor::adicionar(const Registro& r) {
        registros.push_back(r);
    }


    void Coletor::exportarCSV(const string& caminhoArquivo) {

        ofstream arquivo(caminhoArquivo);

        // cabeçalho do CSV
        arquivo << "estrutura,tamanho_entrada,operacao,tempo_ms,comparacoes,altura_arvore\n";

        for (const Registro& r : registros) {
            arquivo << r.estrutura << ","
                    << r.tamanhoEntrada << ","
                    << r.operacao << ","
                    << r.tempoMs << ","
                    << r.comparacoes << ","
                    << r.alturaArvore << "\n";
        }

        arquivo.close();
    }

}