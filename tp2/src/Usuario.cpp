#include "../include/Usuario.hpp"


Usuario::Usuario() {}

Usuario::Usuario(int id, std::string nome, int idade) : _id(id), _nome(nome), _idade(idade) {}

// Método para permitir atributos pós construção
void Usuario::config(int id, std::string nome, int idade) {
    _id = id; _nome = nome; _idade = idade;
}

std::string Usuario::get_nome() {
    return _nome;
}

int Usuario::get_id() {
    return _id;
}

int Usuario::get_idade() {
    return _idade;
}