#include "YogaPets.h"
#include <iostream>

YogaPets::YogaPets(int id, const std::string& horario, int idInstrutor, int limiteAlunos, const std::string& tipoPet)
    : Aula(id, horario, idInstrutor, limiteAlunos), // <--- Chama o construtor da Mãe
      tipoPetPermitido(tipoPet) {
}

std::string YogaPets::getTipoPetPermitido() const {
    return tipoPetPermitido;
}

std::string YogaPets::getTipoDeAula() const {
    return "Yoga com Pets"; // Retorna o nome específico
}

void YogaPets::exibirDetalhes() const {
    // 1. Chama o método da Mãe
    Aula::exibirDetalhes();

    // 2. Adiciona a info específica
    std::cout << "  Pets Permitidos: " << tipoPetPermitido << std::endl;
}