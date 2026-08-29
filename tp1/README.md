# Documentação Técnica - TP1: Estruturas de Dados

## 1. Modelagem e Entidades (C++)

O sistema modela um mercado de ações utilizando arrays dinâmicos para gerenciar entidades e cotações.

### 1.1 Principais Entidades
* **Ação:** Armazena os dados da ação, histórico interno de cotações em array e métodos para cálculo das métricas.
* **ListaAção:** Lista de referências (ponteiros) para ações, permitindo manipulações e ordenações locais sem duplicar nem alterar os objetos reais em memória.
* **Cliente:** Representa um participante do mercado contendo uma carteira de ações baseada em `ListaAção`.
* **Ordenação:** Mantém o ranking global das ações em relação a uma métrica específica via `ListaAção`.
* **AçãoValor:** Estrutura auxiliar usada para associar uma ação à sua pontuação agregada durante a consulta da carteira.
* **Mercado:** Entidade central (fachada para a `main`) que gerencia as listas de clientes, ações concretas e ordenações globais.

> **Nota de Implementação:** O uso de arrays de ponteiros em `ListaAção` exige revalidação de ponteiros caso ocorra realocação de memória das ações.

---

## 2. Estratégias de Processamento

| Característica | Sob Demanda (Lazy) | Imediata (Eager) |
| :--- | :--- | :--- |
| **Cálculo de Métricas** | Calculadas apenas no momento da consulta. | Calculadas a cada nova inserção de cotação. |
| **Ordenações Globais** | Executadas durante a consulta via **Quicksort**. | Atualizadas a cada cotação via **Insertion Sort** (otimizado para listas quase ordenadas). |
| **Ordenação da Carteira** | **Quicksort** adaptado para os $n$ primeiros elementos. | **Quicksort** adaptado para os $n$ primeiros elementos. |

### Algoritmo de Consulta
1. Recupera a carteira do cliente (`const ListaAção`).
2. Obtém/atualiza as ordenações globais de cada métrica solicitada.
3. Agrega a pontuação de cada ação em uma estrutura `AçãoValor`.
4. Ordena a carteira de forma decrescente para os $n$ melhores e crescente para os $n$ piores (devido a critérios de desempate não-simétricos).

---

## 3. Análise de Complexidade

Considere:
* $N$: Total de ações no mercado
* $n$: Número de ações solicitadas na consulta
* $c$: Número de clientes
* $w$: Janela temporal de cotações

### 3.1 Operações de Lista (Array)
* **Acesso:** $O(1)$
* **Busca linear:** $O(N)$
* **Inserção (Sob Demanda):** $O(1)$
* **Inserção de Cotação (Imediata):** $O(N + w)$ (recalcula métricas em $O(w)$ e reordena com Insertion Sort em $\Omega(N)$)
* **Realocação de Ações:** $O(N^2 \cdot c)$ no pior caso (devido à atualização de referências em todas as carteiras e ordenações).

### 3.2 Cálculo das Métricas
* **Retorno Acumulado:** $O(1)$
* **Média de Retorno:** $O(w)$
* **Estabilidade:** $O(w)$
* **Consistência:** $O(w)$
*(Na estratégia imediata, o custo de acesso torna-se $O(1)$, transferindo $O(w)$ para a inserção).*

### 3.3 Custo Total das Operações Principais

| Operação | Estratégia Sob Demanda | Estratégia Imediata |
| :--- | :--- | :--- |
| **Ordenação Global** | $O(w \cdot N \log N)$ | Diluído nas inserções |
| **Ordenação Carteira** | $O(w \cdot n \log n)$ | $O(n \log n)$ |
| **Consulta Completa** | $O(\max(w \cdot N \log N,\; c \cdot N))$ | $O(\max(n \log n,\; c \cdot N))$ |
