#include "../include/ListaAcao.hpp"

ListaAcao::ListaAcao() : _q_acoes(0) {
    acoes = new Acao*[_TAMANHO_MAXIMO_ACOES];
}

void ListaAcao::adicionar_acao(Acao* acao) {
    if(_q_acoes >= _TAMANHO_MAXIMO_ACOES) {
        int t = _TAMANHO_MAXIMO_ACOES;
        _TAMANHO_MAXIMO_ACOES *= 2;
        Acao** novoVetor = new Acao*[_TAMANHO_MAXIMO_ACOES];

        for(int i = 0; i < t; i++) {
            novoVetor[i] = acoes[i];
        }

        delete[] acoes;
        acoes = novoVetor;
    }

    acoes[_q_acoes] = acao;
    _q_acoes++;
}

Acao* ListaAcao::get_acao(int i) {
    if(i >= _q_acoes) {
        // print pra debuggar
        return nullptr;
    }
    return acoes[i];
}

void ListaAcao::trocar(int i, int j) {
    if((i >= _q_acoes) || (j >= _q_acoes) || (i < 0) || (j < 0)) {
        return;
    }
    Acao* aux = acoes[i];
    acoes[i] = acoes[j];
    acoes[j] = aux;
}

void ListaAcao::set(int i, Acao* acao) {
    if(i >= _q_acoes) { return; }
    acoes[i] = acao;
}

int ListaAcao::get_tamanho() {
    return _q_acoes;
}

void ListaAcao::remover_acao(int id) {
    for(int i = 0; i < _q_acoes; i++) {
        if(acoes[i]->get_id() == id) {
            for(int j = i; j < _q_acoes-1; j++) {
                acoes[j] = acoes[j+1];
            }
            _q_acoes--;
            return;
        }
    }
}

int ListaAcao::get_posicao(int id_acao) {
    for(int i = 0; i < _q_acoes; i++) {
        if(acoes[i]->get_id() == id_acao) {
            return i;
        }
    }
    return -1;
}

Acao* const* ListaAcao::get_acoes() const {
    return acoes;
}

void ListaAcao::anular() {
    acoes = nullptr;
}

void ListaAcao::apagar_acoes() {
    delete[] acoes;
}

ListaAcao::~ListaAcao() {
    delete[] acoes;
}