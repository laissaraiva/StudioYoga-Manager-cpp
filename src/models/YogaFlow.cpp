#include "models/YogaFlow.h"
#include <iostream>

// --- Construtor ---
// Apenas chama o construtor da classe Mãe (Aula)
YogaFlow::YogaFlow(int id, const std::string& horario, int idInstrutor, int limiteAlunos)
    : Aula(id, horario, idInstrutor, limiteAlunos) {
    // Corpo vazio, pois não há atributos próprios para inicializar
}

// --- Implementação do Contrato ---

std::string YogaFlow::getTipo() const {
    // IMPORTANTE: Use um nome simples e sem espaços
    return "YogaFlow";
}

void YogaFlow::exibirDetalhes() const {
    // 1. Chama o método da Mãe para imprimir as infos comuns
    Aula::exibirDetalhes();

    // 2. (Opcional) Adiciona infos extras
    // Como esta classe não tem, podemos até omitir
    // std::cout << "  Estilo: Vinyasa Flow" << std::endl;
}