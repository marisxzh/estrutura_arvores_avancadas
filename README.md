# Modelagem, Implementação e Análise Comparativa de Estruturas em Árvore Especializadas

Professor: Michel Pires da Silva

Aluna: Mariana Kaori Yano

AEDS II - CEFET-MG

## Introdução

Estruturas de dados em árvore são amplamente utilizadas para organizar informações de forma que seja possível buscar, inserir e remover elementos com eficiência. Este trabalho tem como objetivo o estudo, a implementação e a análise comparativa de cinco estruturas de árvore especializadas: **Trie**, **Árvore Patricia**, **Árvore Splay**, **Treap** e **KD-Tree**.

Cada uma dessas estruturas foi projetada para lidar com um tipo específico de problema em que uma BST ou AVL convencional não seria a escolha mais adequada — seja por trabalhar com chaves textuais com prefixos compartilhados, por apresentar padrões de acesso desiguais, por exigir balanceamento probabilístico mais simples de implementar, ou por lidar com dados multidimensionais sem uma ordenação natural única.

Além da implementação das cinco estruturas, este trabalho inclui uma metodologia experimental para comparação de desempenho, utilizando conjuntos de dados de diferentes tamanhos e medindo tempo de execução, número de comparações realizadas e altura resultante de cada árvore.

## Metodologia

As cinco estruturas foram implementadas em C++, cada uma com suas operações fundamentais (inserção, busca e remoção) e, quando aplicável, operações específicas (como busca por prefixo na Trie, ou vizinho mais próximo e busca por região na KD-Tree). Para viabilizar uma comparação justa, estruturas que aceitam o mesmo tipo de dado compartilham a mesma fonte de entrada: Trie e Patricia são testadas com o mesmo conjunto de strings, enquanto Splay e Treap são testadas com o mesmo conjunto de inteiros.

### Estrutura do projeto

O projeto foi organizado em arquivos separados por estrutura e por responsabilidade, facilitando a modularização e manutenção do código:

```
.
├── include/
│ ├── Trie.hpp                                 # Struct do nó e classe da Trie
│ ├── Patricia.hpp                             # Struct do nó e classe da Árvore Patricia
│ ├── Splay.hpp                                # Struct do nó e classe da Árvore Splay
│ ├── Treap.hpp                                # Struct do nó e classe da Treap
│ ├── KDTree.hpp                               # Struct do nó e classe da KD-Tree
│ ├── Dataset.hpp                              # Geração/carregamento dos conjuntos de dados de teste
│ ├── Metricas.hpp                             # Coleta e exportação dos resultados experimentais
│ └── Experimentos.hpp                         # Funções de teste de cada estrutura
├── src/
│ ├── Trie.cpp, Patricia.cpp, Splay.cpp, Treap.cpp, KDTree.cpp
│ ├── Dataset.cpp, Metricas.cpp, Experimentos.cpp
│ ├── main.cpp                                 # Orquestra os experimentos e gera o CSV de resultados
│ └── testes/                                  # Testes unitários individuais de cada estrutura
├── build/                                     # Arquivos objeto gerados na compilação
├── input.csv                                  # Fonte de dados textuais (A Million News Headlines)
├── resultados.csv                             # Saída gerada pela execução dos experimentos
└── Makefile                                   # Compilação
```

### Bibliotecas incluídas no projeto

Para o desenvolvimento do projeto, foram utilizadas as bibliotecas:

| Biblioteca                             | Função                                                             |
| --------------------------------------- | -------------------------------------------------------------------|
| `<iostream>`, `<fstream>`, `<sstream>` | Entrada e saída de dados no terminal e em arquivos                 |
| `<string>`                             | Manipulação de strings (Trie e Patricia)                           |
| `<unordered_map>`                      | Armazenamento dos filhos de cada nó (Trie e Patricia)              |
| `<vector>`                             | Armazenamento dinâmico de dados e resultados                       |
| `<unordered_set>`                      | Garantia de unicidade na geração de inteiros aleatórios            |
| `<random>`                             | Geração de números aleatórios de alta qualidade (Mersenne Twister) |
| `<cstdlib>`, `<ctime>`                 | Geração de prioridades aleatórias (Treap)                          |
| `<cmath>`                              | Cálculo de distância euclidiana (KD-Tree)                          |
| `<chrono>`                             | Medição de tempo de execução das operações                         |

### Principais estruturas e suas operações

| Estrutura    | Anatomia do nó                                                                 | Operações implementadas                                          |
| ------------ | -------------------------------------------------------------------------------| -------------------------------------------------------------------|
| **Trie**     | `unordered_map<char, TrieNo*>` + flag de fim de palavra                        | inserir, buscar, começaCom (prefixo), remover                    |
| **Patricia** | `label` (string) + `unordered_map<char, PatriciaNo*>` + flag de fim de palavra | inserir, buscar, remover                                         |
| **Splay**    | `chave` (int) + ponteiros `esq`/`dir`/`pai`                                    | inserir, buscar, remover (com splaying via zig/zig-zig/zig-zag)  |
| **Treap**    | `chave` + `prioridade` (int) + ponteiros `esq`/`dir`                           | inserir, buscar, remover (rotações condicionadas à prioridade)   |
| **KD-Tree**  | `x`, `y` (int) + ponteiros `esq`/`dir`                                         | inserir, buscar, remover, vizinho mais próximo, busca por região |

### Metodologia experimental

Os experimentos foram conduzidos com conjuntos de dados de tamanhos crescentes (1.000, 10.000, 100.000 e 1.000.000 de elementos), gerados de forma reprodutível (semente fixa igual a 42 para os dados numéricos e espaciais) ou carregados de uma fonte real de texto (dataset *A Million News Headlines*, ver Referências). A prioridade sorteada internamente pela Treap, por sua vez, usa uma semente baseada no horário do sistema, garantindo diversidade entre execuções — coerente com a garantia probabilística da estrutura.

Para cada estrutura, foram medidas as operações de inserção, busca e remoção, registrando-se o tempo de execução em milissegundos, o número de comparações ou nós visitados e a altura da árvore. A inserção foi realizada sobre todos os elementos de cada conjunto; busca e remoção utilizaram uma amostra fixa de 1.000 elementos (ou todos, quando a entrada possuía menos que isso). A Trie foi executada apenas até 100.000 elementos devido ao estouro de memória observado no maior tamanho testado.

## Resultados

### Tempos de execução (ms)

| Estrutura | n | Inserir | Buscar | Remover |
|---|---|---|---|---|
| Trie | 1.000 | 28,16 | 6,91 | 17,89 |
| Trie | 10.000 | 287,18 | 5,17 | 11,37 |
| Trie | 100.000 | 3.166,03 | 12,35 | 18,10 |
| Patricia | 1.000 | 1,86 | 1,40 | 1,38 |
| Patricia | 10.000 | 36,77 | 2,15 | 3,80 |
| Patricia | 100.000 | 301,12 | 2,89 | 3,90 |
| Patricia | 1.000.000 | 5.111,63 | 3,79 | 3,77 |
| Splay | 1.000 | 0,74 | 0,87 | 0,81 |
| Splay | 10.000 | 7,87 | 0,95 | 1,51 |
| Splay | 100.000 | 113,03 | 1,25 | 1,14 |
| Splay | 1.000.000 | 2.276,37 | 2,39 | 3,38 |
| Treap | 1.000 | 0,41 | 0,34 | 0,59 |
| Treap | 10.000 | 4,02 | 0,27 | 0,56 |
| Treap | 100.000 | 98,00 | 0,83 | 1,92 |
| Treap | 1.000.000 | 1.905,87 | 1,92 | 2,27 |
| KD-Tree | 1.000 | 0,20 | 0,18 | 0,94 |
| KD-Tree | 10.000 | 4,33 | 0,18 | 0,94 |
| KD-Tree | 100.000 | 65,94 | 0,21 | 2,79 |
| KD-Tree | 1.000.000 | 1.204,20 | 0,17 | 9,98 |

Na inserção, a KD-Tree obteve o menor tempo entre as árvores numéricas no maior conjunto (1.204,20 ms), seguida pela Treap (1.905,87 ms) e pela Splay (2.276,37 ms). A Patricia inseriu 1.000.000 de strings em 5.111,63 ms, enquanto a Trie não concluiu o experimento equivalente por falta de memória, tendo atingido 3.166,03 ms em 100.000 strings.

Na busca, a KD-Tree apresentou os menores tempos (entre 0,17 ms e 0,21 ms), seguida por Treap e Splay. A Patricia variou de 1,40 ms a 3,79 ms, e a Trie atingiu 12,35 ms em 100.000 entradas — valores parcialmente explicados pelo tamanho fixo da amostra (1.000 elementos).

Na remoção, a KD-Tree apresentou o maior custo entre as árvores numéricas no maior conjunto (9,98 ms), compatível com a necessidade de localizar um mínimo por eixo e reorganizar a estrutura.

### Comparações e altura na inserção

| Estrutura | n | Comparações | Altura |
|---|---|---|---|
| Trie | 1.000 | 39.976 | 52 |
| Trie | 10.000 | 396.880 | 60 |
| Trie | 100.000 | 3.928.901 | 60 |
| Patricia | 1.000 | 7.083 | 10 |
| Patricia | 10.000 | 116.642 | 13 |
| Patricia | 100.000 | 1.632.937 | 20 |
| Patricia | 1.000.000 | 21.096.520 | 27 |
| Splay | 1.000 | 11.427 | 28 |
| Splay | 10.000 | 162.110 | 36 |
| Splay | 100.000 | 2.105.994 | 42 |
| Splay | 1.000.000 | 25.877.952 | 52 |
| Treap | 1.000 | 11.176 | 19 |
| Treap | 10.000 | 170.715 | 31 |
| Treap | 100.000 | 2.055.176 | 37 |
| Treap | 1.000.000 | 25.442.579 | 52 |
| KD-Tree | 1.000 | 11.569 | 20 |
| KD-Tree | 10.000 | 161.445 | 32 |
| KD-Tree | 100.000 | 2.077.978 | 42 |
| KD-Tree | 1.000.000 | 25.322.192 | 56 |

A Patricia apresentou consistentemente menos comparações e menor altura que a Trie nos tamanhos comuns (em 100.000 elementos: 1.632.937 comparações e altura 20, contra 3.928.901 comparações e altura 60 da Trie) — resultado direto da compressão de caminhos. Entre Splay, Treap e KD-Tree, as alturas permaneceram bem menores que n, compatíveis com o comportamento médio esperado para entradas aleatórias.

Os resultados confirmam a análise teórica: Trie e Patricia dependem principalmente do comprimento das strings, e a compressão de caminhos da Patricia reduz de forma significativa espaço e comparações. Os experimentos não incluíram entradas ordenadas ou adversariais, portanto o pior caso O(n) de Splay, Treap e KD-Tree não foi reproduzido. O consumo de memória não foi medido diretamente; o estouro observado na Trie em 1.000.000 de entradas é uma evidência prática, não uma medição em bytes.

## Aplicações, Análise Crítica e Discussão

Cada estrutura resolve problemas em domínios distintos — Trie e Patricia para strings, Splay e Treap para chaves ordenáveis, e KD-Tree para dados multidimensionais:

- **Trie**: ideal para dicionários, autocompletar e busca por prefixo, com tempo de busca dependente apenas do comprimento do prefixo. Seu alto consumo de memória é uma limitação severa, comprovada pelo estouro de memória em 1.000.000 de entradas.
- **Patricia**: indicada para tabelas de roteamento e indexação compacta, resolvendo o problema de memória da Trie ao custo de uma implementação mais complexa (divisão e fusão de labels).
- **Splay**: apropriada para caches e sistemas com alta localidade temporal, adaptando-se ao padrão de consultas sem manter fator de balanceamento explícito, mas com risco de operações isoladas custarem O(n).
- **Treap**: útil para conjuntos dinâmicos que exigem implementação simples e altura esperada logarítmica, abrindo mão de garantias determinísticas em favor de simplicidade.
- **KD-Tree**: essencial em geometria computacional e buscas espaciais, com inserção rápida mas maior custo de remoção, dependente da distribuição dos pontos.

Como principais dificuldades de implementação, destacam-se: o gerenciamento de nós dinâmicos na Trie, a compactação cuidadosa de arestas na Patricia, a manutenção rigorosa de ponteiros `pai` nos três casos de rotação da Splay, a preservação simultânea das regras de BST e heap na Treap, e a alternância geométrica de eixos na KD-Tree — especialmente crítica na remoção.

## Conclusão

Este trabalho apresentou um estudo comparativo entre cinco estruturas especializadas (Trie, Patricia, Splay, Treap e KD-Tree) e as estruturas genéricas BST e AVL, validando suas propriedades teóricas por meio de experimentos. Nas estruturas de strings, a Patricia superou a Trie de forma consistente graças à compressão de caminhos, evitando o estouro de memória que a Trie sofreu em grandes volumes de dados. Entre as árvores numéricas, a KD-Tree obteve os melhores tempos de inserção e busca, embora com maior custo de remoção, enquanto Splay e Treap mantiveram alturas médias logarítmicas.

Em relação à complexidade de implementação, Splay e Patricia revelaram-se as mais desafiadoras, contrastando com a simplicidade probabilística da Treap. Conclui-se que a adoção de cada estrutura é pautada por seu nicho de aplicação: Trie e Patricia para busca por prefixos, Splay para forte localidade de acesso, Treap para simplicidade sem balanceamento rígido, e KD-Tree para dados espaciais — evidenciando que abrir mão da generalidade da BST e da AVL é um sacrifício justificado pelos ganhos de desempenho quando a estrutura correta é alinhada ao problema computacional adequado.

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
