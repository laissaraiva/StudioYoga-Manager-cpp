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
 * Esta classe substitui a antiga classe "StudioYoga" do arquivo monolítico.
 */
class StudioManager {
private:
    // --- Armazenamento de Dados (em memória) ---
    // Usamos ponteiros de Aula para permitir Polimorfismo (HotYoga, YogaPets, etc.)
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
    int selecionarTipoAulaMenu(); // <--- Substitui o "enum selecionarTipoAula"

    // Funções "find" para localizar objetos
    Praticante* findPraticanteById(int id);
    Instrutor* findInstrutorById(int id);
    Aula* findAulaById(int id);
    Plano* findPlanoById(int id);

    // --- Métodos de Lógica do Menu (privados) ---
    void cadastrarPraticante();
    void cadastrarInstrutor();
    void cadastrarPlano();
    void cadastrarAula(); // <--- ATUALIZADO para usar Herança
    void matricularPraticanteEmAula();

    void listarPraticantes();
    void listarInstrutores();
    void listarPlanos();
    void listarAulas(); // <--- ATUALIZADO para usar Polimorfismo

public:
    // --- Construtor e Destrutor ---
    StudioManager();
    ~StudioManager(); // Destrutor para limpar os ponteiros de Aula*

    // --- Ponto de Entrada do Menu ---
    void run(); // (Era o "menuPrincipal" no seu código antigo)
};

#endif // STUDIOMANAGER_H