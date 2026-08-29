#include <iostream>
#include <string>
#include <sstream>
#include "../include/Mercado.hpp"


Profiler* profiler_global = nullptr;

int main(int argc, char* argv[]) {

    std::string nome_experimento = "analise/relatorio_detalhado.txt";
    
    if (argc >= 3) {
        nome_experimento = "analise/" +  std::string(argv[1]) + std::string(argv[2]); 
    }

    profiler_global = new Profiler(nome_experimento);
    Mercado mercado = Mercado();
    std::string in;
    int w;
    while(std::getline(std::cin, in)) {
        if (in.length() < 1){ continue; }
        std::stringstream ss(in);
        std::string com;

        ss >> com;

        if(com == "M") {
            ss >> w;
            mercado.set_w(w);
            std::string param;
            while(ss >> param) {
                mercado.adicionar_metrica(param);
            }
        } else if(com == "A") {
            int id;
            ss >> id;
            mercado.adicionar_acao(id);
        } else if(com == "U") {
            int id;
            ss >> id;
            mercado.adicionar_cliente(id);
        } else if(com == "P") {
            int id;
            double preco;
            ss >> id;
            ss >> preco;
            mercado.adicionar_cotacao(id, preco);
        } else if(com == "B") {
            int id_cliente, id_acao;
            ss >> id_cliente;
            ss >> id_acao;
            mercado.fazer_compra(id_cliente, id_acao);
        } else if(com == "V") {
            int id_cliente, id_acao;
            ss >> id_cliente;
            ss >> id_acao;
            mercado.fazer_venda(id_cliente, id_acao);
        } else if(com == "Q") {
            int id_consulta, id_cliente, n, m;
            ss >> id_consulta;
            ss >> id_cliente;
            ss >> n;
            ss >> m;

            std::string* metricas = new std::string[m];
            double* pesos = new double[m];

            for(int i = 0; i < m; i++) {
                ss >> metricas[i];
                ss >> pesos[i];
            }

            mercado.consulta(id_consulta, id_cliente, n, m, metricas, pesos);
            delete[] metricas;
            delete[] pesos;

        } else {
            break;
        }
    }
    profiler_global->imprimir_relatorio();
}