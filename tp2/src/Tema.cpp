#include "../include/Tema.hpp"

Tema::Tema() {}

Tema::Tema(int id, std::string nome, char tipo) : _id(id), _nome(nome), _tipo(tipo) {
}

// Método para permitir atributos pós construção
void Tema::config(int id, std::string nome, char tipo) {
    _id = id; _nome = nome; _tipo = tipo;
}

int Tema::get_id() {
    return _id;
}

std::string Tema::get_nome() {
    return _nome;
}

char Tema::get_tipo() {
    return _tipo;
}      