#include "../include/Acao.hpp"

Acao::Acao(int id, int w) : _id(id), _w(w), _ret(0), _avgret(0), _stab(0), _vol(0), _cons(0) {
    _qcotacoes = 0;
    cotacoes = new double[_TAMANHO_MAXIMO_VETOR];
};

Acao::Acao() : _id(0), _w(0), _ret(0), _avgret(0), _stab(0), _vol(0), _cons(0) {
    _qcotacoes = 0;
    cotacoes = new double[_TAMANHO_MAXIMO_VETOR];
    _id = 0;
}

void Acao::set_id(int id, int w) {
    _id = id; _w = w;
}

void Acao::atualiza_metricas() {
    __ret(); __avgret(); __stab(); __vol(); __cons();
}

void Acao::adicionar_cotacao(double cotacao) {
    if(_qcotacoes >= _TAMANHO_MAXIMO_VETOR) {
        int t = _TAMANHO_MAXIMO_VETOR;
        _TAMANHO_MAXIMO_VETOR *= 2;
        double *novoVetor = new double[_TAMANHO_MAXIMO_VETOR];

        for(int i = 0; i < t; i++) {
            novoVetor[i] = cotacoes[i];
        }

        delete[] cotacoes;
        cotacoes = novoVetor;
        // std::cout << "Vetor realocado: novo tamanho: " << _TAMANHO_MAXIMO_VETOR << std::endl;
    }

    cotacoes[_qcotacoes] = cotacao;
    _qcotacoes++;
    atualiza_metricas();
    // std::cout << "cotacao: " << cotacao << " adicionado com sucesso. total: " << _qcotacoes << " na acao " << _id << std::endl;
    // this->print_cotacoes();
}

int Acao::get_id() {
    return _id;
}

bool Acao::igual(double a, double b) {
    double diferenca = a - b;
    if(diferenca > EPSILON) { return false; }
    if(diferenca < -EPSILON) { return false; }
    return true;
}

bool Acao::maior(double a, double b) {
    double diferenca = a - b;
    if(diferenca > EPSILON) { return true; }
    return false;
}

double Acao::r(int i) {
    if(i == 0) { return 0; }
    return (cotacoes[i] / cotacoes[i-1]) - 1;
}

double Acao::ind(int i) {
    if(maior(r(i), 0)) { return 1; }
    else { return 0; }
}

double Acao::__ret() {
    _ret = (cotacoes[_qcotacoes-1] / cotacoes[_qcotacoes-_w]) - 1;
    return _ret;
}

double Acao::__avgret() {
    double soma = 0;
    for(int i = _qcotacoes-_w+1; i < _qcotacoes; i++) {
        soma += r(i);
    }
    _avgret = soma / (_w-1);
    return _avgret;
}

double Acao::__stab() {
    _stab = 1 / (1 + __vol());
    return _stab;
}

double Acao::__vol() {
    double soma = 0;
    double avg = __avgret();
    for(int i = _qcotacoes-_w+1; i < _qcotacoes; i++) {
        soma += pow(r(i) - avg, 2);
    }
    double media = soma / (_w-1);
    _vol = sqrt(media);
    return _vol;
}

double Acao::__cons() {
    double soma = 0;
    for(int i = _qcotacoes-_w+1; i < _qcotacoes; i++) {
        soma +=ind(i);
    }
    _cons = soma / (_w-1);
    return _cons;
}

double Acao::ret() {
    return _ret;
}

double Acao::avgret() {
    return _avgret;
}

double Acao::stab() {
    return _stab;
}

double Acao::vol() {
    return _vol;
}

double Acao::cons() {
    return _cons;
}

/*
 * Função auxiliar para balanciar o gerenciamento de memória e cópia de vetores
*/
void Acao::anular() {
    cotacoes = nullptr;
}

void Acao::apagar_cotacoes() {
    delete[] cotacoes;
}

Acao::~Acao() {
    delete[] cotacoes; // se cotacoes for nullptr não acontece nada
}

int Acao::tamanho_cotacoes() {
    return _qcotacoes;
}

void Acao::print_cotacoes() {
    std::cout << " Acao " << _id << " w=" << _w << " cotacoes: ";
    for(int i = 0; i < _qcotacoes; i++) {
        std::cout << std::fixed << std::setprecision(2) << cotacoes[i] << " ";
    }
    std::cout << std::endl;
}