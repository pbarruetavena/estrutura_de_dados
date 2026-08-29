#include "../include/Ordenacao.hpp"

Ordenacao::Ordenacao(int n, std::string param) : _n_param(n), _param(param) {}
Ordenacao::Ordenacao(){}

void Ordenacao::set_param(int n, std::string param) {
    _n_param = n;
    _param = param;
}

void Ordenacao::adicionar_acao(Acao* acao) {
    acoes.adicionar_acao(acao);
}

void Ordenacao::set(int i, Acao* acao) {
    acoes.set(i, acao);
}

void Ordenacao::ordenar_insertion() {
    MedidorOrdenacao medidor;
    int tamanho = acoes.get_tamanho();

    for(int i = 1; i < tamanho; i++) {
        Acao* chave = acoes.get_acao(i);
        int k = i-1;

        while(k >= 0 && maior(chave, acoes.get_acao(k))) {
            acoes.set(k+1, acoes.get_acao(k));
            k--;
        }

        acoes.set(k+1, chave);
    }
} 

void Ordenacao::merge(int e, int m, int d) {
    // std::cout << "init Iteracao merge: indices e=" << e << " m=" << m << " d=" << d << std::endl;
    int n1 = m - e + 1;
    int n2 = d - m;

    Acao** esquerda = new Acao*[n1];
    Acao** direita = new Acao*[n2];

    for(int i = 0; i < n1; i++) { esquerda[i] = acoes.get_acao(e+i); }
    for(int i = 0; i < n2; i++) { direita[i] = acoes.get_acao(m+1+i); }

    int i_esq = 0; int i_dir = 0; int j = e;
    while(i_esq < n1 && i_dir < n2) {
        if(maior(esquerda[i_esq], direita[i_dir])) {
            acoes.set(j, esquerda[i_esq]);
            i_esq++;
        } else {
            acoes.set(j, direita[i_dir]);
            i_dir++;
        }
        j++;
    }


    while(i_esq < n1) {
        acoes.set(j, esquerda[i_esq]);
        i_esq++; j++;
    }
    while(i_dir < n2) {
        acoes.set(j, direita[i_dir]);
        i_dir++; j++;
    }

    delete[] esquerda;
    delete[] direita;
    // std::cout << "final Iteracao merge: indices e=" << e << " m=" << m << " d=" << d << std::endl;
}

void Ordenacao::mergesort(int e, int d) {
    // std::cout << "init Iteracao mergesort: indices " << e << " até " << d << std::endl;
    if(e < d) {
        int meio = e + (d - e)/2;

        this->mergesort(e, meio);
        this->mergesort(meio+1, d);

        this->merge(e, meio, d);
    }
    // std::cout << "final Iteracao mergesort: indices " << e << " até " << d << std::endl;
}

void Ordenacao::ordenar_mergesort() {
    //std::cout << "Iniciando ordenacao, tamanho do vetor: " << acoes.get_tamanho() << std::endl;
    mergesort(0,acoes.get_tamanho()-1);
}

void Ordenacao::quick(int e, int d) {
    if(e < d) {
        int p = partition(e, d);
        quick(e, p-1);
        quick(p+1, d); // só vai ordenar esse lado se o o pivo estiver a esquerda do elemento n 
        
    }
}

int Ordenacao::partition(int in, int fm) {
    Acao* pivo = acoes.get_acao(fm);
    int i = in;

    for(int j = in; j <= fm-1; j++) {
        if(maior(acoes.get_acao(j), pivo)) {
            Acao* aux = acoes.get_acao(i);
            acoes.set(i++, acoes.get_acao(j));
            acoes.set(j, aux);
        }
    }
    Acao* aux = acoes.get_acao(i);
    acoes.set(i, acoes.get_acao(fm));
    acoes.set(fm, aux);
    return i;
}

void Ordenacao::ordenar_quicksort() {
    quick(0, acoes.get_tamanho()-1);
}


std::string Ordenacao::get_param_str() {
    return _param;
}

int Ordenacao::get_param_int() {
    return _n_param;
}

double Ordenacao::calcular_chave(int i) {
    if(_param == "RET") {
        return acoes.get_acao(i)->ret();
    } else if(_param == "AVGRET") {
        return acoes.get_acao(i)->avgret();
    } else if(_param == "STAB") {
        return acoes.get_acao(i)->stab();
    } else if(_param == "CONS") {
        return acoes.get_acao(i)->cons();
    }
    return 0;
}

double Ordenacao::calcular_chave(Acao* i) {
    if(_param == "RET") {
        return i->ret();
    } else if(_param == "AVGRET") {
        return i->avgret();
    } else if(_param == "STAB") {
        return i->stab();
    } else if(_param == "CONS") {
        return i->cons();
    }
    return 0;
}

bool Ordenacao::maior(int i, int j) {
    double diferenca = calcular_chave(i) - calcular_chave(j);
    if(diferenca > EPSILON) { return true; }
    if(diferenca < -EPSILON) { return false; }
    return acoes.get_acao(i)->get_id() < acoes.get_acao(j)->get_id();
}

bool Ordenacao::maior(Acao* i, Acao* j) {
    double diferenca = calcular_chave(i) - calcular_chave(j);
    if(diferenca > EPSILON) { return true; }
    if(diferenca < -EPSILON) { return false; }
    return i->get_id() < j->get_id();
}

int Ordenacao::get_pontuacao(int id_acao) {
    int pos = acoes.get_posicao(id_acao);
    int n = acoes.get_tamanho();
    if(pos == -1) { return 0; }
    return n - pos;
}


void Ordenacao::print() {
    Acao* const* aux = acoes.get_acoes();
    for(int i = 0; i < acoes.get_tamanho(); i++) {
        std::cout << "[" << i << "] id=" << aux[i]->get_id() << " p=" << calcular_chave(aux[i]) << std::endl;
    }
}

void Ordenacao::print_all() {
    std::cout << "Descricao do parametro" << get_param_str() << std::endl;
    Acao* const* aux = acoes.get_acoes();
    for(int i = 0; i < acoes.get_tamanho(); i++) {
        std::cout << "[" << i << "] id=" << aux[i]->get_id();
        aux[i]->print_cotacoes();
    }
}