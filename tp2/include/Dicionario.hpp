#ifndef DICIONARIO_HPP
#define DICIONARIO_HPP

#include "Lista.hpp"
#include "Usuario.hpp"
#include "Tema.hpp"
#include "No.hpp"

#include <iostream>


class Dicionario {
    public:
        Lista<Usuario*> usuarios;
        Lista<Tema*> temas;

        // Lista de nós do grafo social indexados pelos IDs dos usuários reais
        Lista<No*> nos_social;
        // Lista de nós do grafo de tema (usuários) indexados pelos IDs reais dos usuários
        Lista<No*> nos_tema_user;
        // Lista de nós do grafo de tema (temas) indexados pelos IDs reais dos temas
        Lista<No*> nos_temas_temas;

        // Lista de nós do grafo social indexados pelos IDs internos do grafo social (usuários)
        Lista<No*> nos_internos_social;
        // Lista de nós do grafo de temas indexados pelos IDs internos do grafo de temas (usuários e temas)
        Lista<No*> nos_internos_temas;

        Dicionario();
        ~Dicionario();

        // conversão do ID interno para o real do usuário no grafo social
        int user_social_interno_to_real(int id_interno);
        //conversão do ID real para o interno do usuário no grafo social
        int user_social_real_to_interno(int id_real);
        //conversão do ID interno para o real do usuário no grafo de temas
        int user_temas_interno_to_real(int id_interno);
        //conversão do ID real para o interno do usuário no grafo social
        int user_temas_real_to_interno(int id_real);

        //conversão do ID interno para o real do tema no grafo de temas
        int tema_interno_to_real(int id_interno);
        //conversão do ID real para o interno do tema no grafo de temas
        int tema_real_to_interno(int id_real);

        int get_quantidade_tema();
        int get_quantidade_usuario();

        // void imprimirDicionarioDebug();
};

#endif