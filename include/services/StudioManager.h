#ifndef STUDIOMANAGER_H
#define STUDIOMANAGER_H

#include <vector>
#include <string>
#include <limits>
using namespace std;

#include "models/Pessoa.h"
#include "models/Praticante.h"
#include "models/Instrutor.h"
#include "models/Plano.h"
#include "models/Aula.h"
#include "models/HotYoga.h"
#include "models/YogaPets.h"
#include "models/YogaFlow.h"

/**
 * @brief Classe principal que gerencia a UI (menu) e os dados em memória.
 */
class StudioManager {
private:
    // Armazenamento de Dados (em memória)
    vector<Aula*> aulas;
    vector<Instrutor> instrutores;
    vector<Praticante> praticantes;
    vector<Plano> planos;

    // Contadores de ID
    int proximoIdPessoa;
    int proximoIdAula;
    int proximoIdPlano;

    // Métodos Auxiliares (privados)
    void limparBufferEntrada();
    int selecionarTipoAulaMenu(); 

    // Funções "find" para localizar objetos
    Praticante* findPraticanteById(int id);
    Instrutor* findInstrutorById(int id);
    Aula* findAulaById(int id);
    Plano* findPlanoById(int id);

    // Métodos de Lógica do Menu (privados)
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

    // NOVOS MÉTODOS PARA CRUD COMPLETO
    // (U)pdate
    void atualizarPraticante();
    // (D)elete
    void removerPraticante();
    // FIM DAS ADIÇÕES

    // Exibe sempre o menu principal completo (1 a 12 e 0)
    void imprimirMenuPrincipal() const;

    void gerarRelatorioHTML(); // (Nosso "front" de consulta)

public:
    // Construtor e Destrutor
    StudioManager();
    ~StudioManager(); // Destrutor para limpar os ponteiros de Aula*

    // Ponto de Entrada do Menu
    void run(); 
};

#endif // STUDIOMANAGER_H