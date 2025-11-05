#include "models/HotYoga.h"
#include <iostream>
using namespace std;

// Construtor com atributos de Aula e inicializacao do seu próprio atributo
HotYoga::HotYoga(int id, const std::string& horario, int idInstrutor, int limiteAlunos, int temperatura)
    : Aula(id, horario, idInstrutor, limiteAlunos),
      temperaturaSala(temperatura) {
}

// Getters Específicos
int HotYoga::getTemperatura() const {
    return temperaturaSala;
}

std::string HotYoga::getTipo() const {
    return "HotYoga";
}

// Sobrescrita do Método
void HotYoga::exibirDetalhes() const {
    // 1. Chama o método da Mãe para imprimir as infos comuns
    Aula::exibirDetalhes();

    // 2. Adiciona a informação específica da HotYoga
    cout << "  Temperatura da Sala: " << temperaturaSala << "(em C)" << endl; // <--- removido std::
}