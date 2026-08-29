#include "../include/Mercado.hpp"

Mercado::Mercado() {}

void Mercado::cadastrar_usuario(std::string nome, int idade, std::string cidade, std::string estado, std::string nacionalidade) {
    int id = usuarios.tamanho();
    Usuario usuario;
    usuario.set(id, nome, idade, cidade, estado, nacionalidade);
    usuarios.add(usuario);

    hash_usuario.nome.inserir(nome, id);
    hash_usuario.idade.inserir(idade, id);
    hash_usuario.cidade.inserir(cidade, id);
    hash_usuario.estado.inserir(estado, id);
    hash_usuario.nacionalidade.inserir(nacionalidade, id);

    std::cout << "U " << id;
}

void Mercado::cadastrar_produto(std::string nome, double preco, int qtd, std::string categoria, std::string marca, std::string condicao) {
    int id = produtos.tamanho();
    Produto produto;
    produto.set(id, nome, preco, qtd, categoria, marca, condicao);
    produtos.add(produto);

    hash_produto.nome.inserir(nome, id);
    hash_produto.categoria.inserir(categoria, id);
    hash_produto.marca.inserir(marca, id);
    hash_produto.condicao.inserir(condicao, id);

    std::cout << "P " << id; 
}

void Mercado::reposicao(int timestamp, ListaArray<int> produtos_comprados, ListaArray<int> quantidades) {
    if(produtos_comprados.tamanho() != quantidades.tamanho()) {
        return;
    }
    
    int id = reposicoes.tamanho();
    Reposicao repo;
    repo.set(id, timestamp);
    reposicoes.add(repo);

    for(int i = 0; i < produtos_comprados.tamanho(); i++) {
        int id_produto = produtos_comprados[i];
        int quantidade = quantidades[i];
        reposicoes[id].add_produto(id_produto, quantidade);
        
        produtos[id_produto].add_reposicao(id, quantidade);
    }

    hash_reposicao.timestamp.inserir(timestamp, id);
    std::cout << "R " << id;
}

void Mercado::compra(int timestamp, int id_usuario, ListaArray<int> produtos_comprados, ListaArray<int> quantidades) {
    if(produtos_comprados.tamanho() != quantidades.tamanho()) {
        return;
    }
    if(id_usuario < 0 || id_usuario >= usuarios.tamanho()) {
        std::cout << "C INV";
    }


    for(int i = 0; i < produtos_comprados.tamanho(); i++) {
        int id_produto = produtos_comprados[i];
        int quantidade = quantidades[i];
        if(quantidade > produtos[id_produto].get_quantidade()) {
            std::cout << "C INV"; 
            return;
        }
    }
    
    int id = compras.tamanho();
    Compra c;
    c.set(id, timestamp, id_usuario);
    compras.add(c);

    for(int i = 0; i < produtos_comprados.tamanho(); i++) {
        int id_produto = produtos_comprados[i];
        int quantidade = quantidades[i];
        compras[id].add_produto(id_produto, quantidade);
        
        produtos[id_produto].add_compra(id, quantidade);
        produtos[id_produto].add_usuario(id_usuario, quantidade);
        usuarios[id_usuario].add_produto(id_produto, quantidade);
    }

    hash_compra.timestamp.inserir(timestamp, id);
    hash_compra.usuario.inserir(id_usuario, id);
    std::cout << "C " << id;
}

void Mercado::consultar_usuario(ListaArray<Consulta> consultas) {
    ListaArray<int> usuarios_totais;
    bool p_iteracao = true;
    for(int i = 0; i < consultas.tamanho(); i++) {
        //processamento da pesquisa
        std::string atributo = consultas[i].atributo;
        int vi = consultas[i].valor_int;
        std::string vs = consultas[i].valor_string;
        ListaArray<int> usuarios_pesquisa;
        if(atributo == "id") {
            if(vi < usuarios.tamanho() && vi >= 0 ) {usuarios_pesquisa.add(vi); }
        } else if(atributo == "nome") {
            usuarios_pesquisa = hash_usuario.nome.pesquisar(vs);
        } else if(atributo == "idade") {
            usuarios_pesquisa = hash_usuario.idade.pesquisar(vi);
        } else if(atributo == "cidade") {
            usuarios_pesquisa = hash_usuario.cidade.pesquisar(vs);
        } else if(atributo == "estado") {
            usuarios_pesquisa = hash_usuario.estado.pesquisar(vs);
        } else if(atributo == "nacionalidade") {
            usuarios_pesquisa = hash_usuario.nacionalidade.pesquisar(vs);
        } else {
            continue; // teste pra ver se tem atributos errados na consulta
        }
     
        usuarios_pesquisa.ordenar();

        if(p_iteracao) {
            usuarios_totais = usuarios_pesquisa;
            p_iteracao = false;
        } else {
            ListaArray<int> resultado;
            resultado.merge(usuarios_pesquisa, usuarios_totais);
            // std::cout << "resultado atr " << atributo;
            // resultado.print();
            usuarios_totais = resultado;
        }

    }

    //usuarios_totais.ordenar();

    if(usuarios_totais.tamanho() == 0) {
        std::cout << "LU VAZIO";
        return;
    }
    for(int i = 0; i < usuarios_totais.tamanho(); i++) {
        if(i!=0) {std::cout << std::endl;}
        int id = usuarios_totais[i];
        std::cout << "LU resultado_" << i+1 << " usuario " <<
        id << " " << usuarios[id].get_nome() << " " << usuarios[id].get_idade() << " " << usuarios[id].get_cidade() <<
        " " << usuarios[id].get_estado() << " " << usuarios[id].get_nacionalidade();// << std::endl;

        ListaArray<Item> compras_user = usuarios[id].get_produtos_comprados();
        compras_user.ordenar();
        if(compras_user.tamanho() == 0) { continue; }
        std::cout << std::endl;
        for(int j = 0; j < compras_user.tamanho(); j++) {
            if(j!=0) {std::cout << " ";}
            std::cout << "produto_" << j+1 << " " << compras_user[j].get_id() << " " << compras_user[j].get_qtd();
        }
    }
}

void Mercado::consultar_produto(ListaArray<Consulta> consultas) {
    ListaArray<int> produtos_totais;
    bool p_iteracao = true;
    for(int i = 0; i < consultas.tamanho(); i++) {
        std::string atr = consultas[i].atributo;
        int vi = consultas[i].valor_int;
        std::string vs = consultas[i].valor_string;
        ListaArray<int> produtos_pesquisa;
        if(atr == "id") {
            if(vi < produtos.tamanho() && vi >= 0 ) {produtos_pesquisa.add(vi); }
        } else if(atr == "nome") {
            produtos_pesquisa = hash_produto.nome.pesquisar(vs);
        } else if(atr == "categoria") {
            produtos_pesquisa = hash_produto.categoria.pesquisar(vs);
        } else if(atr == "marca") {
            produtos_pesquisa = hash_produto.marca.pesquisar(vs);
        } else if(atr == "condicao") {
            produtos_pesquisa = hash_produto.condicao.pesquisar(vs);
        } else {
            continue; // teste pra ver se tem atributos errados na consulta
        }

        produtos_pesquisa.ordenar();
        if(p_iteracao) {
            produtos_totais = produtos_pesquisa;
            p_iteracao = false;
        } else {
            ListaArray<int> resultado;
            resultado.merge(produtos_pesquisa, produtos_totais);
            produtos_totais = resultado;
        }
    }

    //produtos_totais.ordenar();

    if(produtos_totais.tamanho() == 0) {
        std::cout << "LP VAZIO";// << std::endl;
        return;
    }

    for(int i = 0; i < produtos_totais.tamanho(); i++) {
        if(i!=0) {std::cout << std::endl;}
        int id = produtos_totais[i];
        std::cout << "LP resultado_" << i+1 << " produto " <<
        id << " " << produtos[id].get_nome() << " " << std::fixed << std::setprecision(2) << produtos[id].get_preco() <<
        " " << produtos[id].get_quantidade() << " " << produtos[id].get_categoria() <<
        " " << produtos[id].get_marca() << " " << produtos[id].get_condicao();// << std::endl;

        ListaArray<Item> compradores_produto = produtos[id].get_compradores();
        compradores_produto.ordenar();
        if(compradores_produto.tamanho() == 0) { continue; }
        std::cout << std::endl;
        for(int j = 0; j < compradores_produto.tamanho(); j++) {
            if(j!=0) { std::cout << " "; }
            std::cout << "usuario_" << j+1 << " " << compradores_produto[j].get_id() << " " << compradores_produto[j].get_qtd();
        }

    }
}


void Mercado::consultar_compra(ListaArray<Consulta> consultas) {
    ListaArray<int> compras_totais;
    bool p_iteracao = true;

    for(int i = 0; i < consultas.tamanho(); i++) {
        std::string atributo = consultas[i].atributo;
        int vi = consultas[i].valor_int;
        ListaArray<int> compras_pesquisadas;
        if(atributo == "id") {
            if(vi < compras.tamanho() && vi >= 0 ) {compras_pesquisadas.add(vi); }
        } else if(atributo == "timestamp") {
            compras_pesquisadas = hash_compra.timestamp.pesquisar(vi);
        } else if(atributo == "id_usuario") {
            compras_pesquisadas = hash_compra.usuario.pesquisar(vi);
        } else if(atributo == "id_produto") {
            compras_pesquisadas = produtos[vi].get_compras();
        } else {
            continue; // teste pra ver se tem atributos errados na consulta
        }
       
        compras_pesquisadas.ordenar();


        if(p_iteracao) {
            compras_totais = compras_pesquisadas;
            p_iteracao = false;
        } else {
            ListaArray<int> resultado;
            resultado.merge(compras_pesquisadas, compras_totais);
            compras_totais = resultado;
        }
    }

    //compras_totais.ordenar();

    if(compras_totais.tamanho() == 0) {
        std::cout << "LC VAZIO"; // << std::endl;
        return;
    }
    for(int i = 0; i < compras_totais.tamanho(); i++) {
        if(i!=0) {std::cout << std::endl;}
        int id = compras_totais[i];
        std::cout << "LC resultado_" << i+1 << " compra " <<
        id << " timestamp " << compras[id].get_timestamp() <<
        " usuario " << compras[id].get_id_usuario(); // << std::endl;

        compras[id].ordenar_produtos();
        ListaArray<Item> itens = compras[id].get_produtos();
        if(itens.tamanho() == 0) { continue; }
        std::cout << std::endl;
        for(int j = 0; j < itens.tamanho(); j++) {
            if(j!=0) {std::cout << " ";}
            std::cout << "produto_" << j+1 << " " << itens[j].get_id() << " " << itens[j].get_qtd();
        }
    }
}

void Mercado::consultar_reposicao(ListaArray<Consulta> consultas) {
    ListaArray<int> reposicao_totais;
    bool p_iteracao = true;

    for(int i = 0; i < consultas.tamanho(); i++) {
        std::string atributo = consultas[i].atributo;
        int vi = consultas[i].valor_int;
        ListaArray<int> reposicoes_pesquisadas;
        if(atributo == "id") {
            if(vi < reposicoes.tamanho() && vi >= 0 ) {reposicoes_pesquisadas.add(vi); }
        } else if(atributo == "timestamp") {
            reposicoes_pesquisadas = hash_reposicao.timestamp.pesquisar(vi);
        } else if(atributo == "id_produto") {
            reposicoes_pesquisadas = produtos[vi].get_reposicao();
        } else {
            continue; // teste pra ver se tem atributos errados na consulta
        }
       
        reposicoes_pesquisadas.ordenar();

        if(p_iteracao) {
            reposicao_totais = reposicoes_pesquisadas;
            p_iteracao = false;
        } else {
            ListaArray<int> resultado;
            resultado.merge(reposicoes_pesquisadas, reposicao_totais);
            reposicao_totais = resultado;
        }
    }

    //reposicao_totais.ordenar();

    if(reposicao_totais.tamanho() == 0) {
        std::cout << "LR VAZIO"; 
        return;
    }
    for(int i = 0; i < reposicao_totais.tamanho(); i++) {
        if(i!=0) {std::cout << std::endl;}
        int id = reposicao_totais[i];
        std::cout << "LR resultado_" << i+1 << " reposicao " <<
        id << " timestamp " << reposicoes[id].get_timestamp(); //<< std::endl;

        reposicoes[id].ordenar_produtos();
        ListaArray<Item> itens = reposicoes[id].get_produtos();
        if(itens.tamanho() == 0) { continue; }
        std::cout << std::endl;
        for(int j = 0; j < itens.tamanho(); j++) {
            if(j!=0) {std::cout << " ";}
            std::cout << "produto_" << j+1 << " " << itens[j].get_id() << " " << itens[j].get_qtd();
        }
    }
}


void Mercado::print_estado() {
    std::cout << "\n===== USUARIOS =====\n";

    for(int i = 0; i < usuarios.tamanho(); i++)
    {
        usuarios[i].print();
    }

    std::cout << "====================\n";

    std::cout << "\n===== PRODUTOS =====\n";

    for(int i = 0; i < produtos.tamanho(); i++)
    {
        produtos[i].print();
    }

    std::cout << "====================\n";
}