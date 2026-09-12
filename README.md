# Modelagem, Implementação e Análise Comparativa de Estruturas em Árvore Especializadas

Professor: Michel Pires da Silva

Aluna: Mariana Kaori Yano

AEDS II - CEFET-MG

## Introdução

Estruturas de dados em árvore são amplamente utilizadas para organizar informações de forma que seja possível buscar, inserir e remover elementos com eficiência. Este trabalho tem como objetivo o estudo, a implementação e a análise comparativa de cinco estruturas de árvore especializadas: **Trie**, **Árvore Patricia**, **Árvore Splay**, **Treap** e **KD-Tree**.

Cada uma dessas estruturas foi projetada para lidar com um tipo específico de problema em que uma BST ou AVL convencional não seria a escolha mais adequada — seja por trabalhar com chaves textuais com prefixos compartilhados, por apresentar padrões de acesso desiguais, por exigir balanceamento probabilístico mais simples de implementar, ou por lidar com dados multidimensionais sem uma ordenação natural única.

Além da implementação das cinco estruturas, este trabalho inclui uma metodologia experimental para comparação de desempenho, utilizando conjuntos de dados de diferentes tamanhos e medindo tempo de execução, número de comparações realizadas e altura resultante de cada árvore.

## Metodologia

As cinco estruturas foram implementadas em C++, cada uma com suas operações fundamentais (inserção, busca e remoção) e, quando aplicável, operações específicas (como busca por prefixo na Trie, ou vizinho mais próximo na KD-Tree). Para viabilizar uma comparação justa, estruturas que aceitam o mesmo tipo de dado compartilham a mesma fonte de entrada: Trie e Patricia são testadas com o mesmo conjunto de strings, enquanto Splay e Treap são testadas com o mesmo conjunto de inteiros.

### Estrutura do projeto

O projeto foi organizado em arquivos separados por estrutura e por responsabilidade, facilitando a modularização e manutenção do código:

```
.
├── include/
│ ├── Trie.hpp                      # Struct do nó e classe da Trie
│ ├── Patricia.hpp                  # Struct do nó e classe da Árvore Patricia
│ ├── Splay.hpp                     # Struct do nó e classe da Árvore Splay
│ ├── Treap.hpp                     # Struct do nó e classe da Treap
│ ├── KDTree.hpp                    # Struct do nó e classe da KD-Tree
│ ├── Dataset.hpp                   # Geração/carregamento dos conjuntos de dados de teste
│ ├── Metricas.hpp                  # Coleta e exportação dos resultados experimentais
│ └── Experimentos.hpp              # Funções de teste de cada estrutura
├── src/
│ ├── Trie.cpp, Patricia.cpp, Splay.cpp, Treap.cpp, KDTree.cpp
│ ├── Dataset.cpp, Metricas.cpp, Experimentos.cpp
│ ├── main.cpp                      # Orquestra os experimentos e gera o CSV de resultados
│ └── testes/                       # Testes unitários individuais de cada estrutura
├── data/
│ └── headlines.csv                 # Fonte de dados textuais (A Million News Headlines)
├── resultados/
│ └── resultados.csv                # Saída gerada pela execução dos experimentos
└── Makefile # Compilação
```

### Bibliotecas incluídas no projeto

Para o desenvolvimento do projeto, foram utilizadas as bibliotecas:

| Biblioteca | Função |
|---|---|
| `<iostream>`, `<fstream>`, `<sstream>` | Entrada e saída de dados no terminal e em arquivos |
| `<string>` | Manipulação de strings (Trie e Patricia) |
| `<unordered_map>` | Armazenamento dos filhos de cada nó (Trie e Patricia) |
| `<vector>` | Armazenamento dinâmico de dados e resultados |
| `<unordered_set>` | Garantia de unicidade na geração de inteiros aleatórios |
| `<random>` | Geração de números aleatórios de alta qualidade (Mersenne Twister) |
| `<cstdlib>`, `<ctime>` | Geração de prioridades aleatórias (Treap) |
| `<cmath>` | Cálculo de distância euclidiana (KD-Tree) |
| `<chrono>` | Medição de tempo de execução das operações |

### Principais estruturas e suas operações

| Estrutura | Anatomia do nó | Operações implementadas |
|---|---|---|
| **Trie** | `unordered_map<char, TrieNo*>` + flag de fim de palavra | inserir, buscar, começaCom (prefixo), remover |
| **Patricia** | `label` (string) + `unordered_map<char, PatriciaNo*>` + flag de fim de palavra | inserir, buscar, remover |
| **Splay** | `chave` (int) + ponteiros `esq`/`dir`/`pai` | inserir, buscar, remover (com splaying via zig/zig-zig/zig-zag) |
| **Treap** | `chave` + `prioridade` (int) + ponteiros `esq`/`dir` | inserir, buscar, remover (rotações condicionadas à prioridade) |
| **KD-Tree** | `x`, `y` (int) + ponteiros `esq`/`dir` | inserir, buscar, remover, vizinho mais próximo, busca por região |

### Metodologia experimental

Os experimentos foram conduzidos com conjuntos de dados de tamanhos crescentes (1.000, 10.000, 100.000 e 1.000.000 de elementos), gerados de forma reprodutível (seed fixa para os dados numéricos e espaciais) ou carregados de uma fonte real de texto (dataset *A Million News Headlines*, ver Referências). Para cada estrutura, foram medidos: tempo de execução, número de comparações realizadas e altura da árvore resultante, exportados em formato CSV para posterior análise em tabelas e gráficos.

## Resultados
Ainda falta desenvolver


## Como Compilar e Executar

### Pré-requisitos

- g++ (C++17 ou superior)

### Compilação
```bash
make            # compila e gera o executável
```

### Execução
```bash
make run        # executa o programa utilizando o imput.dat 
```

### Limpar arquivos compilados
```bash
make clean      # remove os arquivos objetos e o executável
```

- Gera `resultados.csv` (resultados obtidos com os testes).
- Exibe qual árvore está sendo executada (no momento) no console.
