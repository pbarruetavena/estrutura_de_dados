#include "../include/Mercado.hpp"

Mercado::Mercado() {
    _primeira_consulta = true;
    _q_acoes = 0; _q_clientes = 0; _q_param = 0; _q_cotacoes_ord = 0; _ordenado = true;
    parametros = new Ordenacao[4];
    clientes = new Cliente[_TAMANHO_MAXIMO_CLIENTES];
    acoes = new Acao[_TAMANHO_MAXIMO_ACOES];
};

void Mercado::set_w(int w) {
    _w = w;
}

void Mercado::adicionar_metrica(std::string metrica) {
    parametros[_q_param].set_param(_q_param, metrica);
    for(int i = 0; i < _q_acoes; i++) {
        parametros[_q_param].adicionar_acao(&(acoes[i]));
    }
    _q_param++;
}

void Mercado::adicionar_acao(int id_acao) {
    if(_q_acoes >= _TAMANHO_MAXIMO_ACOES) {
        int t = _TAMANHO_MAXIMO_ACOES;
        _TAMANHO_MAXIMO_ACOES *= 2;
        Acao *novoVetor = new Acao[_TAMANHO_MAXIMO_ACOES];

        for(int i = 0; i < t; i++) {
            novoVetor[i].apagar_cotacoes(); // não deixa a memoria alocada junto ao vetor vazar
            novoVetor[i] = acoes[i]; // passa a referência de cotacoes para o novo vetor

            for(int j = 0; j < _q_param; j++) { // com a realocação é necessario corrigir os endereços dentro da lista de acoes ordenada por parametros
                parametros[j].set(i, &(novoVetor[i])); // no caso desse vetor, ele tem as mesmas ações que o vetor original de ação e nesse caso não importa a ordem (vai ordenar depois)
            }
            for(int j = 0; j < _q_clientes; j++) {
                clientes[j].set(novoVetor[i].get_id(), &novoVetor[i]);
            }

            acoes[i].anular();
        }

        delete[] acoes;
        acoes = novoVetor;
    }

    acoes[_q_acoes].set_id(id_acao, _w);
    for(int i = 0; i < _q_param; i++) { // cada vez que uma nova ação for inserida, ela deve ser inserida no vetor de ordenação global por cada um dos parâmetros
        parametros[i].adicionar_acao(&(acoes[_q_acoes]));
    }
    _q_acoes++;
    _ordenado = false;
}

void Mercado::adicionar_cliente(int id_cliente) {
    if(_q_clientes >= _TAMANHO_MAXIMO_CLIENTES) {
        int t = _TAMANHO_MAXIMO_CLIENTES;
        _TAMANHO_MAXIMO_CLIENTES *= 2;
        Cliente* novosClientes = new Cliente[_TAMANHO_MAXIMO_CLIENTES];

        for(int i = 0; i < t; i++) {
            novosClientes[i].apagar_acoes();
            novosClientes[i] = clientes[i];
            clientes[i].anular();
        }

        delete[] clientes;
        clientes = novosClientes;
    }
    clientes[_q_clientes].set_id(id_cliente);
    _q_clientes++;
}

void Mercado::adicionar_cotacao(int id_acao, double preco) {
    MedidorAtualizacao medidor;
    for(int i = 0; i < _q_acoes; i++) {
        if(acoes[i].get_id() == id_acao) {
            acoes[i].adicionar_cotacao(preco);
            break;
        }
    }

    if(++_q_cotacoes_ord >= _q_acoes) {
        for(int i = 0; i < _q_param; i++) { // toda vez que uma nova cotação é adicionar, ordena os parâmetros com o inserction, pois assume-se que está quase ordenado
            parametros[i].ordenar_insertion();
        }
        _ordenado = true;
        _q_cotacoes_ord = 0;
    } else {
        _ordenado = false;
    }
    
}

void Mercado::fazer_compra(int id_cliente, int id_acao) {
    Acao* acao = nullptr;
    for(int i = 0; i < _TAMANHO_MAXIMO_ACOES; i++) {
        if(acoes[i].get_id() == id_acao) {
            acao = &(acoes[i]);
        }
    }
    if(acao == nullptr) { return; }
    for(int i = 0; i < _TAMANHO_MAXIMO_CLIENTES; i++) {
        if(clientes[i].get_id() == id_cliente) {
            clientes[i].comprar_acao(acao);
            return;
        }
    }
}

void Mercado::fazer_venda(int id_cliente, int id_acao) {
    for(int i = 0; i < _TAMANHO_MAXIMO_CLIENTES; i++) {
        if(clientes[i].get_id() == id_cliente) {
            clientes[i].vender_acao(id_acao);
            return;
        }
    }
}

void Mercado::consulta(int id_consulta, int id_cliente, int n, int m, std::string metricas[], double pesos[]) {
    MedidorConsulta medidor;
    Cliente *cliente = nullptr;
    for(int i = 0; i < _q_clientes; i++) {
        if(clientes[i].get_id() == id_cliente) {
            cliente = &(clientes[i]);
            break;
        }
    }
    if(cliente == nullptr) { return; }
    

    int tamanho = cliente->get_quantidade_acoes();
    AcaoValor* carteira = new AcaoValor[tamanho];
    Acao* const* acoes = cliente->get_acoes();
    for(int i = 0; i < tamanho; i++) {
        carteira[i].acao = (acoes[i]);
        carteira[i].pontuacao = 0;
    }

    for(int i = 0; i < m; i++) {
        // std::cout << "Iniciando calculo para parametro " << metricas[i] << std::endl;
        int k_metrica = -1;
        for(int j = 0; j < _q_param; j++) {
            if(parametros[j].get_param_str() == metricas[i]) {
                k_metrica = j;
                break;
            }
        }
        if(k_metrica == -1) { return; }
        if(!_ordenado) {
            parametros[k_metrica].ordenar_insertion();
        }
        for(int j = 0; j < tamanho; j++) {
            int id_acao = carteira[j].acao->get_id();
            carteira[j].pontuacao += parametros[k_metrica].get_pontuacao(id_acao) * pesos[i];
        }
    }

    

    if(n > tamanho) {
        n = tamanho;
    }
    quick(carteira, 0, tamanho-1, n, true);

    //ordenado em forma crescente
    for(int i = 0; i < n; i++) {
        if(!_primeira_consulta) {
            std::cout << std::endl;
        }
        _primeira_consulta = false;
        std::cout << "R " << id_consulta << " M " << i << " " << carteira[i].acao->get_id() << " " << std::fixed << std::setprecision(2) << carteira[i].pontuacao;
    }
    quick(carteira, 0, tamanho-1, n,  false); // ordenação crescente (não é simétrica)
    for(int i = 0; i < n; i++) {
        std::cout << std::endl << "R " << id_consulta << " P " << i << " " << carteira[i].acao->get_id() << " " << std::fixed << std::setprecision(2) << carteira[i].pontuacao;
    }

    delete[] carteira;
}

bool Mercado::maior(AcaoValor& i, AcaoValor& j, bool emaior) {
    double diferenca = i.pontuacao - j.pontuacao;
    if(emaior) { // i maior que j
        if(diferenca > EPSILON) { return true; }
        if(diferenca < -EPSILON) { return false; }
        return i.acao->get_id() < j.acao->get_id();
    } else { // i menor que j
        if(diferenca > EPSILON) { return false; }
        if(diferenca < -EPSILON) { return true; }
        return i.acao->get_id() < j.acao->get_id();
    }
}

int Mercado::mediana(AcaoValor* acoes, int l, int r) {
    int m = l + (r - l) / 2;

    AcaoValor* val_l = &acoes[l];
    AcaoValor* val_r = &acoes[r];
    AcaoValor* val_m = &acoes[m];

    if ((maior(*val_l, *val_m, true) && maior(*val_r, *val_l, true)) || 
        (maior(*val_l, *val_r, true) && maior(*val_m, *val_l, true))) {return l;}

    if ((maior(*val_m, *val_l, true) && maior(*val_r, *val_m, true)) || 
        (maior(*val_m, *val_r, true) && maior(*val_l, *val_m, true))) {return m;}

    return r;
}

void Mercado::quick(AcaoValor* acoes, int e, int d, int n, bool e_maior) {
    if(e < d) {
        int p = partition(acoes, e, d, e_maior);
        quick(acoes, e, p-1, n, e_maior); // ordena só o o lado esquerdo pra conseguir o n primeiros
        if(p < n-1) {
            quick(acoes, p+1, d, n, e_maior); // só vai ordenar esse lado se o o pivo estiver a esquerda do elemento n 
        }
    }
}

int Mercado::partition(AcaoValor* acoes, int e, int d, bool e_maior) {
    AcaoValor* p = &acoes[d];
    if(d - e >= 2) {
        int pivo_idx = mediana(acoes, e, d);
        troca(&acoes[pivo_idx], &acoes[d]);
    }
    int i = e;

    for(int j = e; j <= d -1; j++) {
        if(maior(acoes[j], *p, e_maior)) {
            troca(&acoes[i++], &acoes[j]);
        }
    }
    troca(&acoes[i], &acoes[d]);
    return i;
}

void Mercado::troca(AcaoValor* a, AcaoValor* b) {
    AcaoValor aux = *a;
    *a = *b;
    *b = aux;
}