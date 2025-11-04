#ifndef STUDIOMANAGER_H
#define STUDIOMANAGER_H

#include <vector>
#include <string>
#include <limits>
#include "models/Pessoa.h"
#include "models/Praticante.h"
#include "models/Instrutor.h"
#include "models/Plano.h"
#include "models/Aula.h" // A Classe Mãe Abstrata

/**
 * @brief Classe principal que gerencia a UI (menu) e os dados em memória.
 */
class StudioManager {
private:
    // --- Armazenamento de Dados (em memória) ---
    std::vector<Aula*> aulas;
    std::vector<Instrutor> instrutores;
    std::vector<Praticante> praticantes;
    std::vector<Plano> planos;

    // --- Contadores de ID ---
    int proximoIdPessoa;
    int proximoIdAula;
    int proximoIdPlano;

    // --- Métodos Auxiliares (privados) ---
    void limparBufferEntrada();
    int selecionarTipoAulaMenu(); 

    // Funções "find" para localizar objetos
    Praticante* findPraticanteById(int id);
    Instrutor* findInstrutorById(int id);
    Aula* findAulaById(int id);
    Plano* findPlanoById(int id);

    // --- Métodos de Lógica do Menu (privados) ---
    // (C)reate
    void cadastrarPraticante();
    void cadastrarInstrutor();
    void cadastrarPlano();
    void cadastrarAula(); 
    void matricularPraticanteEmAula();

    // (R)ead
    void listarPraticantes();
    void listarInstrutores();
    void listarPlanos();
    void listarAulas(); 
    void gerarRelatorioHTML(); // (Nosso "front" de consulta)

    // --- NOVOS MÉTODOS PARA CRUD COMPLETO ---
    // (U)pdate
    void atualizarPraticante();
    // (D)elete
    void removerPraticante();
    // --- FIM DAS ADIÇÕES ---

public:
    // --- Construtor e Destrutor ---
    StudioManager();
    ~StudioManager(); // Destrutor para limpar os ponteiros de Aula*

    // --- Ponto de Entrada do Menu ---
    void run(); 
};

#endif // STUDIOMANAGER_H