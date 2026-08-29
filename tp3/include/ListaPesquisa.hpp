#ifndef LISTAPESQUISA_HPP
#define LISTAPESQUISA_HPP

#include "ListaArray.hpp"

template<typename T>
class ListaPesquisa {

private:

    struct Elemento {
        T chave;
        int valor; 
        Elemento() {}

        Elemento(T c, int v) {
            chave = c;
            valor = v;
        }
    };

    ListaArray<Elemento> lista;

public:

    void inserir(T chave, int valor) {

        Elemento novo(chave, valor);

        int pos = 0;

        while (pos < lista.tamanho() && lista[pos].chave < chave)
            pos++;

        lista.add(novo);

        for (int i = lista.tamanho() - 1; i > pos; i--)
            lista[i] = lista[i - 1];

        lista[pos] = novo;
    }

    ListaArray<int> pesquisar(T chave) {

        ListaArray<int> resposta;

        int ini = 0;
        int fim = lista.tamanho() - 1;

        while (ini <= fim) {

            int meio = (ini + fim) / 2;

            if (lista[meio].chave == chave) {

                int primeiro = meio;
                while (primeiro > 0 &&
                       lista[primeiro - 1].chave == chave)
                    primeiro--;

                while (primeiro < lista.tamanho() &&
                       lista[primeiro].chave == chave) {

                    resposta.add(lista[primeiro].valor);
                    primeiro++;
                }

                return resposta;
            }

            if (lista[meio].chave < chave)
                ini = meio + 1;
            else
                fim = meio - 1;
        }

        return resposta;
    }

};

#endif