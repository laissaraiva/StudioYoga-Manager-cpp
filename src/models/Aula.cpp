#include "models/Aula.h" // <--- Inclui o header correspondente
#include <iostream>
#include <algorithm> // Para std::find

// --- Construtor ---
// (Inicializa os atributos)
Aula::Aula(int id, const std::string& horario, int idInstrutor, int limiteAlunos)
    : id(id),
      horario(horario),
      idInstrutor(idInstrutor),
      limiteAlunos(limiteAlunos) {
    // O vetor 'idsPraticantesInscritos' já começa vazio
}

// --- Destrutor ---
// (Mesmo vazio, é importante defini-lo)
Aula::~Aula() {}

// --- Getters ---
int Aula::getId() const { return id; }
std::string Aula::getHorario() const { return horario; }
int Aula::getLimiteAlunos() const { return limiteAlunos; }
const std::vector<int>& Aula::getIdsPraticantesInscritos() const {
    return idsPraticantesInscritos;
}
int Aula::getVagasDisponiveis() const {
    return limiteAlunos - idsPraticantesInscritos.size();
}

// --- Lógica de Negócios Comum ---
bool Aula::isLotada() const {
    return idsPraticantesInscritos.size() >= limiteAlunos;
}

bool Aula::isPraticanteInscrito(int idPraticante) const {
    // Procura o ID no vetor
    return std::find(idsPraticantesInscritos.begin(),
                     idsPraticantesInscritos.end(),
                     idPraticante) != idsPraticantesInscritos.end();
}

bool Aula::inscreverPraticante(int idPraticante) {
    if (isLotada()) {
        std::cout << "Falha: Aula (ID " << id << ") esta lotada." << std::endl;
        return false;
    }
    if (isPraticanteInscrito(idPraticante)) {
        std::cout << "Info: Praticante (ID " << idPraticante << ") ja esta inscrito." << std::endl;
        return true; // Já está inscrito, não é uma falha
    }

    idsPraticantesInscritos.push_back(idPraticante);
    std::cout << "Sucesso: Praticante (ID " << idPraticante << ") inscrito na Aula (ID " << id << ")." << std::endl;
    return true;
}

void Aula::cancelarInscricao(int idPraticante) {
    // (Implementação futura - encontrar e remover o ID do vetor)
    std::cout << "Funcionalidade 'Cancelar Inscrição' ainda não implementada." << std::endl;
}

void Aula::exibirDetalhes() const {
    // ----- LINHA CORRIGIDA -----
    std::cout << "  [Aula ID: " << id << "] - " << getTipo() << std::endl;
    std::cout << "  Horario: " << horario << std::endl;
    std::cout << "  Instrutor ID: " << idInstrutor << std::endl;
    std::cout << "  Vagas: " << idsPraticantesInscritos.size() << " / " << limiteAlunos << std::endl;
}