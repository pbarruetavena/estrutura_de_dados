#ifndef COMPRA_HPP
#define COMPRA_HPP

#include <string>
#include "ListaArray.hpp"
#include "Item.hpp"

class Compra {
    private:
        int id;
        int timestamp;
        int id_usuario;
        ListaArray<Item> produtos;

    public:

        Compra();
        void set(int, int, int);
        void set_produtos(const ListaArray<Item>&);
        void add_produto(int, int);
        ListaArray<Item> get_produtos();
        void ordenar_produtos();

        int get_id();
        int get_timestamp();
        int get_id_usuario();
};

#endif