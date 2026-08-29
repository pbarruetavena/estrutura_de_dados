#include "../include/Grafo.hpp"


Grafo::Grafo() {
    _mode = Modo::LISTA; //modo padrão
    matriz_adj = nullptr;
    _maximo = TAMANHO_MAXIMO_LISTA;
    listaAdj = new Lista<int>[_maximo];
    _q_vertices = 0;
}
Grafo::~Grafo() {}
void Grafo::config(Modo modo, bool direcionado, std::string titulo) {
    _mode = modo; _direcionado = direcionado; _titulo = titulo;
}

void Grafo::_inserir_aresta(int idA, int idB) {
    if(idA < 0 || idA >= _q_vertices) {
        std::cout << "Primeiro Id fora do escopo do grafo" << std::endl;
    }
    if(idB < 0 || idB >= _q_vertices) {
        std::cout << "Segundo Id fora do escopo do grafo" << std::endl;
    }

    if(_mode == Modo::LISTA) {
        for(int i = 0; i < listaAdj[idA].tamanho(); i++) {
            if(listaAdj[idA].get(i) == idB) {
                return;
            }
        }
        listaAdj[idA].add(idB);
    } else {
        matriz_adj[idA][idB] = 1;
    }
}

void Grafo::_remover_aresta(int idA, int idB) {
    if(idA < 0 || idA >= _q_vertices) {
        std::cout << "Primeiro Id fora do escopo do grafo" << std::endl;
    }
    if(idB < 0 || idB >= _q_vertices) {
        std::cout << "Segundo Id fora do escopo do grafo" << std::endl;
    }

    if(_mode == Modo::LISTA) {
        listaAdj[idA].remove(idB);
    } else {
        matriz_adj[idA][idB] = 0;
    }
}

int Grafo::inserir_vertice() {
    
    if(_q_vertices >= _maximo) { // realocação
        if(_mode == Modo::LISTA) {
            _maximo = _maximo * 2;
            Lista<int>* novaLista = new Lista<int>[_maximo];
        
            for(int i = 0; i < _q_vertices; i++) {
                for(int j = 0; j < listaAdj[i].tamanho(); j++) {
                    novaLista[i].add(listaAdj[i].get(j));
                }
            }

            delete[] listaAdj;
            listaAdj = novaLista;
        
        } else {
            _maximo = _maximo * 2;
            //alocação
            int** nova_matriz = new int*[_maximo];
            for(int i = 0; i < _maximo; i++) {
                nova_matriz[i] = new int[_maximo]();
            }

            for(int i = 0; i < _q_vertices; i++) {
                for(int j = 0; j < _q_vertices; j++) {
                    nova_matriz[i][j] = matriz_adj[i][j];
                }
            }

            for(int i = 0; i < _maximo; i++) {
                delete[] matriz_adj[i];
            }
            delete[] matriz_adj;

            matriz_adj = nova_matriz;
        }
    }
        
    int id_vertice = _q_vertices;
    _q_vertices++;
    return id_vertice; 
}

void Grafo::inserir_aresta(int idA, int idB) {
    _inserir_aresta(idA, idB);
    if(!_direcionado) { // usa método privado para reaproveitar lógica
        _inserir_aresta(idB, idA);
    }
}

void Grafo::remover_aresta(int idA, int idB) {
    _remover_aresta(idA, idB);
    if(!_direcionado) {// usa método privado para reaproveitar lógica
        _remover_aresta(idB, idA);
    }
}

bool Grafo::verificar_aresta(int idA, int idB) {
    if(_mode == Modo::LISTA) {
        for(int i = 0; i < listaAdj[idA].tamanho(); i++) {
            if(listaAdj[idA].get(i) == idB) {
                return true;
            }
        }
        return false;
    } else {
        return matriz_adj[idA][idB] == 1;
    }
}

Lista<int> Grafo::get_vizinhos(int id) {
    Lista<int> vizinhos;

    if(_mode == Modo::LISTA) {
        for(int i = 0; i < listaAdj[id].tamanho(); i++) {
            vizinhos.add(listaAdj[id].get(i));
        }
    } else {
        for(int i = 0; i < _q_vertices; i++) {
            if(matriz_adj[id][i] == 1) {
                vizinhos.add(i);
            }
        }
    }

    return vizinhos;
}
Lista<int> Grafo::get_vizinhos_reverso(int id) {
    Lista<int> vizinhos;

    if(_mode == Modo::LISTA) {
        for(int i = 0; i < _q_vertices; i++) {
            for(int j = 0; j < listaAdj[i].tamanho(); j++) {
                if(listaAdj[i].get(j) == id) {
                    vizinhos.add(i);
                    break;
                }
            }
        }
    } else {
        for(int i = 0; i < _q_vertices; i++) {
            if(matriz_adj[i][id] == 1) {
                vizinhos.add(i);
            }
        }
    }

    return vizinhos;
}



void Grafo::migrar_matriz_to_lista() {
    if(_mode == Modo::LISTA) { return; }

    listaAdj = new Lista<int>[_maximo];
    for(int i = 0; i < _q_vertices; i++) {
        for(int j = 0; j < _q_vertices; j++) {
            if(matriz_adj[i][j] == 1) {
                listaAdj[i].add(j);
            }
        }
    }

    for(int i = 0; i < _maximo; i++) {
        delete[] matriz_adj[i];
    }
    delete[] matriz_adj;

    _mode = Modo::LISTA;

}
void Grafo::migrar_lista_to_matriz() {
    if(_mode == Modo::MATRIZ) { return; }

    matriz_adj = new int*[_maximo];
    for(int i = 0; i < _maximo; i++) {
        matriz_adj[i] = new int[_maximo]();
    }

    for(int i = 0; i < _q_vertices; i++) {
        for(int j = 0; j < listaAdj[i].tamanho(); j++) {
            int indice = listaAdj[i].get(j);
            matriz_adj[i][indice] = 1;
        }
    }

    delete[] listaAdj;

    _mode = Modo::MATRIZ;
}

size_t Grafo::memoriaUsadaMatriz() {
    size_t mem = sizeof(*this); // Tamanho base da classe Grafo
    
    if (matriz_adj != nullptr) {
        // Espaço do array de ponteiros (as linhas)
        mem += _maximo * sizeof(int*); 
        
        // Espaço de cada linha (os dados inteiros reais)
        mem += _maximo * _maximo * sizeof(int); 
    }
    return mem;
}

size_t Grafo::memoriaUsadaLista() {
    size_t mem = sizeof(*this); // Tamanho base da classe Grafo
    
    if (listaAdj != nullptr) {
        // Espaço gasto pelo array principal de Vetores Dinâmicos
        mem += _maximo * sizeof(Lista<int>);
        
        // Espaço gasto dentro de cada Vetor Dinâmico
        for (int i = 0; i < _maximo; i++) {
            // Aqui usamos a 'capacidade' do vetor interno, e não o 'tamanho', 
            // pois queremos saber o espaço ALOCADO na memória.
            mem += listaAdj[i].capacidade() * sizeof(int); 
        }
    }
    return mem;
}