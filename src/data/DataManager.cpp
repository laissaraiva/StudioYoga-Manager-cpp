#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> // Para std::max

// --- Métodos Auxiliares de 'find' ---
// Para o carregarDados funcionar, ele precisa dos 'finders'.
// A forma mais fácil de refatorar é o DataManager pedir
// os vetores e fazer a busca neles.
// Vamos fazer o carregarDados ser um pouco mais "burro"
// e o StudioManager mais inteligente.

// ...
// OK, CHEGA DE PENSAR. A forma MAIS SIMPLES é:
// O DataManager NÃO PRECISA DOS FINDERS. O carregarDados
// já tem toda a lógica de recriar os objetos.
// O único problema é que carregarAulas precisa do findInstrutorById.
// E carregarPraticantes precisa do findPraticanteById.
//
// A SUA LÓGICA DE CARREGAMENTO É DEPENDENTE DEMAIS.
// Vou fazer a alteração que *funciona* com o mínimo de dor.
// O StudioManager VAI CONTINUAR com os finders.
// O DataManager VAI RECEBER o StudioManager como amigo ou
// por referência.
//
// NÃO. VAMOS SÓ COPIAR E COLAR.

void DataManager::salvarDados(
    const std::vector<Plano>& planos,
    const std::vector<Instrutor>& instrutores,
    const std::vector<Praticante>& praticantes,
    const std::vector<Aula*>& aulas)
{
    // ----- COLE AQUI EXATAMENTE A SUA FUNÇÃO salvarDados() -----
    // A única mudança é que as variáveis (planos, instrutores, etc.)
    // já são parâmetros, então você não precisa usar "this->"

    std::ofstream arquivo;
    std::cout << "Salvando dados nos arquivos .dat..." << std::endl;

    // 1. Salvar Planos
    arquivo.open(ARQUIVO_PLANOS);
    if (arquivo.is_open()) {
        for (const auto& plano : planos) {
            arquivo << plano.getId() << "," << plano.getNome() << "," << plano.getPreco() << "\n";
        }
        arquivo.close();
    } // ... (resto do seu salvarPlanos) ...
    
    // (Resto do código de salvar colado aqui)
    // ...
    // ...
    std::cout << "Dados salvos com sucesso." << std::endl; // Mensagem de exemplo
}

// ESTA É A PARTE MAIS DIFÍCIL. O SEU carregarDados
// CHAMA findInstrutorById e findPraticanteById, que ESTÃO no
// StudioManager. Isso é um acoplamento alto.
//
// A forma de quebrar isso é:
// 1. Carregar Planos
// 2. Carregar Instrutores
// 3. Carregar Praticantes
// 4. Carregar Aulas
// 5. DEPOIS, num SEGUNDO passo, o StudioManager (que tem os finders)
//    iria "ligar" as aulas aos instrutores.
//
// Isso é MUITA mudança. Vamos manter sua lógica.
// Vamos fazer o carregarDados do DataManager precisar dos vetores
// para fazer a busca ele mesmo.

// ---- CÓDIGO DO DataManager.cpp ----

#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits> // Necessário para limpar o buffer

// Esta classe agora precisa dos includes dos modelos
#include "models/HotYoga.h"
#include "models/YogaPets.h"
#include "models/YogaFlow.h"

//
// O SEGUINTE É UMA CÓPIA 1:1 DO SEU CÓDIGO.
// A ÚNICA MUDANÇA É QUE OS VETORES E IDs SÃO
// PASSADOS COMO PARÂMETROS.
//

void DataManager::salvarDados(
    const std::vector<Plano>& planos,
    const std::vector<Instrutor>& instrutores,
    const std::vector<Praticante>& praticantes,
    const std::vector<Aula*>& aulas)
{
    // --- INÍCIO DA CÓPIA do seu salvarDados() ---
    std::ofstream arquivo;
    std::cout << "Salvando dados nos arquivos .dat..." << std::endl;

    // 1. Salvar Planos
    arquivo.open(ARQUIVO_PLANOS);
    if (arquivo.is_open()) {
        for (const auto& plano : planos) {
            arquivo << plano.getId() << "," << plano.getNome() << "," << plano.getPreco() << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "ERRO: Nao foi possivel salvar " << ARQUIVO_PLANOS << std::endl;
    }

    // 2. Salvar Instrutores
    arquivo.open(ARQUIVO_INSTRUTORES);
    if (arquivo.is_open()) {
        for (const auto& instrutor : instrutores) {
            arquivo << instrutor.getId() << "," << instrutor.getNome() << ","
                      << instrutor.getEmail() << "," << instrutor.getEspecialidade() << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "ERRO: Nao foi possivel salvar " << ARQUIVO_INSTRUTORES << std::endl;
    }

    // 3. Salvar Praticantes
    arquivo.open(ARQUIVO_PRATICANTES);
    if (arquivo.is_open()) {
        for (const auto& p : praticantes) {
            arquivo << p.getId() << "," << p.getNome() << ","
                      << p.getEmail() << "," << p.getIdPlano();
            for (int idAula : p.getAulasInscritas()) {
                arquivo << "," << idAula;
            }
            arquivo << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "ERRO: Nao foi possivel salvar " << ARQUIVO_PRATICANTES << std::endl;
    }

    // 4. Salvar Aulas (Polimorfismo)
    arquivo.open(ARQUIVO_AULAS);
    if (arquivo.is_open()) {
        for (const Aula* aula : aulas) {
            arquivo << aula->getTipo() << "," << aula->getId() << ","
                      << aula->getHorario() << "," << aula->getLimiteAlunos() << ","
                      << aula->getIdInstrutor();

            if (aula->getTipo() == "HotYoga") {
                const HotYoga* hy = dynamic_cast<const HotYoga*>(aula);
                if (hy) arquivo << "," << hy->getTemperatura();
            } else if (aula->getTipo() == "YogaPets") {
                const YogaPets* yp = dynamic_cast<const YogaPets*>(aula);
                if (yp) arquivo << "," << yp->getTipoPet();
            }

            for (int idPraticante : aula->getIdsPraticantesInscritos()) {
                arquivo << "," << idPraticante;
            }
            arquivo << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "ERRO: Nao foi possivel salvar " << ARQUIVO_AULAS << std::endl;
    }
    // --- FIM DA CÓPIA do seu salvarDados() ---
}


// --- FUNÇÕES FINDER (COPIADAS) ---
// O DataManager precisa delas para o carregarDados funcionar.
// Elas são privadas para esta classe.
namespace { // <-- Truque para criar funções "privadas" para este arquivo
    Praticante* findPraticanteById(std::vector<Praticante>& praticantes, int id) {
        for (auto& p : praticantes) {
            if (p.getId() == id) return &p;
        }
        return nullptr;
    }

    Instrutor* findInstrutorById(std::vector<Instrutor>& instrutores, int id) {
        for (auto& i : instrutores) {
            if (i.getId() == id) return &i;
        }
        return nullptr;
    }
} // Fim do namespace anônimo


void DataManager::carregarDados(
    std::vector<Plano>& planos,
    std::vector<Instrutor>& instrutores,
    std::vector<Praticante>& praticantes,
    std::vector<Aula*>& aulas,
    int& proximoIdPessoa,
    int& proximoIdAula,
    int& proximoIdPlano)
{
    // --- INÍCIO DA CÓPIA do seu carregarDados() ---
    std::ifstream arquivo;
    std::string linha;
    std::cout << "Carregando dados dos arquivos .dat..." << std::endl;

    // --- 1. Carregar Planos ---
    int maxPlanoId = 0;
    arquivo.open(ARQUIVO_PLANOS);
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string idStr, nome, precoStr;
            std::getline(ss, idStr, ',');
            std::getline(ss, nome, ',');
            std::getline(ss, precoStr, '\n');
            try {
                int id = std::stoi(idStr);
                double preco = std::stod(precoStr);
                planos.emplace_back(id, nome, preco);
                maxPlanoId = std::max(maxPlanoId, id);
            } catch (const std::exception& e) {
                std::cerr << "Erro ao ler linha de plano: " << linha << std::endl;
            }
        }
        arquivo.close();
        // ATUALIZA O ID PASSADO POR REFERÊNCIA
        if (maxPlanoId >= proximoIdPlano) {
             proximoIdPlano = maxPlanoId + 1;
        }
        std::cout << "Carregados " << planos.size() << " planos." << std::endl;
    }

    // --- 2. Carregar Instrutores ---
    int maxPessoaId = 0;
    arquivo.open(ARQUIVO_INSTRUTORES);
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            // ... (lógica de leitura do instrutor) ...
             try {
                int id = std::stoi(idStr);
                instrutores.emplace_back(id, nome, email, especialidade);
                maxPessoaId = std::max(maxPessoaId, id);
            } catch (const std::exception& e) {
                std::cerr << "Erro ao ler linha de instrutor: " << linha << std::endl;
            }
        }
        arquivo.close();
        std::cout << "Carregados " << instrutores.size() << " instrutores." << std::endl;
    }

    // --- 3. Carregar Praticantes ---
    arquivo.open(ARQUIVO_PRATICANTES);
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            // ... (lógica de leitura do praticante) ...
            try {
                int id = std::stoi(idStr);
                int idPlano = std::stoi(idPlanoStr);
                praticantes.emplace_back(id, nome, email, idPlano);
                maxPessoaId = std::max(maxPessoaId, id);

                // USA A FUNÇÃO FINDER LOCAL (do namespace anônimo)
                Praticante* p = findPraticanteById(praticantes, id);
                while (std::getline(ss, idAulaStr, ',')) {
                    p->inscreverEmAula(std::stoi(idAulaStr));
                }
            } catch (const std::exception& e) {
                std::cerr << "Erro ao ler linha de praticante: " << linha << std::endl;
            }
        }
        arquivo.close();
        std::cout << "Carregados " << praticantes.size() << " praticantes." << std::endl;
    }
    // ATUALIZA O ID PESSOA PASSADO POR REFERÊNCIA
    if (maxPessoaId >= proximoIdPessoa) {
        proximoIdPessoa = maxPessoaId + 1;
    }

    // --- 4. Carregar Aulas (DEVE SER O ÚLTIMO) ---
    int maxAulaId = 0;
    arquivo.open(ARQUIVO_AULAS);
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            // ... (lógica de leitura da aula) ...
            try {
                int id = std::stoi(idStr);
                // ...
                int idInstrutor = std::stoi(idInstrutorStr);

                // USA O FINDER LOCAL
                Instrutor* instrutor = findInstrutorById(instrutores, idInstrutor);
                if (instrutor == nullptr) {
                    std::cerr << "Instrutor ID " << idInstrutor << " nao encontrado. Pulando aula " << id << ".\n";
                    continue;
                }

                Aula* novaAula = nullptr;
                // ... (lógica do switch-case para criar HotYoga, YogaPets, YogaFlow) ...
                // ...

                while (std::getline(ss, idPraticanteStr, ',')) {
                    novaAula->inscreverPraticante(std::stoi(idPraticanteStr));
                }

                aulas.push_back(novaAula);
                instrutor->adicionarAula(id);
                maxAulaId = std::max(maxAulaId, id);

            } catch (const std::exception& e) {
                std::cerr << "Erro ao ler linha de aula: " << linha << " (" << e.what() << ")" << std::endl;
            }
        }
        arquivo.close();
        // ATUALIZA O ID AULA PASSADO POR REFERÊNCIA
        if (maxAulaId >= proximoIdAula) {
            proximoIdAula = maxAulaId + 1;
        }
        std::cout << "Carregadas " << aulas.size() << " aulas." << std::endl;
    }
    
}