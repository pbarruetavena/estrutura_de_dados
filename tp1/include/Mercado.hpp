#ifndef MERCADO_HPP
#define MERCADO_HPP

#include "Acao.hpp"
#include "Cliente.hpp"
#include "Ordenacao.hpp"
#include <iomanip>
#include <string>
#include "AcaoValor.hpp"
#include <cstdlib>

class Mercado {
    private:
        bool _primeira_consulta;
        int _w;
        int _q_param;
        int _TAMANHO_MAXIMO_CLIENTES = TAMANHO_MAXIMO_INICIAL_GLOBAL;
        int _q_clientes;
        int _TAMANHO_MAXIMO_ACOES = TAMANHO_MAXIMO_INICIAL_GLOBAL;
        int _q_acoes;

        int _q_cotacoes_ord;
        bool _ordenado;

        Cliente* clientes;
        Acao* acoes;
        bool maior(AcaoValor& a, AcaoValor& b, bool maior);
        int mediana(AcaoValor* acoes, int l, int r);
        void quick(AcaoValor* acoes, int e, int d, int n, bool maior);
        int partition(AcaoValor* acoes, int e, int d, bool maior);
        void troca(AcaoValor* a, AcaoValor* b);

        /*
         * Vetor que guarda cada uma das ordenações: cada ordenação mantém uma lista de ações ordenadas com base no seu parâmetro designado
        */
        Ordenacao* parametros;

    public:

        Mercado();
        void set_w(int w);
        void adicionar_metrica(std::string metrica);
        void adicionar_acao(int id_acao);
        void adicionar_cotacao(int id_acao, double preco);
        void adicionar_cliente(int id_cliente);
        void fazer_compra(int id_cliente, int id_acao);
        void fazer_venda(int id_cliente, int id_acao);

        void consulta(int id_consulta, int id_cliente, int n, int m, std::string metricas[], double pesos[]);

};

#endif