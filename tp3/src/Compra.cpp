#include "../include/Compra.hpp"

Compra::Compra() : id(0), timestamp(0), id_usuario(0) {}

void Compra::set(int id, int timestamp, int id_usuario) {
    this->id = id;
    this->timestamp = timestamp;
    this->id_usuario = id_usuario;
}

void Compra::set_produtos(const ListaArray<Item>& produto) {
    this->produtos = produto;
}

void Compra::add_produto(int id, int q) {
    Item item;
    item.set(id, q);
    produtos.add(item);
}

ListaArray<Item> Compra::get_produtos() {
    return produtos;
}

void Compra::ordenar_produtos() {
    produtos.ordenar();
}

int Compra::get_id() {
    return id;
}

int Compra::get_timestamp() {
    return timestamp;
}

int Compra::get_id_usuario() {
    return id_usuario;
}