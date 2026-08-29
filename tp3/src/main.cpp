
#include "Mercado.hpp"

Profiler* profiler_global = nullptr;

std::ofstream trace_file("trace_mem.txt");
bool RASTREAR_MEMORIA = true;

int main(int argc, char* argv[]) {

    if (argc >= 3) {
        std::string grupo = argv[1];
        std::string valor_n = argv[2];
        profiler_global = new Profiler(grupo, valor_n);
    }

    Mercado mc;
    bool primeiraLinha = true;
    std::string in;
    int w;
    while(std::getline(std::cin, in)) {

        if (!in.empty() && in.back() == '\r') {
            in.pop_back();
        }
        std::stringstream ss(in);
        std::string com;

        ss >> com;

        // if (!primeiraLinha) {
        //     std::cout << std::endl; 
        // }
        // primeiraLinha = false;

        if(com == "U") {
            MedidorU m;
            int idade;
            std::string nome, cidade, estado, nacionalidade;
            ss >> nome >> idade >> cidade >> estado >> nacionalidade;
            mc.cadastrar_usuario(nome, idade, cidade, estado, nacionalidade);
        } else if(com == "P") {
            MedidorP m;
            int qtd;
            double preco;
            std::string nome, categoria, marca, condicao;
            ss >> nome >> preco >> qtd >> categoria >> marca >> condicao;
            mc.cadastrar_produto(nome, preco, qtd, categoria, marca, condicao);
        } else if(com == "R") {
            MedidorR m;
            int timestamp, prod, qtd;
            ListaArray<int> produtos;
            ListaArray<int> qtd_comprada;
            ss >> timestamp;
            while(ss >> prod) {
                produtos.add(prod);
                ss >> qtd;
                qtd_comprada.add(qtd);
            }
            mc.reposicao(timestamp, produtos, qtd_comprada);
        } else if(com == "C") {
            MedidorC m;
            int timestamp, id_usuario, prod, qtd;
            ListaArray<int> produtos;
            ListaArray<int> qtd_comprada;
            ss >> timestamp >> id_usuario;
            while(ss >> prod) {
                produtos.add(prod);
                ss >> qtd;
                qtd_comprada.add(qtd);
            }
            mc.compra(timestamp, id_usuario, produtos, qtd_comprada);
        } else if(com == "LU") {
            MedidorLU m;
            std::string atr;
            ListaArray<Consulta> pesquisa;
            while(ss >> atr) {
                Consulta co;
                co.atributo = atr;
                if(atr == "idade" || atr == "id") {
                    ss >> co.valor_int;
                } else {
                    ss >> co.valor_string;
                }
                pesquisa.add(co);
            }
            mc.consultar_usuario(pesquisa);
        } else if(com == "LP") {
            MedidorLP m;
            std::string atr;
            ListaArray<Consulta> pesquisa;
            while(ss >> atr) {
                Consulta co;
                co.atributo = atr;
                if(atr == "id") {
                    ss >> co.valor_int;
                } else {
                    ss >> co.valor_string;
                }
                pesquisa.add(co);
            }
            mc.consultar_produto(pesquisa);
        } else if(com == "LC") {
            MedidorLC m;
            std::string atr;
            ListaArray<Consulta> pesquisa;
            while(ss >> atr) {
                Consulta co;
                co.atributo = atr;
                ss >> co.valor_int;
                pesquisa.add(co);
            }
            mc.consultar_compra(pesquisa);
        } else if(com == "LR") {
            MedidorLR m;
            std::string atr;
            ListaArray<Consulta> pesquisa;
            while(ss >> atr) {
                Consulta co;
                co.atributo = atr;
                ss >> co.valor_int;
                pesquisa.add(co);
            }
            mc.consultar_reposicao(pesquisa);
        } 
        std::cout << std::endl;
    }

    if (profiler_global != nullptr) {
        profiler_global->imprimir_relatorio(); 
        delete profiler_global;
    }
    
    return 0;
}