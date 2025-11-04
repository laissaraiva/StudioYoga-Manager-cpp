#include "models/YogaPets.h" // Inclui o cabeçalho do YogaPets.
#include <iostream>          // Necessário para std::cout e std::endl

// Construtor da classe YogaPets.
// Chama o construtor da classe base (Aula) e inicializa o atributo 'tipoPetPermitido'.
YogaPets::YogaPets(int id, const std::string& horario, int idInstrutor, int limiteAlunos, const std::string& tipoPet)
    : Aula(id, horario, idInstrutor, limiteAlunos), 
      tipoPetPermitido(tipoPet) {
    // O corpo do construtor pode ficar vazio, pois a inicialização é feita na lista.
}

// Retorna o tipo de pet que é permitido nesta aula.
std::string YogaPets::getTipoPetPermitido() const {
    return tipoPetPermitido;
}

// Implementa o método virtual da classe base para retornar o tipo da aula.
std::string YogaPets::getTipoDe-Aula() const {
    return "Yoga com Pets"; // Retorna o nome específico do tipo
}

// Sobrescreve o método 'exibirDetalhes' para incluir informações do Yoga com Pets.
void YogaPets::exibirDetalhes() const {
    // Chama o método da classe base (Aula) para imprimir os detalhes comuns.
    Aula::exibirDetalhes();

    // Adiciona a informação específica desta classe filha (pets permitidos).
    std::cout << "  Pets Permitidos: " << tipoPetPermitido << std::endl;
}