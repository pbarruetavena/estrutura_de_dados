#ifndef TABELAS_HPP
#define TABELAS_HPP

#include "TabelaHash.hpp"
#include "ListaPesquisa.hpp"

// structs pra organizar todos os atributos buscáveis

struct TabelasUsuario {
    TabelaHash<std::string> nome;
    TabelaHash<int> idade;
    TabelaHash<std::string> cidade;
    TabelaHash<std::string> estado;
    TabelaHash<std::string> nacionalidade;
};

struct TabelasProduto {
    TabelaHash<std::string> nome;
    TabelaHash<std::string> categoria;
    TabelaHash<std::string> marca;
    TabelaHash<std::string> condicao;
};

struct TabelasCompra {
    TabelaHash<int> timestamp;
    TabelaHash<int> usuario;
};

struct TabelasReposicao {
    TabelaHash<int> timestamp;
};

#endif