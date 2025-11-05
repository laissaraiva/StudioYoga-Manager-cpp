#include "data/DataManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

#include "models/Plano.h"
#include "models/Instrutor.h"
#include "models/Praticante.h"
#include "models/Aula.h"
#include "models/HotYoga.h"
#include "models/YogaPets.h"
#include "models/YogaFlow.h"

namespace {
    Praticante* findPraticanteById(std::vector<Praticante>& praticantes, int id) {
        for (auto& p : praticantes) { if (p.getId() == id) return &p; }
        return nullptr;
    }
    Instrutor* findInstrutorById(std::vector<Instrutor>& instrutores, int id) {
        for (auto& i : instrutores) { if (i.getId() == id) return &i; }
        return nullptr;
    }
}

void DataManager::salvarDados(
    const vector<Plano>& planos,
    const vector<Instrutor>& instrutores,
    const vector<Praticante>& praticantes,
    const vector<Aula*>& aulas)
{
    ofstream arquivo;
    cout << "Salvando dados nos arquivos .dat..." << endl;

    // 1) Planos
    arquivo.open(ARQUIVO_PLANOS, std::ios::trunc);
    if (arquivo.is_open()) {
        for (const auto& plano : planos) {
            arquivo << plano.getId() << "," << plano.getNome() << "," << plano.getPreco() << "\n";
        }
        arquivo.close();
    } else {
        cerr << "ERRO: Nao foi possivel salvar " << ARQUIVO_PLANOS << endl;
    }

    // 2) Instrutores
    arquivo.open(ARQUIVO_INSTRUTORES, std::ios::trunc);
    if (arquivo.is_open()) {
        for (const auto& instrutor : instrutores) {
            arquivo << instrutor.getId() << "," << instrutor.getNome() << ","
                    << instrutor.getEmail() << "," << instrutor.getEspecialidade() << "\n";
        }
        arquivo.close();
    } else {
        cerr << "ERRO: Nao foi possivel salvar " << ARQUIVO_INSTRUTORES << endl;
    }

    // 3) Praticantes
    arquivo.open(ARQUIVO_PRATICANTES, std::ios::trunc);
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
        cerr << "ERRO: Nao foi possivel salvar " << ARQUIVO_PRATICANTES << endl;
    }

    // 4) Aulas (polimórfico)
    arquivo.open(ARQUIVO_AULAS, std::ios::trunc);
    if (arquivo.is_open()) {
        for (const Aula* a : aulas) {
            // Formato: id,tipo,horario,idInstrutor,limiteAlunos[,extra][,idsPraticantes...]
            arquivo << a->getId() << "," << a->getTipo() << ","
                    << a->getHorario() << "," << a->getIdInstrutor() << ","
                    << a->getLimiteAlunos();

            if (auto hot = dynamic_cast<const HotYoga*>(a)) {
                arquivo << "," << hot->getTemperatura();
            } else if (auto pets = dynamic_cast<const YogaPets*>(a)) {
                arquivo << "," << pets->getTipoPet();
            }

            for (int idP : a->getIdsPraticantesInscritos()) {
                arquivo << "," << idP;
            }
            arquivo << "\n";
        }
        arquivo.close();
    } else {
        cerr << "ERRO: Nao foi possivel salvar " << ARQUIVO_AULAS << endl;
    }

    cout << "Dados salvos." << endl;
}

void DataManager::carregarDados(
    std::vector<Plano>& planos,
    std::vector<Instrutor>& instrutores,
    std::vector<Praticante>& praticantes,
    std::vector<Aula*>& aulas,
    int& proximoIdPessoa,
    int& proximoIdAula,
    int& proximoIdPlano)
{
    std::ifstream arquivo;
    std::string linha;

    int maxPlanoId = 0;
    int maxPessoaId = 0; // compartilha para instrutor/praticante
    int maxAulaId  = 0;

    std::cout << "Carregando dados dos arquivos .dat..." << std::endl;

    // 1) Planos
    arquivo.open(ARQUIVO_PLANOS);
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string idStr, nome, precoStr;
            if (!std::getline(ss, idStr, ',')) continue;
            if (!std::getline(ss, nome, ',')) continue;
            if (!std::getline(ss, precoStr, ',')) continue;

            try {
                int id = std::stoi(idStr);
                double preco = std::stod(precoStr);
                planos.emplace_back(id, nome, preco);
                maxPlanoId = std::max(maxPlanoId, id);
            } catch (...) {
                std::cerr << "Erro ao ler plano: " << linha << std::endl;
            }
        }
        arquivo.close();
    }

    // 2) Instrutores
    arquivo.open(ARQUIVO_INSTRUTORES);
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string idStr, nome, email, especialidade;
            if (!std::getline(ss, idStr, ',')) continue;
            if (!std::getline(ss, nome, ',')) continue;
            if (!std::getline(ss, email, ',')) continue;
            if (!std::getline(ss, especialidade, ',')) continue;

            try {
                int id = std::stoi(idStr);
                instrutores.emplace_back(id, nome, email, especialidade);
                maxPessoaId = std::max(maxPessoaId, id);
            } catch (...) {
                std::cerr << "Erro ao ler instrutor: " << linha << std::endl;
            }
        }
        arquivo.close();
    }

    // 3) Praticantes
    arquivo.open(ARQUIVO_PRATICANTES);
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string idStr, nome, email, idPlanoStr;
            if (!std::getline(ss, idStr, ',')) continue;
            if (!std::getline(ss, nome, ',')) continue;
            if (!std::getline(ss, email, ',')) continue;
            if (!std::getline(ss, idPlanoStr, ',')) continue;

            try {
                int id = std::stoi(idStr);
                int idPlano = std::stoi(idPlanoStr);
                praticantes.emplace_back(id, nome, email, idPlano);
                maxPessoaId = std::max(maxPessoaId, id);

                // IDs de aulas (opcionais)
                Praticante* p = findPraticanteById(praticantes, id);
                std::string idAulaStr;
                while (std::getline(ss, idAulaStr, ',')) {
                    try { p->inscreverEmAula(std::stoi(idAulaStr)); } catch (...) {}
                }
            } catch (...) {
                std::cerr << "Erro ao ler praticante: " << linha << std::endl;
            }
        }
        arquivo.close();
    }

    // 4) Aulas
    arquivo.open(ARQUIVO_AULAS);
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string idStr, tipo, horario, idInstrutorStr, limiteStr;
            if (!std::getline(ss, idStr, ',')) continue;
            if (!std::getline(ss, tipo, ',')) continue;
            if (!std::getline(ss, horario, ',')) continue;
            if (!std::getline(ss, idInstrutorStr, ',')) continue;
            if (!std::getline(ss, limiteStr, ',')) continue;

            try {
                int id = std::stoi(idStr);
                int idInstrutor = std::stoi(idInstrutorStr);
                int limite = std::stoi(limiteStr);

                Instrutor* instr = findInstrutorById(instrutores, idInstrutor);
                if (!instr) {
                    std::cerr << "Instrutor " << idInstrutor << " nao encontrado; aula " << id << " ignorada.\n";
                    continue;
                }

                Aula* nova = nullptr;

                if (tipo == "HotYoga") {
                    std::string tempStr;
                    if (!std::getline(ss, tempStr, ',')) tempStr = "40";
                    int temp = 40;
                    try { temp = std::stoi(tempStr); } catch (...) {}
                    nova = new HotYoga(id, horario, idInstrutor, limite, temp);
                } else if (tipo == "YogaPets") {
                    std::string tipoPet;
                    if (!std::getline(ss, tipoPet, ',')) tipoPet = "Pets";
                    nova = new YogaPets(id, horario, idInstrutor, limite, tipoPet);
                } else if (tipo == "YogaFlow") {
                    nova = new YogaFlow(id, horario, idInstrutor, limite);
                } else {
                    std::cerr << "Tipo de aula desconhecido: " << tipo << ". Ignorando id " << id << ".\n";
                    continue;
                }

                // Inscrever participantes remanescentes da linha
                std::string idPraticanteStr;
                while (std::getline(ss, idPraticanteStr, ',')) {
                    try {
                        int idP = std::stoi(idPraticanteStr);
                        nova->inscreverPraticante(idP);
                        if (auto p = findPraticanteById(praticantes, idP)) {
                            p->inscreverEmAula(id);
                        }
                    } catch (...) {}
                }

                aulas.push_back(nova);
                instr->adicionarAula(id);
                maxAulaId = std::max(maxAulaId, id);
            } catch (...) {
                std::cerr << "Erro ao ler aula: " << linha << std::endl;
            }
        }
        arquivo.close();
    }

    // Ajuste dos próximos IDs (se necessário)
    if (maxPlanoId >= proximoIdPlano)  proximoIdPlano  = maxPlanoId + 1;
    if (maxPessoaId >= proximoIdPessoa) proximoIdPessoa = maxPessoaId + 1;
    if (maxAulaId  >= proximoIdAula)   proximoIdAula   = maxAulaId + 1;

    std::cout << "Carregamento concluido." << std::endl;
}