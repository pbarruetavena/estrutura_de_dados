#ifndef FILTRO_HPP
#define FILTRO_HPP

#include <string>

// filtro encapsulado pra passar string e int
struct Consulta  {
    std::string atributo;
    // bool eInt;
    std::string valor_string;
    int valor_int;
};

#endif