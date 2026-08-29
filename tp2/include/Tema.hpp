#ifndef TEMA_HPP
#define TEMA_HPP

#include <string>

class Tema {
    private:
        int _id;
        std::string _nome;
        char _tipo;

    public:
        Tema();
        Tema(int id, std::string nome, char tipo);
        // Método para permitir atributos pós construção
        void config(int id, std::string nome, char tipo);

        int get_id();
        std::string get_nome();
        char get_tipo();      
};

#endif