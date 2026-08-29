#ifndef ORDENACAO_HPP
#define ORDENACAO_HPP

#include "ListaAcao.hpp"
#include "Profiler.hpp"

/**
 * @brief Classe responsável por gerenciar a ordenação das ações por um determinado parâmetro
 */
class Ordenacao {
    private:
        ListaAcao acoes;
        int _n_param;
        std::string _param;
        void mergesort(int l, int r);
        void merge(int e, int meio, int d);
        void quick(int l, int r);
        int partition(int e, int d);

    public:
        Ordenacao();
        Ordenacao(int n, std::string param);
        void set_param(int n, std::string param);
        void adicionar_acao(Acao* acao);
        void ordenar_mergesort();
        void ordenar_quicksort();
        void ordenar_insertion(); // para casos quase ordenados
        std::string get_param_str();
        int get_param_int();
        bool maior(int i, int j);
        bool maior(Acao* i, Acao* j);
        double calcular_chave(int i);
        double calcular_chave(Acao* i);
        int get_pontuacao(int id_acao);
        void set(int i, Acao* acao);

        void print(); // função apenas para debuggar
        void print_all();
};

#endif