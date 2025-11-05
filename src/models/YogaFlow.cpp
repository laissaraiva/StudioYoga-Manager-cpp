#include "models/YogaFlow.h"
#include <iostream>
using namespace std;

// Construtor
// Apenas chama o construtor da classe Mãe (Aula)
YogaFlow::YogaFlow(int id, const std::string& horario, int idInstrutor, int limiteAlunos)
    : Aula(id, horario, idInstrutor, limiteAlunos) {
    // Corpo vazio, pois não há atributos próprios para inicializar
}

// Implementação do Contrato

std::string YogaFlow::getTipo() const {
    // IMPORTANTE: Use um nome simples e sem espaços
    return "YogaFlow";
}

void YogaFlow::exibirDetalhes() const {
    Aula::exibirDetalhes();
}