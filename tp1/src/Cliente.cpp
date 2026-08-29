#include "../include/Cliente.hpp"

Cliente::Cliente(int id) : _id(id) {}
Cliente::Cliente() {}

void Cliente::set_id(int id) {
    _id = id;
}

int Cliente::get_id() {
    return _id;
}

int Cliente::get_quantidade_acoes() {
    return _carteira.get_tamanho();
}

Acao* const* Cliente::get_acoes() const {
    return _carteira.get_acoes();
}

void Cliente::comprar_acao(Acao* acao) {
    if(acao == nullptr) {return;}
    _carteira.adicionar_acao(acao);
}

void Cliente::vender_acao(int id_acao) {
    _carteira.remover_acao(id_acao);
}

void Cliente::set(int id_acao, Acao* acao) {
    int i = _carteira.get_posicao(id_acao);
    _carteira.set(i, acao);
}

void Cliente::anular() {
    _carteira.anular();
}

void Cliente::apagar_acoes() {
    _carteira.apagar_acoes();
}