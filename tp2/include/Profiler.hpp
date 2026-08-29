#include <iostream>
#include <chrono>
#include <string>
#include <iomanip>
#include <fstream>

// =====================================================================
// 1. DEFINIÇÃO DA CLASSE PROFILER
// =====================================================================
class Profiler {
private:
    std::string nome_experimento;
    std::chrono::time_point<std::chrono::high_resolution_clock> inicio_teste;

    // Acumuladores de tempo e quantidade
    double tempo_consultas = 0;     
    long long qtd_consultas = 0;
    
    double tempo_atualizacao = 0;   
    long long qtd_atualizacoes = 0;

    double tempo_migracao_matriz = 0;   
    long long qtd_migracoes_matriz = 0;

    double tempo_migracao_lista = 0;   
    long long qtd_migracoes_lista = 0;

    // Memória máxima registrada (em bytes)
    size_t memoria_maxima_matriz = 0;
    size_t memoria_maxima_lista = 0;

public:
    Profiler(std::string nome) : nome_experimento(nome) {
        inicio_teste = std::chrono::high_resolution_clock::now();
    }

    // --- Funções para Acumular os Tempos ---
    void add_consulta(double ms) { tempo_consultas += ms; qtd_consultas++; }
    void add_atualizacao(double ms) { tempo_atualizacao += ms; qtd_atualizacoes++; }
    void add_migracao_matriz(double ms) { tempo_migracao_matriz += ms; qtd_migracoes_matriz++; }
    void add_migracao_lista(double ms) { tempo_migracao_lista += ms; qtd_migracoes_lista++; }

    // --- Funções para Acumular Memória ---
    void registrar_memoria_matriz(size_t bytes) { if (bytes > memoria_maxima_matriz) memoria_maxima_matriz = bytes; }
    void registrar_memoria_lista(size_t bytes) { if (bytes > memoria_maxima_lista) memoria_maxima_lista = bytes; }

    // --- Relatório Final ---
    void imprimir_relatorio() {
        auto fim_teste = std::chrono::high_resolution_clock::now();
        double total_ms = std::chrono::duration<double, std::milli>(fim_teste - inicio_teste).count();

        std::ofstream outfile(nome_experimento, std::ios::app);

        if (outfile.is_open()) {
            outfile << "\n===================================================\n";
            outfile << " RELATORIO EXPERIMENTAL: [" << nome_experimento << "]\n";
            outfile << "===================================================\n";
            
            outfile << std::fixed << std::setprecision(4);
            outfile << "Tempo Total de Execucao : " << total_ms << " ms\n\n";

            outfile << "--- TEMPO DE PROCESSAMENTO ---\n";
            if (qtd_consultas > 0)
                outfile << "Consultas (LT,LC,LS,LA,Q,G,F) : " << qtd_consultas << " ops | Media: " 
                        << (tempo_consultas / qtd_consultas) << " ms/op\n";
            
            if (qtd_atualizacoes > 0)
                outfile << "Atualizacoes (U,T,S,R)        : " << qtd_atualizacoes << " ops | Media: " 
                        << (tempo_atualizacao / qtd_atualizacoes) << " ms/op\n";

            if (qtd_migracoes_matriz > 0)
                outfile << "Migrar para MATRIZ (A M)      : " << qtd_migracoes_matriz << " ops | Media: " 
                        << (tempo_migracao_matriz / qtd_migracoes_matriz) << " ms/op\n";
            if (qtd_migracoes_lista > 0)
                outfile << "Migrar para LISTA (A L)       : " << qtd_migracoes_lista << " ops | Media: " 
                        << (tempo_migracao_lista / qtd_migracoes_lista) << " ms/op\n";

            outfile << "\n--- CONSUMO DE MEMORIA (PICO) ---\n";
            outfile << "Memoria no Modo Lista  : " << memoria_maxima_lista << " bytes\n";
            outfile << "Memoria no Modo Matriz : " << memoria_maxima_matriz << " bytes\n";
            
            outfile << "===================================================\n\n";
            outfile.close();
        } else {
            std::cout << "[Erro] Nao foi possivel salvar o log de analise.\n";
        }
    }
};

// =====================================================================
// 2. DECLARAÇÃO DO PONTEIRO GLOBAL
// =====================================================================
extern Profiler* profiler_global;

// =====================================================================
// 3. CLASSES MEDIDORAS (RAII)
// =====================================================================

class MedidorConsulta {
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
    MedidorConsulta() { if (profiler_global) start = std::chrono::high_resolution_clock::now(); }
    ~MedidorConsulta() {
        if (profiler_global) {
            auto end = std::chrono::high_resolution_clock::now();
            profiler_global->add_consulta(std::chrono::duration<double, std::milli>(end - start).count());
        }
    }
};

class MedidorAtualizacao {
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
    MedidorAtualizacao() { if (profiler_global) start = std::chrono::high_resolution_clock::now(); }
    ~MedidorAtualizacao() {
        if (profiler_global) {
            auto end = std::chrono::high_resolution_clock::now();
            profiler_global->add_atualizacao(std::chrono::duration<double, std::milli>(end - start).count());
        }
    }
};

class MedidorMigracao {
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::string modo_destino; // Guarda para qual modo estamos migrando
public:
    MedidorMigracao(std::string modo) : modo_destino(modo) { 
        if (profiler_global) start = std::chrono::high_resolution_clock::now(); 
    }
    ~MedidorMigracao() {
        if (profiler_global) {
            auto end = std::chrono::high_resolution_clock::now();
            double ms = std::chrono::duration<double, std::milli>(end - start).count();
            
            if (modo_destino == "M") {
                profiler_global->add_migracao_matriz(ms);
            } else if (modo_destino == "L") {
                profiler_global->add_migracao_lista(ms);
            }
        }
    }
};