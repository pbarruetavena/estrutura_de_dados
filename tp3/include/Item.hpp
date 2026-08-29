
#ifndef ITEM_HPP
#define ITEM_HPP

#include <ostream>

// classe para encapsular os ids_produtos e qtd_produtos juntos
class Item {
    private:
    
        int id;
        int qtd;
    
    public:

        Item();

        void set(int, int);
        int get_id() const;
        int get_qtd() const;
        void add_qtd(int);

        // operadores pra ordenação de ListaArray funcionar
        bool operator<(const Item& i) const;
        bool operator<=(const Item& i) const;
        bool operator==(const Item& i) const;
        bool operator>(const Item& i) const;

};

// para printar a classe item (debug)
std::ostream& operator<<(std::ostream& os, const Item& item);

#endif