#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "ListaAcao.hpp"

class Cliente {
    private:

        int _id;
        ListaAcao _carteira;

    public:
        Cliente();
        Cliente(int id);
        void set_id(int id);
        int get_id();
        int get_quantidade_acoes();
        Acao* const* get_acoes() const;
        void comprar_acao(Acao* acao);
        void vender_acao(int id_acao);
        void set(int id_acao, Acao* acao);

        void anular();
        void apagar_acoes();
};

#endif