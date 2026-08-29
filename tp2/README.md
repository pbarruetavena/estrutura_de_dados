# Documentação Técnica - TP2: Estruturas de Dados

## 1. Modelagem e Entidades (C++)

O sistema modela redes de relacionamentos sociais e de interesse utilizando grafos genéricos desacoplados da semântica das entidades.

### 1.1 Principais Entidades
* **Tema:** Modela o conceito de tema e seus atributos no sistema.
* **Usuário:** Representa os usuários da rede.
* **Lista:** TAD genérico baseado em array com suporte a inserção, remoção e ordenação via **Quicksort**.
* **Nó:** Encapsula uma entidade (`Tema` ou `Usuário`), mapeando o seu **ID real** ao seu **ID sequencial interno** no grafo correspondente.
* **Grafo:** Estrutura puramente topológica/estrutural (semântica neutra). Suporta grafos direcionados e alternância dinâmica entre duas representações:
  * **Matriz de Adjacência** ($n \times n$).
  * **Lista de Adjacência** (vetor de listas).
  * A inserção de vértices incrementa o contador interno e retorna o novo ID sem depender de dados externos.
* **Dicionário (Tradutor):** Realiza a tradução bidirecional entre IDs reais e IDs internos do grafo em $O(1)$:
  * *Direto (ID Real $\rightarrow$ ID Grafo):* 3 listas indexadas por ID real (Usuários no Grafo Social, Usuários no Grafo de Temas e Temas no Grafo de Temas).
  * *Reverso (ID Grafo $\rightarrow$ ID Real):* 2 listas indexadas pelo ID interno do grafo (Grafo Social e Grafo de Temas).
* **Rede:** Entidade de fachada/interface global responsável por conectar as entradas do sistema às operações estruturais dos grafos.

---

## 2. Análise de Complexidade Assintótica

### 2.1 Estrutura Lista (Baseada em Array)
* **Acesso:** $O(1)$
* **Inserção:** $O(1)$ (com capacidade disponível)
* **Remoção:** $O(N)$ (devido ao deslocamento de elementos)
* **Realocação de Memória:** $O(N)$
* **Espaço:** $O(m) \approx O(N)$ (onde $m$ é a capacidade alocada)

---

### 2.2 Grafo: Matriz vs. Lista de Adjacência
Considere $n$ como o número de vértices e $p$ como o grau médio de conexões ($p \ll n$):

| Operação | Lista de Adjacência | Matriz de Adjacência |
| :--- | :--- | :--- |
| **Inserção de Vértice** | $O(1)$ | $O(1)$ |
| **Realocação do Grafo** | $O(n^2)$ | $O(n^2)$ |
| **Inserção de Aresta $(u, v)$** | $O(n)$ pior caso / $O(p)$ médio | $O(1)$ |
| **Remoção de Aresta $(u, v)$** | $O(n)$ pior caso / $O(p)$ médio | $O(1)$ |
| **Verificação de Aresta $(u, v)$** | $O(n)$ pior caso / $O(p)$ médio | $O(1)$ |
| **Obter Saídas de $u$** | $O(n)$ pior caso / $O(p)$ médio (cópia direta) | $O(n)$ (varredura da linha $u$) |
| **Obter Entradas de $u$** | $O(n^2)$ (busca em todas as listas) | $O(n)$ (varredura da coluna $u$) |
| **Complexidade de Espaço** | $O(n + p) \approx O(n^2)$ no pior caso denso | $O(n^2)$ fixo |

---

### 2.3 Dicionário (Tradutor de IDs)
Considere $u$ como a quantidade total de usuários e $t$ como a quantidade total de temas:

* **Tradução ID Real $\rightarrow$ ID Grafo:** $O(1)$ (acesso direto por indexação vetorial).
* **Tradução ID Grafo $\rightarrow$ ID Real:** $O(1)$ (acesso direto por indexação vetorial).
* **Complexidade de Espaço:** $O(u + t)$
  * *Listas Diretas:* $2u + t$
  * *Listas Reversas:* $u + (u + t) = 2u + t$
  * *Total:* $O(u + t)$.