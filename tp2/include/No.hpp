#ifndef NO_HPP
#define NO_HPP

enum class TipoEntidade { USUARIO, TEMA };

class No {
    private:
        int _id_grafo;
        TipoEntidade _tipo;
        int _id_original;

    public:
        No();
        No(int id_grafo, TipoEntidade tipo, int id_original);
        // Método para permitir atributos pós construção
        void config(int id_grafo, TipoEntidade tipo, int id_original);

        int get_id_interno(); //id do grafo
        int get_id_original(); // posição na lista de nó
        TipoEntidade get_tipo();

};

#endif