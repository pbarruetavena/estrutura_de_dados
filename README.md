# Estruturas de Dados — Trabalhos Práticos (UFMG 2026.1)

Este repositório contém as implementações e análises de complexidade/desempenho desenvolvidas para os Trabalhos Práticos (TPs) da disciplina de **Estruturas de Dados** da **Universidade Federal de Minas Gerais (UFMG)** no semestre **2026.1**.

O objetivo principal foi modelar soluções eficientes em C++ para 3 problemas distintos, avaliando o impacto de escolhas de projeto, complexidade assintótica de algoritmos/estruturas e localidade de memória no desempenho real.

---

## 📁 Visão Geral dos Trabalhos

### 📈 TP1: Mercado de Ações
* **Tema:** Processamento de séries temporais de cotações e ranqueamento de carteiras de ações.
* **Estruturas & Algoritmos:** Arrays dinâmicos, listas de ponteiros (`ListaAção`), Quicksort vs. Insertion Sort.
* **Foco de Análise:** Comparação entre estratégias de processamento **Sob Demanda (*Lazy*)** e **Imediata (*Eager*)**, avaliando o *trade-off* entre custo de escrita e custo de consulta.

---

### 🕸️ TP2: Redes Social
* **Tema:** Modelagem de conexões sociais e tópicos de interesse em redes.
* **Estruturas & Algoritmos:** Grafos direcionados genéricos (desacoplados de semântica) e Dicionário de tradução bidirecional $O(1)$ de identificadores.
* **Foco de Análise:** Comparativo de desempenho, acesso e consumo de memória entre representações por **Matriz de Adjacência** e **Lista de Adjacência**.

---

### 🛒 TP3: Mercado
* **Tema:** Plataforma de estoque com filtros compostos de busca sobre usuários, produtos e transações.
* **Estruturas & Algoritmos:** Tabelas Hash com tratamento de colisões por encadeamento externo (função de espalhamento **DJB2**), `ListaArray` e algoritmo de intersecção por dois ponteiros.
* **Foco de Análise:** Eficiência assintótica de consultas combinadas e impacto da **localidade espacial de memória** (vetores contíguos vs. *pointer chasing* em listas encadeadas).

---

## 🛠️ Tecnologias e Diretrizes
* **Linguagem:** C++ (padronizado, uso de TADs e *templates*)
* **Compilação:** `g++` / `make`
* **Métricas:** Complexidade de tempo ($O$), complexidade de espaço e análise de localidade de cache.
