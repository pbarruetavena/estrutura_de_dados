#include <iostream>
#include <chrono>
#include <string>
#include <random>
#include <iomanip>
#include <fstream>

// =====================================================================
// 1. DEFINIÇÃO DA CLASSE PROFILER
// =====================================================================
class Profiler {
private:
    std::string nome_experimento;
    std::chrono::time_point<std::chrono::high_resolution_clock> inicio_teste;

    // Acumuladores de tempo (em milissegundos)
    double tempo_consultas = 0;     
    long long qtd_consultas = 0;
    
    double tempo_ordenacao = 0;     
    long long qtd_ordenacoes = 0;
    
    double tempo_atualizacao = 0;   
    long long qtd_atualizacoes = 0;

    // Gerador de números aleatórios rápido para a amostragem
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;

public:
    Profiler(std::string nome) : nome_experimento(nome), dist(0.0, 100.0) {
        // Inicializa o RNG com um seed variável
        rng.seed(std::random_device{}()); 
        inicio_teste = std::chrono::high_resolution_clock::now();
    }

    // --- Funções de Sorteio (Amostragem) ---
    bool deve_medir_ordenacao() { return dist(rng) <= 25.0; }     // 5% de chance
    bool deve_medir_atualizacao() { return dist(rng) <= 25.0; }   // 0.5% de chance

    // --- Funções para Acumular os Tempos ---
    void add_consulta(double ms) { tempo_consultas += ms; qtd_consultas++; }
    void add_ordenacao(double ms) { tempo_ordenacao += ms; qtd_ordenacoes++; }
    void add_atualizacao(double ms) { tempo_atualizacao += ms; qtd_atualizacoes++; }

    // --- Relatório Final ---
    void imprimir_relatorio() {
        auto fim_teste = std::chrono::high_resolution_clock::now();
        double total_ms = std::chrono::duration<double, std::milli>(fim_teste - inicio_teste).count();

        // O 'std::ios::app' garante que o log seja adicionado no final do arquivo (append)
        // em vez de apagar os logs de testes anteriores.
        std::ofstream outfile(nome_experimento, std::ios::app);

        if (outfile.is_open()) {
            outfile << "\n===================================================\n";
            outfile << " RELATORIO DE PERFORMANCE: [" << nome_experimento << "]\n";
            outfile << "===================================================\n";
            
            outfile << std::fixed << std::setprecision(4);
            outfile << "Tempo Total do Teste : " << total_ms << " ms\n\n";

            if (qtd_consultas > 0)
                outfile << "Consultas (100%)     : " << qtd_consultas << " medidas | Media: " 
                        << (tempo_consultas / qtd_consultas) << " ms/op\n";
            
            if (qtd_ordenacoes > 0)
                outfile << "Ordenacoes (~5%)     : " << qtd_ordenacoes << " medidas | Media: " 
                        << (tempo_ordenacao / qtd_ordenacoes) << " ms/op\n";

            if (qtd_atualizacoes > 0)
                outfile << "Atualizacoes (~0.5%) : " << qtd_atualizacoes << " medidas | Media: " 
                        << (tempo_atualizacao / qtd_atualizacoes) << " ms/op\n";
            
            outfile << "===================================================\n";
            
            outfile.close(); // Fecha e salva o arquivo
        } else {
            // Se a pasta não existir ou houver erro de permissão, avisa no terminal
            std::cout << "[Erro do Profiler] Nao foi possivel abrir/criar o arquivo log: " << nome_experimento << "\n";
        }
    }
};

// =====================================================================
// 2. DECLARAÇÃO DO PONTEIRO GLOBAL
// =====================================================================
// Isso avisa ao compilador que existe um Profiler global disponível
extern Profiler* profiler_global;


// =====================================================================
// 3. CLASSES MEDIDORAS (RAII)
// =====================================================================

class MedidorConsulta {
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
    MedidorConsulta() {
        if (profiler_global) {
            start = std::chrono::high_resolution_clock::now();
        }
    }
    ~MedidorConsulta() {
        if (profiler_global) {
            auto end = std::chrono::high_resolution_clock::now();
            profiler_global->add_consulta(std::chrono::duration<double, std::milli>(end - start).count());
        }
    }
};

class MedidorOrdenacao {
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    bool medindo;
public:
    MedidorOrdenacao() {
        // Verifica se o global existe e faz o sorteio (5% chance)
        medindo = profiler_global && profiler_global->deve_medir_ordenacao();
        if (medindo) {
            start = std::chrono::high_resolution_clock::now();
        }
    }
    ~MedidorOrdenacao() {
        if (medindo && profiler_global) {
            auto end = std::chrono::high_resolution_clock::now();
            profiler_global->add_ordenacao(std::chrono::duration<double, std::milli>(end - start).count());
        }
    }
};

class MedidorAtualizacao {
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    bool medindo;
public:
    MedidorAtualizacao() {
        // Verifica se o global existe e faz o sorteio (0.5% chance)
        medindo = profiler_global && profiler_global->deve_medir_atualizacao();
        if (medindo) {
            start = std::chrono::high_resolution_clock::now();
        }
    }
    ~MedidorAtualizacao() {
        if (medindo && profiler_global) {
            auto end = std::chrono::high_resolution_clock::now();
            profiler_global->add_atualizacao(std::chrono::duration<double, std::milli>(end - start).count());
        }
    }
};

