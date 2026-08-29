#ifndef GRAFO_HPP
#define GRAFO_HPP

#include "Lista.hpp"
#include <iostream>

enum class Modo { LISTA, MATRIZ };

class Grafo {
    private:
        
        Modo _mode;
        bool _direcionado;
        int _q_vertices;
        int _maximo;
        std::string _titulo;

        int** matriz_adj;
        Lista<int>* listaAdj;

        /* Inserção de aresta privada (sem saber se é direcionado ou não)
        */
        void _inserir_aresta(int idA, int idB);
        /* Remoção de aresta privada (sem saber se é direcionado ou não)
        */
        void _remover_aresta(int idA, int idB);

    public:
        Grafo();
        ~Grafo();
        void config(Modo modo, bool direcionaro, std::string titulo);    

        int inserir_vertice();
        void inserir_aresta(int idA, int idB);
        void remover_aresta(int idA, int idB);
        bool verificar_aresta(int idA, int idB);

        void migrar_matriz_to_lista();
        void migrar_lista_to_matriz();

        /* Retorna a lista de vértices que são apontados pelo vértice de parâmetro
         */
        Lista<int> get_vizinhos(int id); 
        /* Retorna a lista de vértices que apontam o vértice de parâmetro
         */
        Lista<int> get_vizinhos_reverso(int id);

        // void imprimirGrafoDebug();

        size_t memoriaUsadaMatriz();
        size_t memoriaUsadaLista();
};

#endif