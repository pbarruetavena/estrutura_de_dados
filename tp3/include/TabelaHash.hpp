#ifndef TABELA_HASH_HPP
#define TABELA_HASH_HPP

#include "ListaEncadeada.hpp"
#include "ListaArray.hpp"
#include "Hash.hpp"

constexpr int TAMANHO_MAXIMO_TABELA = 10000;

// Apesar de ser uma tabela hash genérica na chave, ela é uma tabela usada engessada para que os valores sejam sempre ids inteiros
template <typename T>
class TabelaHash {
    private:
        int tamanho;
        int capacidade;
        ListaEncadeada<T>* listas;

    public:

        TabelaHash() {
            tamanho = 0;
            capacidade = TAMANHO_MAXIMO_TABELA;
            listas = new ListaEncadeada<T>[capacidade];  
        }

        void inserir(T chave, int valor) {
            int indice = hash(chave, capacidade);
            // std::cout << "chave=" << chave << " valor=" << valor << " indice=" << indice << " capacidade=" << capacidade << std::endl;
            if(indice < 0 || indice >= capacidade) {
                std::cout << "Erro hash fora do escopo da tabela" << std::endl;
                return;
            }
            listas[indice].add(chave, valor);
            // std::cout << "elemento adicionado no indice " << indice << std::endl;
            tamanho++;
        }
        
        ListaArray<int> pesquisar(T chave) {
            int indice = hash(chave, capacidade);
            if(indice < 0 || indice >= capacidade) {
                std::cout << "Erro hash fora do escopo da tabela" << std::endl;
                return ListaArray<int>();
            }
            // std::cout << "Elemento buscado no indice " << indice << std::endl;
            return listas[indice].get_all(chave);
        }

};


#endif