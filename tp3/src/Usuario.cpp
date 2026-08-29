#include "../include/Usuario.hpp"

Usuario::Usuario() : id(0), nome(""), idade(0), cidade(""), estado(""), nacionalidade("") {}

void Usuario::set(int id, std::string nome, int idade, std::string cidade, std::string estado, std::string nacionalidade) {
    this->id = id; this->nome = nome; this->idade = idade;
    this->cidade = cidade; this->estado = estado; this->nacionalidade = nacionalidade;
}

void Usuario::add_produto(int produto, int quantidade) {
    for(int i = 0; i < produtos_comprados.tamanho(); i++) {
        if(produtos_comprados[i].get_id() == produto) {
            produtos_comprados[i].add_qtd(quantidade);
            return;
        }
    }
    Item item;
    item.set(produto, quantidade);
    produtos_comprados.add(item);
}

ListaArray<Item> Usuario::get_produtos_comprados() {
    return produtos_comprados;
}

int Usuario::get_id() {
    return id;
}

std::string Usuario::get_nome() {
    return nome;
}

int Usuario::get_idade() {
    return idade;
}

std::string Usuario::get_cidade() {
    return cidade;
}

std::string Usuario::get_estado() {
    return estado;
}

std::string Usuario::get_nacionalidade() {
    return nacionalidade;
}

void Usuario::print() {
    std::cout
            << "ID=" << id << " Nome=" << nome << " Idade=" << idade
            << " Cidade=" << cidade << " Estado=" << estado << " Nacionalidade=" << nacionalidade
            << std::endl;

    std::cout << "produtos comprados: "; produtos_comprados.print();
}