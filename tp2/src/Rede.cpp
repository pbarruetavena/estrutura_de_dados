#include "../include/Rede.hpp"

Rede::Rede() {
    social.config(Modo::LISTA, true, "social");
    temas.config(Modo::LISTA, false, "tema");
}

void Rede::criar_tema(std::string nome, char tipo) {
    MedidorAtualizacao medidor;
    int id_temas = dicionario.get_quantidade_tema();
    Tema* tema = new Tema(id_temas, nome, tipo);
    dicionario.temas.add(tema);


    int id_interno = temas.inserir_vertice();
    No* no = new No(id_interno, TipoEntidade::TEMA, id_temas);
    dicionario.nos_temas_temas.add(no);
    dicionario.nos_internos_temas.add(no);

    std::cout << "T " << id_temas << std::endl;
}

void Rede::criar_usuario(std::string nome, int idade, Lista<int> ids_temas) {
    MedidorAtualizacao medidor;
    int id_usuario = dicionario.get_quantidade_usuario();
    Usuario* usuario = new Usuario(id_usuario, nome, idade);
    dicionario.usuarios.add(usuario);

    int id_interno_social = social.inserir_vertice();
    No* no_social = new No(id_interno_social, TipoEntidade::USUARIO, id_usuario);
    dicionario.nos_social.add(no_social);
    dicionario.nos_internos_social.add(no_social);

    int id_interno_usuario_tema = temas.inserir_vertice();
    No* no_tema = new No(id_interno_usuario_tema, TipoEntidade::TEMA, id_usuario);
    dicionario.nos_tema_user.add(no_tema);
    dicionario.nos_internos_temas.add(no_tema);

    //Operação reversa de tradução dos ids dos temas no grafo de temas
    for(int i = 0;  i < ids_temas.tamanho(); i++) {
        int id_tema = ids_temas.get(i);
        int id_interno_tema = dicionario.nos_temas_temas.get(id_tema)->get_id_interno();

        temas.inserir_aresta(id_interno_usuario_tema, id_interno_tema);
    }

    std::cout << "U " << id_usuario << std::endl;

}

void Rede::seguir(int id_user1, int id_user2) {
    MedidorAtualizacao medidor;
    int id_interno_user1 = dicionario.user_social_real_to_interno(id_user1);
    int id_interno_user2 = dicionario.user_social_real_to_interno(id_user2);

    std::string nome1 = dicionario.usuarios.get(id_user1)->get_nome();
    std::string nome2 = dicionario.usuarios.get(id_user2)->get_nome();

    social.inserir_aresta(id_interno_user1, id_interno_user2);
    std::cout << "S " << nome1 << " " << nome2 << std::endl;
}

void Rede::unfollow(int id_user1, int id_user2) {
    MedidorAtualizacao medidor;
    int id_interno_user1 = dicionario.user_social_real_to_interno(id_user1);
    int id_interno_user2 = dicionario.user_social_real_to_interno(id_user2);

    std::string nome1 = dicionario.usuarios.get(id_user1)->get_nome();
    std::string nome2 = dicionario.usuarios.get(id_user2)->get_nome();

    social.remover_aresta(id_interno_user1, id_interno_user2);
    std::cout << "R " << nome1 << " " << nome2 << std::endl;
}

void Rede::temas_user(int id_user) {
    MedidorConsulta medidor;
    std::string nome = dicionario.usuarios.get(id_user)->get_nome();
    int id_interno_user = dicionario.user_temas_real_to_interno(id_user);
    Lista<int> id_internos_vizinhos = temas.get_vizinhos(id_interno_user);

    std::cout << "LT " << nome;
    Lista<int> ids_temas_vizinhos;

    // Tradução dos ids internos
    for(int i = 0; i < id_internos_vizinhos.tamanho(); i++) {
        int id_interno_vizinho = id_internos_vizinhos.get(i);
        int id_real_vizinho = dicionario.nos_internos_temas.get(id_interno_vizinho)->get_id_original();

        ids_temas_vizinhos.add(id_real_vizinho);
    }

    ids_temas_vizinhos.ordenar();

    for(int i = 0; i < ids_temas_vizinhos.tamanho(); i++) {
        std::string nome_tema = dicionario.temas.get(ids_temas_vizinhos.get(i))->get_nome();
        std::cout << " " << nome_tema;
    }

    std::cout << std::endl;

}

void Rede::popularidade(int id_tema) {
    MedidorConsulta medidor;
    int id_interno_tema = dicionario.tema_real_to_interno(id_tema);
    std::string nome_tema = dicionario.temas.get(id_tema)->get_nome();

    Lista<int> vizinhos = temas.get_vizinhos(id_interno_tema);
    std::cout << "F " << nome_tema << " " << vizinhos.tamanho() << std::endl;
}

void Rede::interesse(int id_user, int id_tema) {
    MedidorConsulta medidor;
    std::string nome_user = dicionario.usuarios.get(id_user)->get_nome();
    std::string nome_tema = dicionario.temas.get(id_tema)->get_nome();

    int id_interno_user = dicionario.user_temas_real_to_interno(id_user);
    int id_interno_tema = dicionario.tema_real_to_interno(id_tema);

    bool interesse = temas.verificar_aresta(id_interno_user, id_interno_tema);
    int inte = interesse ? 1 : 0;
    std::cout << "G " << nome_user << " " << nome_tema << " " << inte << std::endl;
}

void Rede::seguidos_user(int id_user) {
    MedidorConsulta medidor;
    std::string nome_user = dicionario.usuarios.get(id_user)->get_nome();
    std::cout << "LS " << nome_user;

    int id_interno_user = dicionario.user_social_real_to_interno(id_user);
    Lista<int> id_internos_seguidos = social.get_vizinhos(id_interno_user);
    Lista<int> id_reais_seguidos;

    // Operação reversa: conseguir os ids reais a partir dos internos
    for(int i = 0; i < id_internos_seguidos.tamanho(); i++) {
        int id_real_seguido = dicionario.user_social_interno_to_real(id_internos_seguidos.get(i));
        id_reais_seguidos.add(id_real_seguido);
    }

    id_reais_seguidos.ordenar();

    for(int i = 0; i < id_reais_seguidos.tamanho(); i++) {
        int id_usuario_seguido = id_reais_seguidos.get(i);
        std::string nome_seguido = dicionario.usuarios.get(id_usuario_seguido)->get_nome();
        std::cout << " " << nome_seguido;
    }
    std::cout << std::endl;
}

void Rede::seguidores(int id_user) {
    MedidorConsulta medidor;
    std::string nome_user = dicionario.usuarios.get(id_user)->get_nome();
    std::cout << "LC " << nome_user;

    int id_interno_user = dicionario.user_social_real_to_interno(id_user);
    Lista<int> id_internos_seguidores = social.get_vizinhos_reverso(id_interno_user);
    Lista<int> id_reais_seguidores;


    // Operação reversa: conseguir os ids reais a partir dos internos
    for(int i = 0; i < id_internos_seguidores.tamanho(); i++) {
        int id_real_seguidor = dicionario.user_social_interno_to_real(id_internos_seguidores.get(i));
        id_reais_seguidores.add(id_real_seguidor);
    }

    id_reais_seguidores.ordenar();

    for(int i = 0; i < id_reais_seguidores.tamanho(); i++) {
        int id_usuario_seguidor = id_reais_seguidores.get(i);
        std::string nome_seguidor = dicionario.usuarios.get(id_usuario_seguidor)->get_nome();
        std::cout << " " << nome_seguidor;
    }
    std::cout << std::endl;
}

void Rede::amigos(int id_user) {
    MedidorConsulta medidor;
    std::string nome_user = dicionario.usuarios.get(id_user)->get_nome();
    std::cout << "LA " << nome_user;

    int id_interno_user = dicionario.user_social_real_to_interno(id_user);
    Lista<int> id_internos_seguidos = social.get_vizinhos(id_interno_user);
    Lista<int> id_reais_seguidos;

    // Operação reversa: conseguir os ids reais a partir dos internos
    for(int i = 0; i < id_internos_seguidos.tamanho(); i++) {
        int id_usuario_interno_seguido = id_internos_seguidos.get(i);
        if(social.verificar_aresta(id_usuario_interno_seguido, id_interno_user)) { // Amizado é mútua
            int id_real_seguido = dicionario.user_social_interno_to_real(id_usuario_interno_seguido);
            id_reais_seguidos.add(id_real_seguido);
        }
    }

    id_reais_seguidos.ordenar();

    for(int i = 0; i < id_reais_seguidos.tamanho(); i++) {
        int id_usuario_seguido = id_reais_seguidos.get(i);
        std::string nome_seguido = dicionario.usuarios.get(id_usuario_seguido)->get_nome();
        std::cout << " " << nome_seguido;
    }
    std::cout << std::endl;
}

void Rede::relacionados(int id_user1, int id_user2) {
    MedidorConsulta medidor;
    std::string nome_user1 = dicionario.usuarios.get(id_user1)->get_nome();
    std::string nome_user2 = dicionario.usuarios.get(id_user2)->get_nome();
    int id_interno_user1 = dicionario.user_social_real_to_interno(id_user1);
    int id_interno_user2 = dicionario.user_social_real_to_interno(id_user2);

    int valor;
    bool _1_segue_2 = social.verificar_aresta(id_interno_user1, id_interno_user2);
    bool _2_segue_1 = social.verificar_aresta(id_interno_user2, id_interno_user1);

    if(_2_segue_1) {
        valor = 2;
    } else {
        valor = 0;
    }
    if(_1_segue_2) {
        valor++;
    }

    std::cout << "Q " << nome_user1 << " " << nome_user2 << " " << valor << std::endl;
}

void Rede::migrar_modo(std::string mode) {
    if(mode == "L") {
        temas.migrar_matriz_to_lista();
        social.migrar_matriz_to_lista();
    } else if(mode == "M") {
        temas.migrar_lista_to_matriz();
        social.migrar_lista_to_matriz();
    }
    std::cout << "A " << mode << std::endl;
}

void Rede::registrar_memoria() {
    if (profiler_global != nullptr) {
        
        profiler_global->registrar_memoria_matriz(social.memoriaUsadaMatriz() + temas.memoriaUsadaMatriz());
        profiler_global->registrar_memoria_lista(social.memoriaUsadaLista() + temas.memoriaUsadaLista());
    }
}