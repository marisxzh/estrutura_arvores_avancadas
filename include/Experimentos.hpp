#ifndef EXPERIMENTOS_HPP
#define EXPERIMENTOS_HPP

#include <vector>
#include <string>
#include "Dataset.hpp"
#include "Metricas.hpp"

using namespace std;

namespace Experimentos {

    void testarTrie(const vector<string>& dados, Metricas::Coletor& coletor);
    void testarPatricia(const vector<string>& dados, Metricas::Coletor& coletor);

    void testarSplay(const vector<int>& dados, Metricas::Coletor& coletor);
    void testarTreap(const vector<int>& dados, Metricas::Coletor& coletor);

    void testarKDTree(const vector<Dataset::Ponto>& dados, Metricas::Coletor& coletor);

}

#endif