#ifndef LISTA_ENCADEADA_HPP
#define LISTA_ENCADEADA_HPP

// Lista encadeada engessada para estar dentro da tabela, ou seja, ela não precisa de métodos como remover nem busca
#include "No.hpp"
#include "ListaArray.hpp"

template<typename T>
class ListaEncadeada {
    private:
    
        int tamanho;
        No<T>* inicio;
        No<T>* fim;

    public:

        ListaEncadeada() {
            tamanho = 0;
            inicio = nullptr;
            fim = nullptr;
        }

        ~ListaEncadeada() {
            No<T>* aux = inicio;
            while(aux != nullptr) {
                No<T>* var = aux;
                if (RASTREAR_MEMORIA) {
                    // Imprime o ponteiro diretamente (ele já é um endereço hexadecimal)
                    trace_file << " L " << aux << "\n"; 
                }
                aux = aux->get_prox();
                delete var;
            }
        }

        void add(T chave, int id) {
            No<T>* novo = new No<T>(chave, id);
            No<T>* aux = fim;

            if(tamanho <= 0) {
                inicio = novo;
            }

            if(aux!=nullptr) {
                aux->set_prox(novo);
            }
            fim = novo;
            tamanho++;
        }

        int get_tamanho() {
            return tamanho;
        }

        // método para retornar os ids dos elementos
        ListaArray<int> get_all(T chave) {
            // std::cout << "tamanho da lista: " << tamanho << std::endl;
            ListaArray<int> lista;
            No<T>* aux = inicio;
            while(aux != nullptr) {
                // std::cout << " " << aux->get_chave() << ", " << aux->get_valor() << " | ";
                if(aux->get_chave() == chave) {
                    lista.add(aux->get_valor());
                }
                if (RASTREAR_MEMORIA) {
                    // Imprime o ponteiro diretamente (ele já é um endereço hexadecimal)
                    trace_file << " L " << aux << "\n"; 
                }
                aux = aux->get_prox();
                
            }
            // std::cout << std::endl;
            return lista;
        }

};

#endif