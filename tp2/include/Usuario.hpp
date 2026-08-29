#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

class Usuario {
    private:

        std::string _nome;
        int _idade;
        int _id;

    public:

        Usuario();
        Usuario(int id, std::string nome, int idade);
        // Método para permitir atributos pós construção
        void config(int id, std::string nome, int idade);

        std::string get_nome();
        int get_id();
        int get_idade();
};

#endif