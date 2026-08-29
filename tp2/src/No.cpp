#include "../include/No.hpp"

No::No(){}

No::No(int id_grafo, TipoEntidade tipo, int id_original) : _id_grafo(id_grafo), _tipo(tipo), _id_original(id_original) {}

// Método para permitir atributos pós construção
void No::config(int id_grafo, TipoEntidade tipo, int id_original) {
    _id_grafo = id_grafo; _tipo = tipo; _id_original = id_original;
}

int No::get_id_interno() {
    return _id_grafo;
}

int No::get_id_original() {
    return _id_original;
}

TipoEntidade No::get_tipo() {
    return _tipo;
}