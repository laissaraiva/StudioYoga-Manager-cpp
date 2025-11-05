#include "models/YogaPets.h"
#include <iostream>
using namespace std;

YogaPets::YogaPets(int id, const std::string& horario, int idInstrutor, int limiteAlunos, const std::string& tipoPet)
    : Aula(id, horario, idInstrutor, limiteAlunos), // Chama o construtor da Mãe
      tipoPetPermitido(tipoPet) {
}

std::string YogaPets::getTipoPet() const {
    return tipoPetPermitido;
}

std::string YogaPets::getTipo() const {
    return "YogaPets";
}

void YogaPets::exibirDetalhes() const {
    // 1. Chama o método da Mãe
    Aula::exibirDetalhes();

    // 2. Adiciona a info específica
    cout << "  Pets Permitidos: " << tipoPetPermitido << endl;
}