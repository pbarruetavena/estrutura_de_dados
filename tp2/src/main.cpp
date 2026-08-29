#include <iostream>
#include <string>
#include <sstream>

#include "Rede.hpp"

Profiler* profiler_global = nullptr;

int main(int argc, char* argv[]) {
    std::cout << "Iniciando ======================================================" << std::endl;

    std::string nome_experimento = "analise/relatorio_detalhado.txt";
    
    if (argc >= 3) {
        nome_experimento = "analise/" +  std::string(argv[1]) + std::string(argv[2]); 
    }

    profiler_global = new Profiler(nome_experimento);
    Rede rede = Rede();
    std::string in;
    int w;
    while(std::getline(std::cin, in)) {

        if (!in.empty() && in.back() == '\r') {
            in.pop_back();
        }
        std::stringstream ss(in);
        std::string com;

        ss >> com;

        if(com == "A") {
            std::string mode;
            ss >> mode;
            MedidorMigracao medidor(mode);
            
            rede.migrar_modo(mode);


        } else if(com == "T") {
            std::string nome;
            char tipo;
            ss >> nome;
            ss >> tipo;
            rede.criar_tema(nome, tipo);
        } else if(com == "U") {
            std::string nome;
            int idade, id;
            Lista<int> ids_temas;
            ss >> nome;
            ss >> idade;
            while(ss >> id) {
                ids_temas.add(id);
            }
            rede.criar_usuario(nome, idade, ids_temas);
        } else if(com == "S") {
            int id1, id2;
            ss >> id1;
            ss >> id2;
            rede.seguir(id1, id2);
        } else if(com == "R") {
            int id1, id2;
            ss >> id1;
            ss >> id2;
            rede.unfollow(id1, id2);
        } else if(com == "LT") {
            int id;
            ss >> id;
            rede.temas_user(id);
        } else if(com == "LC") {
            int id;
            ss >> id;
            rede.seguidores(id);
        } else if(com == "LS") {
            int id;
            ss >> id;
            rede.seguidos_user(id);
        } else if(com == "LA") {
            int id;
            ss >> id;
            rede.amigos(id);
        } else if(com == "Q") {
            int id1, id2;
            ss >> id1;
            ss >> id2;
            rede.relacionados(id1, id2);
        } else if(com == "G") {
            int id_user, id_tema;
            ss >> id_user;
            ss >> id_tema;
            rede.interesse(id_user, id_tema);
        } else if(com == "F") {
            int id;
            ss >> id;
            rede.popularidade(id);
        } else {
            std::cout << "ALERTA: Comando ignorado: [" << com << "]\n";
            break;
        }
    }
    std::cout << "--- FIM DA LEITURA ---\n";
    rede.registrar_memoria();
    profiler_global->imprimir_relatorio();
    std::cout << "--- FIM DA LEITURA ---\n";
}