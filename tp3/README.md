# Documentação Técnica - TP3: Estruturas de Dados

## 1. Modelagem e Entidades (C++)

O sistema modela uma plataforma de mercado com suporte a consultas multicritério, associando entidades a estruturas de indexação rápida (Tabelas Hash com encadeamento).

### 1.1 Principais Entidades
* **Consulta:** *Struct* simples que representa um filtro composto por atributo e valor.
* **ListaArray:** Vetor dinâmico genérico com suporte a ordenação (**Quicksort**) e intersecção ordenada (algoritmo de dois ponteiros).
* **Nó:** Célula interna da `ListaEncadeada` que armazena a chave genérica, o valor inteiro (`id`) e ponteiro para o próximo nó.
* **ListaEncadeada:** Estrutura utilizada para o tratamento de colisões por encadeamento externo na `TabelaHash`.
* **TabelaHash:** Tabela genérica parametrizada por tipo `T` (`int` ou `std::string` com algoritmo **DJB2**) que mapeia atributos buscáveis para listas de IDs.
* **Item:** Encapsula par `(id_produto, quantidade)`.
* **Usuário:** Dados do usuário e histórico de itens adquiridos.
* **Produto:** Atributos do produto, histórico de compradores/quantidades e registros de transações (compras/reposições).
* **Compra / Reposição:** Registros transacionais com timestamps e listas de itens movimentados.
* **Mercado:** Fachada central contendo:
  * 4 listas principais indexadas por ID direto (`Usuário`, `Produto`, `Compra`, `Reposição`).
  * Agrupamentos de `TabelaHash` para atributos buscáveis:
    * *Usuário:* nome, idade, cidade, estado, nacionalidade.
    * *Produto:* nome, categoria, marca, condição.
    * *Compra:* timestamp, usuário.
    * *Reposição:* timestamp.

---

## 2. Análise de Complexidade Assintótica

Considere:
* $N$: Número de elementos na estrutura
* $m$: Tamanho do bucket/capacidade da tabela hash
* $\alpha = \frac{n}{m}$: Fator de carga da tabela hash
* $k$: Média de elementos por bucket ($k \approx 1$ em distribuição uniforme)
* $p$: Quantidade de filtros por consulta

### 2.1 Estruturas de Lista
| Operação | ListaArray (Vetor Dinâmico) | ListaEncadeada (Buckets) |
| :--- | :--- | :--- |
| **Acesso por Índice** | $O(1)$ | $O(N)$ |
| **Inserção no Final** | $O(1)$ amortizado ($O(N)$ na realocação) | $O(1)$ (com ponteiro para cauda) |
| **Ordenação** | $O(N \log N)$ via Quicksort | Não aplicável |
| **Intersecção** | $O(N)$ (algoritmo de dois ponteiros) | Não aplicável |
| **Espaço de Memória** | $O(m_{alocado}) \approx O(N)$ | $O(N)$ |

---

### 2.2 Tabela Hash (Encadeamento Separado)
* **Inserção:** $O(1)$ ou $O(1 + \alpha)$
* **Pesquisa:** $O(1 + \alpha)$
* **Espaço:** $O(m + n)$ (vetor de ponteiros para buckets + nós encadeados)

---

### 2.3 Operações de Negócio

| Operação | Custo Assintótico | Descrição |
| :--- | :--- | :--- |
| **Cadastro (Usuário / Produto)** | $O(1)$ | Inserção no vetor principal e nas tabelas hash dos atributos. |
| **Cadastro (Compra / Reposição)** | $O(n_{itens})$ | Validação de estoque/produtos em $O(1)$ e inserção em listas de vínculos. |
| **Busca (Usuário / Produto)** | $O(p \cdot k + k \log k + u \cdot r)$ | Pesquisa em $p$ hashes, ordenação/intersecção dos IDs e recuperação dos $r$ registros. |
| **Busca (Compra / Reposição)** | $O(p \cdot k + k \log k + c \cdot i)$ | Pesquisa em $p$ hashes, ordenação/intersecção e recuperação dos $i$ itens para $c$ transações. |

---

## 3. Análise de Localidade de Memória e Eficiência de Cache

* **ListaArray (Vetor Contíguo):**
  * **Localidade Espacial Alta:** Alocação em bloco contíguo de memória permite carregar múltiplos elementos adjacentes em uma única *cache line* (normalmente 64 bytes).
  * **Otimização no Hardware:** Maximiza o *cache hit* durante a varredura linear da intersecção de dois ponteiros e nos passos sequenciais do Quicksort.
* **ListaEncadeada e TabelaHash (Ponteiros Esparsos):**
  * **Localidade Espacial e Temporal Reduzida:** Cada `Nó` é alocado individualmente na *heap*, resultando em fragmentação e acessos a endereços distantes de memória (*pointer chasing*).
  * **Custo Real de Cache:** Mesmo com complexidade assintótica teórica de $O(1 + \alpha)$, o encadeamento pode causar múltiplos *cache misses* por bucket longo. O impacto é mitigado mantendo $\alpha \approx 1$, limitando as cadeias encadeadas a poucos saltos de ponteiro.
