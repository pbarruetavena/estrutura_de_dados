#ifndef LISTA_H
#define LISTA_H

#include <string>
#include <iostream>
constexpr int TAMANHO_MAXIMO_LISTA = 1000;

template <typename T>
class Lista {
    private:
        T* _lista;
        int _maximo;
        int _tamanho;

        int particao(int l, int r) {
            T pivo = _lista[r];
            int i = l - 1;

            for(int j = l; j <= r - 1; j++) {
                if(_lista[j] <= pivo) {
                    i++;
                    T aux = _lista[i];
                    _lista[i] = _lista[j];
                    _lista[j] = aux;
                }
            }

            T aux = _lista[i+1];
            _lista[i+1] = _lista[r];
            _lista[r] = aux;
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

        Lista() {
            _maximo = TAMANHO_MAXIMO_LISTA;
            _tamanho = 0;
            _lista = new T[_maximo];
        }
        
        Lista(const Lista& outro) {
            _tamanho = outro._tamanho;
            _maximo = outro._maximo;

            _lista = new T[_maximo];
            for (int i = 0; i < _tamanho; i++) {
                _lista[i] = outro._lista[i];
            }
        }

        ~Lista() {
            delete[] _lista;
        }

        void add(T e) {
            if (_tamanho >= _maximo) {
                _maximo = _maximo * 2;
                T* novo = new T[_maximo];
                for(int i = 0; i < _tamanho; i++) {
                    novo[i] = _lista[i];
                }
                delete[] _lista;
                _lista = novo;
            }
            _lista[_tamanho++] = e;
        }

        void remove(T e) {
            int j = -1;
            for(int i = 0; i < _tamanho; i++) {
                if(_lista[i] == e) {
                    j = i;
                    break;
                }
            }

            if(j == -1) { return; }
            for(int i = j; i < _tamanho-1; i++) {
                _lista[i] = _lista[i+1];
            }
            _tamanho--;
        }

        T get(int i) {
            // if(i < 0 || i >= _tamanho) {
            //     return nullptr;
            // }
            return _lista[i];
        }
        
        int tamanho() {
            return _tamanho;
        }

        int capacidade() {
            return _maximo;
        }

        void ordenar() {
            if (_tamanho > 1) {
                quick(0, _tamanho - 1);
            }
        }

        void print() {
            std::cout << "[";
            for(int i = 0; i < _tamanho; i++) {
                std::cout << " " << _lista[i];
            }
            std::cout << " ]" << std::endl;
        }
};

#endif