#ifndef REDE_HPP
#define REDE_HPP

#include "Dicionario.hpp"
#include "Grafo.hpp"
#include <iostream>
#include "Profiler.hpp"

class Rede {
    private:
        Dicionario dicionario;
        Grafo social;
        Grafo temas;

    public:
        Rede();
        //~Rede();

        //entradas
        void criar_tema(std::string nome, char tipo);
        void criar_usuario(std::string nome, int idade, Lista<int> ids_temas);
        void seguir(int id1, int id2);
        void unfollow(int id1, int id2);

        //consultas
        void temas_user(int id_user);
        void seguidores(int id_user);
        void seguidos_user(int id_user);
        void amigos(int id_user);
        void relacionados(int id_user1, int id_user2);
        void interesse(int id_user, int id_tema);
        void popularidade(int id_tema);

        void migrar_modo(std::string mode);

        // void debug_print();

        void registrar_memoria();
};  

#endif