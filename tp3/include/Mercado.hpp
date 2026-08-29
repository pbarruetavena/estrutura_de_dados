#ifndef MERCADO_HPP
#define MERCADO_HPP

#include "Tabelas.hpp"
#include "Consulta.hpp"
#include "ListaArray.hpp"

#include "Usuario.hpp"
#include "Produto.hpp"
#include "Compra.hpp"
#include "Reposicao.hpp"

#include "Profiler.hpp"

#include <iomanip>

class Mercado {
    private:
        // conjunto de tabelas por entidade (cada uma tabela tem uma tabela hash por atributo buscável)
        TabelasUsuario hash_usuario;
        TabelasProduto hash_produto;
        TabelasCompra hash_compra;
        TabelasReposicao hash_reposicao;
        
        // Entidades concretas
        ListaArray<Usuario> usuarios;
        ListaArray<Produto> produtos;
        ListaArray<Compra> compras;
        ListaArray<Reposicao> reposicoes;

    public:

        Mercado();

        void cadastrar_usuario(std::string nome, int idade, std::string cidade, std::string estado, std::string nacionalidade);
        void cadastrar_produto(std::string nome, double preco, int qtd, std::string categoria, std::string marca, std::string condicao);
        void reposicao(int timestamp, ListaArray<int> produtos, ListaArray<int> quantidas);
        void compra(int timestamp, int id_usuario, ListaArray<int> produtos, ListaArray<int> quantidas);

        void consultar_usuario(ListaArray<Consulta> consulta);
        void consultar_produto(ListaArray<Consulta> consulta);
        void consultar_compra(ListaArray<Consulta> consulta);
        void consultar_reposicao(ListaArray<Consulta> consulta);

        // apenas para debuug
        void print_estado();
};

#endif