#include "models/HotYoga.h"
#include <iostream>

// Construtor da classe HotYoga.
// Chama o construtor da classe base (Aula) e inicializa o atributo específico 'temperaturaSala'.
HotYoga::HotYoga(int id, const std::string& horario, int idInstrutor, int limiteAlunos, int temperatura)
    : Aula(id, horario, idInstrutor, limiteAlunos),
      temperaturaSala(temperatura) {
    // O corpo do construtor pode ficar vazio, pois a inicialização é feita na lista.
}

// Retorna a temperatura específica desta sala de Hot Yoga.
int HotYoga::getTemperatura() const {
    return temperaturaSala;
}

// Implementa o método virtual da classe base para retornar o tipo da aula.
std::string HotYoga::getTipoDeAula() const {
    return "Hot Yoga"; // Retorna o nome específico do tipo
}

// Sobrescreve o método 'exibirDetalhes' para incluir informações da Hot Yoga.
void HotYoga::exibirDetalhes() const {
    // Chama o método da classe base (Aula) para imprimir os detalhes comuns.
    Aula::exibirDetalhes();

    // Adiciona a informação específica desta classe filha (temperatura).
    std::cout << "  Temperatura da Sala: " << temperaturaSala << "°C" << std::endl;
}