#include "../include/Produto.hpp"


Produto::Produto() : id(0), nome(""), preco(0.0), quantidade(0), categoria(""), marca(""), condicao("") {}

void Produto::set(int id, std::string nome, double preco, int quantidade, std::string categoria, std::string marca, std::string condicao) {
    this->id = id; this->nome = nome; this->preco = preco; this->quantidade = quantidade;
    this->categoria = categoria; this->marca = marca; this->condicao = condicao;
}

void Produto::add_usuario(int usuario, int quantidade) {
    for(int i = 0; i < compradores.tamanho(); i++) {
        if(compradores[i].get_id() == usuario) {
            compradores[i].add_qtd(quantidade);
            return;
        }
    }
    Item item;
    item.set(usuario, quantidade);
    compradores.add(item);
}

ListaArray<Item> Produto::get_compradores() {
    return compradores;
}

void Produto::add_compra(int compra, int qtd) {
    if(qtd > quantidade) {
        return;
    }
    quantidade = quantidade - qtd;
    compras.add(compra);
};

ListaArray<int> Produto::get_compras() {
    return compras;
}

void Produto::add_reposicao(int reposicao, int qtd) {
    reposicoes.add(reposicao);
    quantidade = quantidade + qtd;
}

ListaArray<int> Produto::get_reposicao() {
    return reposicoes;
}


int Produto::get_id() {
    return id;
}

std::string Produto::get_nome() {
    return nome;
}

double Produto::get_preco() {
    return preco;
}

int Produto::get_quantidade() {
    return quantidade;
}

std::string Produto::get_categoria() {
    return categoria;
}

std::string Produto::get_marca() {
    return marca;
}

std::string Produto::get_condicao() {
    return condicao;
}

void Produto::print() {
    std::cout
            << "ID=" << id << " Nome=" << nome << " Preco=" << preco << " Qtd=" << quantidade << " Categoria=" << categoria
            << " Marca=" << marca << " Condicao=" << condicao << std::endl;

    std::cout << "usuarios compradores: "; compradores.print();
}