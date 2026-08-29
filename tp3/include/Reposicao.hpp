#ifndef REPOSICAO_HPP
#define REPOSICAO_HPP

#include <string>
#include "ListaArray.hpp"
#include "Item.hpp"

class Reposicao {
    private:
        int id;
        int timestamp;
        ListaArray<Item> produtos;

    public:

        Reposicao();

        void set(int, int);
        void set_produtos(const ListaArray<Item>&);
        void add_produto(int, int);
        ListaArray<Item> get_produtos();
        void ordenar_produtos();

        int get_id();
        int get_timestamp();
};

#endif