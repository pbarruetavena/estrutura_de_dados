#include "Reposicao.hpp"

Reposicao::Reposicao() : id(0), timestamp(0) {}

void Reposicao::set(int id, int timestamp) {
    this->id = id;
    this->timestamp = timestamp;
}

void Reposicao::set_produtos(const ListaArray<Item>& produto) {
    this->produtos = produto;
}

void Reposicao::add_produto(int id, int q) {
    Item item;
    item.set(id, q);
    produtos.add(item);
}

ListaArray<Item> Reposicao::get_produtos() {
    return produtos;
}

void Reposicao::ordenar_produtos() {
    produtos.ordenar();
}

int Reposicao::get_id() {
    return id;
}

int Reposicao::get_timestamp() {
    return timestamp;
}