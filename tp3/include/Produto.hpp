#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>
#include "ListaArray.hpp"
#include "Item.hpp"

class Produto {
    private:
        int id;
        std::string nome;
        double preco;
        int quantidade;
        std::string categoria;
        std::string marca;
        std::string condicao;
        // compradores que ja compraram esse produto: para consulta de produto
        ListaArray<Item> compradores;
        // ListaArray<int> qtd_comprado;

        // compras e reposicoes que tem esse produto: para consultas de compra usando atributo id_produto
        ListaArray<int> compras;
        ListaArray<int> reposicoes;

    public:

        Produto();

        void set(int, std::string, double, int, std::string, std::string, std::string);
        void add_usuario(int, int);
        ListaArray<Item> get_compradores();
        // ListaArray<int> get_quantidade_compradores();
        void add_compra(int compra, int qtd);
        ListaArray<int> get_compras();
        void add_reposicao(int reposicao, int qtd);
        ListaArray<int> get_reposicao();

        int get_id();
        std::string get_nome();
        double get_preco();
        int get_quantidade();
        std::string get_categoria();
        std::string get_marca();
        std::string get_condicao();

        //apenas para debugar
        void print();
};

#endif