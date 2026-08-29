#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include "ListaArray.hpp"
#include "Item.hpp"

class Usuario {
    private:
        int id;
        std::string nome;
        int idade;
        std::string cidade;
        std::string estado;
        std::string nacionalidade;
        ListaArray<Item> produtos_comprados;

    public:

        Usuario();

        void set(int, std::string, int, std::string, std::string, std::string);
        void add_produto(int, int);
        ListaArray<Item> get_produtos_comprados();
        
        int get_id();
        std::string get_nome();
        int get_idade();
        std::string get_cidade();
        std::string get_estado();
        std::string get_nacionalidade();

        //funcao pra debugg
        void print();

};

#endif