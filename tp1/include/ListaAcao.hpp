#ifndef LISTAACAO_HPP
#define LISTAACAO_HPP

#include "Acao.hpp"

/**
 * @brief Classe responsável por gerenciar listas de ponteiros de ações
 * * Enquantos as ações concretas são mantidas por uma lista interna dentro do mercado, a lista de ações aparece na carteira de cada cliente e para cada parâmetro que mantém uma ordenação relativa
 */
class ListaAcao {
    private:
        int _TAMANHO_MAXIMO_ACOES = TAMANHO_MAXIMO_INICIAL_GLOBAL;
        int _q_acoes;
        Acao** acoes;

    public:
        ListaAcao();
        void adicionar_acao(Acao* acao);
        Acao* get_acao(int i);
        void trocar(int i, int j);
        void set(int i, Acao* acao);
        int get_tamanho();
        void remover_acao(int id);
        int get_posicao(int id_acao);

        Acao* const* get_acoes() const;

        void anular();
        void apagar_acoes();
        ~ListaAcao();
};

#endif