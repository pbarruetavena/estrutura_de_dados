#include "../include/Item.hpp"
#include "Item.hpp"

Item::Item() : id(0), qtd(0) {}

void Item::set(int i, int q) {
    id = i; qtd = q;
}

int Item::get_id() const {
    return id;
}

int Item::get_qtd() const {
    return qtd;
}

void Item::add_qtd(int qtd) {
    this->qtd += qtd;
}

bool Item::operator<(const Item& i) const {
    return this->id < i.id;
}

bool Item::operator<=(const Item& i) const {
    return this->id <= i.id;
}

bool Item::operator==(const Item& i) const {
    return this->id == i.id;
}

bool Item::operator>(const Item& i) const {
    return this->id > i.id;
}

//para debugar
std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << "[id=" << item.get_id() << " qtd=" << item.get_qtd() << "]";
    return os;
}