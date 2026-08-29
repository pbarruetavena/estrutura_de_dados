#include "../include/Hash.hpp"

int hash(int chave, int n) {
    return chave % n;
}

// algoritmo  DJB2
int hash(const std::string& chave, int n) {
    unsigned int hash = 5381;
    for(int i = 0; i < chave.length(); i++) {
        hash = ((hash << 5) + hash) + chave.at(i);
    }
    return hash % n;
}