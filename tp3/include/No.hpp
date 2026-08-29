#ifndef NO_HPP
#define NO_HPP

#include "Hash.hpp"

template<typename T>
class No {
    private:
        
        T chave;
        int valor;
        No<T>* prox;

    public:

        No() {}

        No(T c, int v) : chave(c), valor(v) {
            prox = nullptr;
        }
        void set(T c, int v) {
            chave = c;
            valor = v;
        }
        void set_prox(No<T>* p) {
            prox = p;
        }

        T get_chave() {
            return chave;
        }
        int get_valor() {
            return valor;
        }
        No<T>* get_prox() {
            return prox;
        }
};

#endif