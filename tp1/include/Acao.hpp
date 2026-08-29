#ifndef ACAO_HPP
#define ACAO_HPP

#include <iostream>
#include <cmath>
#include <iomanip>

constexpr int TAMANHO_MAXIMO_INICIAL_GLOBAL = 15000;
constexpr int TAMANHO_MAXIMO_COTACOES = 300;
const double EPSILON = 1e-9;

class Acao {
    private:
        int _TAMANHO_MAXIMO_VETOR = TAMANHO_MAXIMO_COTACOES;
        int _w;
        int _qcotacoes;
        int _id;
        double *cotacoes;
        double r(int i);
        double ind(int i);
        bool igual(double a, double b);
        bool maior(double a, double b);
        // para estratégia imediata
        double _ret;
        double _avgret;
        double _stab;
        double _vol;
        double _cons;
        double __ret();
        double __avgret();
        double __stab();
        double __vol();
        double __cons();

    public:
        Acao();
        Acao(int id, int w);
        void set_id(int id, int w);
        void adicionar_cotacao(double cotacao);
        int get_id();
        double ret();
        double avgret();
        double stab();
        double vol();
        double cons();
        void atualiza_metricas();
        int tamanho_cotacoes();

        void anular();
        void apagar_cotacoes();
        ~Acao();
    
        //debbugar
        void print_cotacoes();
};

#endif