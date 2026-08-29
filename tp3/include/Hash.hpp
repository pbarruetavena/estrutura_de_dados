#ifndef HASH_HPP
#define HASH_HPP

#include <string>
#include <cmath>

int hash(int chave, int n);

// hash de strings com algoritmo DJB2
int hash(const std::string& chave, int n);

#endif