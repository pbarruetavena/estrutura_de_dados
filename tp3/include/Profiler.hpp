#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <chrono>
#include <string>
#include <fstream>
#include <iomanip>

class Profiler {
private:
    std::string grupo;
    std::string valor_n;

    // Acumuladores de Tempo (em milissegundos)
    double t_U = 0, t_P = 0, t_R = 0, t_C = 0;
    double t_LU = 0, t_LP = 0, t_LC = 0, t_LR = 0;

    // Contadores de Quantidade
    int q_U = 0, q_P = 0, q_R = 0, q_C = 0;
    int q_LU = 0, q_LP = 0, q_LC = 0, q_LR = 0;

public:
    Profiler(std::string g, std::string n) : grupo(g), valor_n(n) {}

    void add_U(double ms) { t_U += ms; q_U++; }
    void add_P(double ms) { t_P += ms; q_P++; }
    void add_R(double ms) { t_R += ms; q_R++; }
    void add_C(double ms) { t_C += ms; q_C++; }
    void add_LU(double ms) { t_LU += ms; q_LU++; }
    void add_LP(double ms) { t_LP += ms; q_LP++; }
    void add_LC(double ms) { t_LC += ms; q_LC++; }
    void add_LR(double ms) { t_LR += ms; q_LR++; }

    void imprimir_relatorio() {
        std::string nome_arquivo = "res-operacoes-" + grupo + ".csv";
        std::ofstream outfile(nome_arquivo, std::ios::app);

        if (outfile.is_open()) {
            // Função lambda para calcular a média com segurança (evitar divisão por zero)
            auto media = [](double t, int q) { return q > 0 ? t / q : 0.0; };

            outfile << std::fixed << std::setprecision(6);
            outfile << valor_n << ","
                    << media(t_U, q_U) << "," << media(t_P, q_P) << ","
                    << media(t_R, q_R) << "," << media(t_C, q_C) << ","
                    << media(t_LU, q_LU) << "," << media(t_LP, q_LP) << ","
                    << media(t_LC, q_LC) << "," << media(t_LR, q_LR) << "\n";
            outfile.close();
        }
    }
};

extern Profiler* profiler_global;

// --- CLASSES MEDIDORAS (RAII) ---
#define CRIAR_MEDIDOR(NomeClasse, MetodoAdd) \
class NomeClasse { \
    std::chrono::time_point<std::chrono::high_resolution_clock> start; \
public: \
    NomeClasse() { if (profiler_global) start = std::chrono::high_resolution_clock::now(); } \
    ~NomeClasse() { \
        if (profiler_global) { \
            auto end = std::chrono::high_resolution_clock::now(); \
            profiler_global->MetodoAdd(std::chrono::duration<double, std::milli>(end - start).count()); \
        } \
    } \
}

// Usando macro para gerar as 8 classes limpas sem repetição excessiva de código
CRIAR_MEDIDOR(MedidorU, add_U);
CRIAR_MEDIDOR(MedidorP, add_P);
CRIAR_MEDIDOR(MedidorR, add_R);
CRIAR_MEDIDOR(MedidorC, add_C);
CRIAR_MEDIDOR(MedidorLU, add_LU);
CRIAR_MEDIDOR(MedidorLP, add_LP);
CRIAR_MEDIDOR(MedidorLC, add_LC);
CRIAR_MEDIDOR(MedidorLR, add_LR);

#endif