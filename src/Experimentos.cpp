#include "Experimentos.hpp"
#include <chrono>
#include "Trie.hpp"
#include "Patricia.hpp"
#include "Splay.hpp"
#include "Treap.hpp"
#include "KDTree.hpp"

using namespace std;
using namespace std::chrono;

namespace Experimentos {

    // quantos elementos usar nas amostras de busca/remoção
    const int TAMANHO_AMOSTRA = 1000;


    void testarTrie(const vector<string>& dados, Metricas::Coletor& coletor) {
        Trie estrutura;
        int n = dados.size();

        auto inicio = high_resolution_clock::now();
        long long comparacoesTotais = 0;
        for (const string& palavra : dados) {
            estrutura.inserir(palavra);
            comparacoesTotais += estrutura.getComparacoes();
        }
        auto fim = high_resolution_clock::now();
        double tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"Trie", n, "inserir", tempoMs, comparacoesTotais, estrutura.obterAltura()});

        int amostra = min(TAMANHO_AMOSTRA, n);
        inicio = high_resolution_clock::now();
        comparacoesTotais = 0;
        for (int i = 0; i < amostra; i++) {
            estrutura.buscar(dados[i]);
            comparacoesTotais += estrutura.getComparacoes();
        }
        fim = high_resolution_clock::now();
        tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"Trie", n, "buscar", tempoMs, comparacoesTotais, estrutura.obterAltura()});

        inicio = high_resolution_clock::now();
        comparacoesTotais = 0;
        for (int i = 0; i < amostra; i++) {
            estrutura.remover(dados[i]);
            comparacoesTotais += estrutura.getComparacoes();
        }
        fim = high_resolution_clock::now();
        tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"Trie", n, "remover", tempoMs, comparacoesTotais, estrutura.obterAltura()});
    }


    void testarPatricia(const vector<string>& dados, Metricas::Coletor& coletor) {
        Patricia estrutura;
        int n = dados.size();

        auto inicio = high_resolution_clock::now();
        long long comparacoesTotais = 0;
        for (const string& palavra : dados) {
            estrutura.inserir(palavra);
            comparacoesTotais += estrutura.getComparacoes();
        }
        auto fim = high_resolution_clock::now();
        double tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"Patricia", n, "inserir", tempoMs, comparacoesTotais, estrutura.obterAltura()});

        int amostra = min(TAMANHO_AMOSTRA, n);
        inicio = high_resolution_clock::now();
        comparacoesTotais = 0;
        for (int i = 0; i < amostra; i++) {
            estrutura.buscar(dados[i]);
            comparacoesTotais += estrutura.getComparacoes();
        }
        fim = high_resolution_clock::now();
        tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"Patricia", n, "buscar", tempoMs, comparacoesTotais, estrutura.obterAltura()});

        inicio = high_resolution_clock::now();
        comparacoesTotais = 0;
        for (int i = 0; i < amostra; i++) {
            estrutura.remover(dados[i]);
            comparacoesTotais += estrutura.getComparacoes();
        }
        fim = high_resolution_clock::now();
        tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"Patricia", n, "remover", tempoMs, comparacoesTotais, estrutura.obterAltura()});
    }


    void testarSplay(const vector<int>& dados, Metricas::Coletor& coletor) {
        Splay estrutura;
        int n = dados.size();

        auto inicio = high_resolution_clock::now();
        long long comparacoesTotais = 0;
        for (int valor : dados) {
            estrutura.inserir(valor);
            comparacoesTotais += estrutura.getComparacoes();
        }
        auto fim = high_resolution_clock::now();
        double tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"Splay", n, "inserir", tempoMs, comparacoesTotais, estrutura.obterAltura()});

        int amostra = min(TAMANHO_AMOSTRA, n);
        inicio = high_resolution_clock::now();
        comparacoesTotais = 0;
        for (int i = 0; i < amostra; i++) {
            estrutura.buscar(dados[i]);
            comparacoesTotais += estrutura.getComparacoes();
        }
        fim = high_resolution_clock::now();
        tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"Splay", n, "buscar", tempoMs, comparacoesTotais, estrutura.obterAltura()});

        inicio = high_resolution_clock::now();
        comparacoesTotais = 0;
        for (int i = 0; i < amostra; i++) {
            estrutura.remover(dados[i]);
            comparacoesTotais += estrutura.getComparacoes();
        }
        fim = high_resolution_clock::now();
        tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"Splay", n, "remover", tempoMs, comparacoesTotais, estrutura.obterAltura()});
    }


    void testarTreap(const vector<int>& dados, Metricas::Coletor& coletor) {
        Treap estrutura;
        int n = dados.size();

        auto inicio = high_resolution_clock::now();
        long long comparacoesTotais = 0;
        for (int valor : dados) {
            estrutura.inserir(valor);
            comparacoesTotais += estrutura.getComparacoes();
        }
        auto fim = high_resolution_clock::now();
        double tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"Treap", n, "inserir", tempoMs, comparacoesTotais, estrutura.obterAltura()});

        int amostra = min(TAMANHO_AMOSTRA, n);
        inicio = high_resolution_clock::now();
        comparacoesTotais = 0;
        for (int i = 0; i < amostra; i++) {
            estrutura.buscar(dados[i]);
            comparacoesTotais += estrutura.getComparacoes();
        }
        fim = high_resolution_clock::now();
        tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"Treap", n, "buscar", tempoMs, comparacoesTotais, estrutura.obterAltura()});

        inicio = high_resolution_clock::now();
        comparacoesTotais = 0;
        for (int i = 0; i < amostra; i++) {
            estrutura.remover(dados[i]);
            comparacoesTotais += estrutura.getComparacoes();
        }
        fim = high_resolution_clock::now();
        tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"Treap", n, "remover", tempoMs, comparacoesTotais, estrutura.obterAltura()});
    }


    void testarKDTree(const vector<Dataset::Ponto>& dados, Metricas::Coletor& coletor) {
        KDTree estrutura;
        int n = dados.size();

        auto inicio = high_resolution_clock::now();
        long long comparacoesTotais = 0;
        for (const Dataset::Ponto& p : dados) {
            estrutura.inserir(p.x, p.y);
            comparacoesTotais += estrutura.getComparacoes();
        }
        auto fim = high_resolution_clock::now();
        double tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"KDTree", n, "inserir", tempoMs, comparacoesTotais, estrutura.obterAltura()});

        int amostra = min(TAMANHO_AMOSTRA, n);
        inicio = high_resolution_clock::now();
        comparacoesTotais = 0;
        for (int i = 0; i < amostra; i++) {
            estrutura.buscar(dados[i].x, dados[i].y);
            comparacoesTotais += estrutura.getComparacoes();
        }
        fim = high_resolution_clock::now();
        tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"KDTree", n, "buscar", tempoMs, comparacoesTotais, estrutura.obterAltura()});

        inicio = high_resolution_clock::now();
        comparacoesTotais = 0;
        for (int i = 0; i < amostra; i++) {
            estrutura.remover(dados[i].x, dados[i].y);
            comparacoesTotais += estrutura.getComparacoes();
        }
        fim = high_resolution_clock::now();
        tempoMs = duration<double, milli>(fim - inicio).count();

        coletor.adicionar({"KDTree", n, "remover", tempoMs, comparacoesTotais, estrutura.obterAltura()});
    }

}