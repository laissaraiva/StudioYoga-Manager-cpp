#include "models/Plano.h" // Inclui o cabeçalho do Plano.
#include <iostream>       // Necessário para std::cout e std::endl

// Construtor da classe Plano.
// Inicializa os atributos (id, nome, preco) usando a lista de inicialização.
Plano::Plano(int id, const std::string& nome, double preco)
    : id(id), nome(nome), preco(preco) {
    // O corpo do construtor fica vazio.
}

// Retorna o ID do plano.
int Plano::getId() const { 
    return id; 
}

// Retorna o Nome do plano.
std::string Plano::getNome() const { 
    return nome; 
}

// Retorna o Preço do plano.
double Plano::getPreco() const { 
    return preco; 
}

// Imprime os detalhes do plano no console.
void Plano::exibirDetalhes() const {
    std::cout << "  [Plano ID: " << id << "] "
              << nome << " - R$ " << preco << std::endl;
}