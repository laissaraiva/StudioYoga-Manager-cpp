#include "models/Aula.h" // Inclui o cabeçalho correspondente
#include <iostream>      // Necessário para std::cout
#include <algorithm>     // Necessário para std::find

// Construtor da classe base Aula.
// Inicializa os atributos principais da aula.
Aula::Aula(int id, const std::string& horario, int idInstrutor, int limiteAlunos)
    : id(id),
      horario(horario),
      idInstrutor(idInstrutor),
      limiteAlunos(limiteAlunos) {
    // O vetor 'idsPraticantesInscritos' é inicializado vazio automaticamente.
}

// Destrutor virtual da classe Aula.
// Garante que os destrutores das classes filhas sejam chamados.
Aula::~Aula() {}

// Retorna o ID da aula.
int Aula::getId() const { return id; }

// Retorna o horário da aula.
std::string Aula::getHorario() const { return horario; }

// Retorna o limite máximo de alunos.
int Aula::getLimiteAlunos() const { return limiteAlunos; }

// Retorna uma referência constante ao vetor de IDs dos praticantes inscritos.
const std::vector<int>& Aula::getIdsPraticantesInscritos() const {
    return idsPraticantesInscritos;
}

// Calcula e retorna o número de vagas ainda disponíveis.
int Aula::getVagasDisponiveis() const {
    return limiteAlunos - idsPraticantesInscritos.size();
}

// Verifica se a aula atingiu sua capacidade máxima.
bool Aula::isLotada() const {
    return idsPraticantesInscritos.size() >= limiteAlunos;
}

// Verifica se um praticante específico (pelo ID) já está inscrito nesta aula.
bool Aula::isPraticanteInscrito(int idPraticante) const {
    // Procura o ID no vetor de inscritos.
    return std::find(idsPraticantesInscritos.begin(),
                     idsPraticantesInscritos.end(),
                     idPraticante) != idsPraticantesInscritos.end();
}

// Tenta inscrever um praticante na aula.
bool Aula::inscreverPraticante(int idPraticante) {
    // Não permite inscrição se a aula estiver lotada.
    if (isLotada()) {
        std::cout << "Falha: Aula (ID " << id << ") está lotada." << std::endl;
        return false;
    }
    // Verifica se o praticante já está inscrito para evitar duplicatas.
    if (isPraticanteInscrito(idPraticante)) {
        std::cout << "Info: Praticante (ID " << idPraticante << ") já está inscrito." << std::endl;
        return true; // Considera sucesso, pois o objetivo (estar inscrito) foi atingido.
    }

    // Adiciona o ID do praticante ao vetor.
    idsPraticantesInscritos.push_back(idPraticante);
    std::cout << "Sucesso: Praticante (ID " << idPraticante << ") inscrito na Aula (ID " << id << ")." << Vstd::endl;
    return true;
}

// Remove um praticante da aula (não implementado).
void Aula::cancelarInscricao(int idPraticante) {
    // (Implementação futura - encontrar e remover o ID do vetor)
    std::cout << "Funcionalidade 'Cancelar Inscrição' ainda não implementada." << std::endl;
}

// Exibe os detalhes básicos e comuns a todas as aulas.
void Aula::exibirDetalhes() const {
    // Chama o método virtual 'getTipoDeAula()' que será implementado pelas classes filhas.
    std::cout << "  [Aula ID: " << id << "] - " << getTipoDeAula() << std::endl;
    std::cout << "  Horário: " << horario << std::endl;
    std::cout << "  Instrutor ID: " << idInstrutor << std::endl;
    std::cout << "  Vagas: " << idsPraticantesInscritos.size() << " / " << limiteAlunos << std::endl;
}