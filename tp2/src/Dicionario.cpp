#include "../include/Dicionario.hpp"

Dicionario::Dicionario() {}

Dicionario::~Dicionario() {
    for(int i = 0; i < nos_internos_social.tamanho(); i++) {
        No* no = nos_internos_social.get(i);
        delete no;
    }
    for(int i = 0; i < nos_internos_temas.tamanho(); i++) {
        No* no = nos_internos_temas.get(i);
        delete no;
    }

    for(int i = 0; i < usuarios.tamanho(); i++) {
        Usuario* u = usuarios.get(i);
        delete u;
    }
    for(int i = 0; i < temas.tamanho(); i++) {
        Tema* t = temas.get(i);
        delete t;
    }
}

int Dicionario::user_social_interno_to_real(int id_interno) {
    return nos_internos_social.get(id_interno)->get_id_original();
}
int Dicionario::user_social_real_to_interno(int id_real) {
    return nos_social.get(id_real)->get_id_interno();
}
int Dicionario::user_temas_interno_to_real(int id_interno) {
    return nos_internos_temas.get(id_interno)->get_id_original();
}
int Dicionario::user_temas_real_to_interno(int id_real) {
    return nos_tema_user.get(id_real)->get_id_interno();
}

int Dicionario::tema_interno_to_real(int id_interno) {
    return nos_internos_temas.get(id_interno)->get_id_original();
}
int Dicionario::tema_real_to_interno(int id_real) {
    return nos_temas_temas.get(id_real)->get_id_interno();
}

int Dicionario::get_quantidade_tema() {
    return temas.tamanho();
}
int Dicionario::get_quantidade_usuario() {
    return usuarios.tamanho();
}
