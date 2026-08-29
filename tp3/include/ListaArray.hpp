#ifndef LISTA_ARRAY_H
#define LISTA_ARRAY_H

#include <iostream>
#include <string>
#include <sstream>


#include <fstream>
constexpr int TAMANHO_MAXIMO_LISTA = 1000;
extern std::ofstream trace_file;
extern bool RASTREAR_MEMORIA;

template <typename T>
class ListaArray {
    private:
        T* lista;
        int maximo;
        int q_elementos;

        int particao(int l, int r) {
            int meio = l + (r-l)/2;
            if(lista[l] > lista[meio]) {
                T aux = lista[l]; 
                lista[l] = lista[meio];
                lista[meio] = aux;
            }
            if (lista[l] > lista[r]) {
                T aux = lista[l];
                lista[l] = lista[r];
                lista[r] = aux;
            }
            if (lista[meio] > lista[r]) {
                T aux = lista[meio];
                lista[meio] = lista[r];
                lista[r] = aux;
            }
            T aux_mediana = lista[meio];
            lista[meio] = lista[r];
            lista[r] = aux_mediana;

            T pivo = lista[r];
            int i = l - 1;

            for(int j = l; j <= r - 1; j++) {
                if(lista[j] <= pivo) {
                    i++;
                    T aux = lista[i];
                    lista[i] = lista[j];
                    lista[j] = aux;
                }
            }

            T aux = lista[i+1];
            lista[i+1] = lista[r];
            lista[r] = aux;
            return i+1;
        }
        void quick(int l, int r) {
            if(l < r) {
                int p = particao(l, r);

                quick(l, p-1);
                quick(p+1, r);
            }
        }

    public:

        ListaArray() {
            maximo = TAMANHO_MAXIMO_LISTA;
            q_elementos = 0;
            lista = new T[maximo];
        }
        
        ListaArray(const ListaArray& outro) {
            q_elementos = outro.q_elementos;
            maximo = outro.maximo;

            lista = new T[maximo];
            for (int i = 0; i < q_elementos; i++) {
                lista[i] = outro.lista[i];
            }
        }

        ListaArray& operator=(const ListaArray& outro) {
            if (this == &outro) {return *this;}

            delete[] this->lista;

            q_elementos = outro.q_elementos;
            maximo = outro.maximo;

            lista = new T[maximo];
            for (int i = 0; i < q_elementos; i++) {
                lista[i] = outro.lista[i];
            }

            return *this;
        }

        ~ListaArray() {
            delete[] lista;
        }

        void add(T e) {
            if (q_elementos >= maximo) {
                maximo = maximo * 2;
                T* novo = new T[maximo];
                for(int i = 0; i < q_elementos; i++) {
                    novo[i] = lista[i];
                }
                delete[] lista;
                lista = novo;
            }
            lista[q_elementos++] = e;
        }

        void remove(T e) {
            int j = -1;
            for(int i = 0; i < q_elementos; i++) {
                if(lista[i] == e) {
                    j = i;
                    break;
                }
            }

            if(j == -1) { return; }
            for(int i = j; i < q_elementos-1; i++) {
                lista[i] = lista[i+1];
            }
            q_elementos--;
        }

        T get(int i) {
            return lista[i];
        }

        T& operator[](int i) {
            if (i < 0 || i >= q_elementos) {
                // std::cout << "Index da lista negativo ou fora de escopo" << std::endl;
            }
            if (RASTREAR_MEMORIA) {
                // Imprime no mesmo formato que o Python já espera ler!
                trace_file << " L " << &lista[i] << "\n"; 
            }
            return lista[i];
        }
        
        int tamanho() {
            return q_elementos;
        }

        int capacidade() {
            return maximo;
        }

        void ordenar() {
            if (q_elementos > 1) {
                quick(0, q_elementos - 1);
            }
        }

        // função pra juntar elementos de ambas as litas: algoritmo dos dois ponteiros
        void merge(ListaArray<int> l1, ListaArray<int> l2) {
            int i = 0; int j = 0;

            while(i < l1.tamanho() && j < l2.tamanho()) {
                if(l1[i] == l2[j]) {
                    this->add(l2[j]);
                    i++; j++;
                } else if(l1[i] < l2[j]) {
                    i++;
                } else {
                    j++;
                }
            }
        }

        void print() {
            std::cout << "[";
            for(int i = 0; i < q_elementos; i++) {
                std::cout << " " << lista[i];
            }
            std::cout << " ]" << std::endl;
        }
};

#endif