#include "models/Plano.h" // <--- Inclui o header

Plano::Plano(int id, const std::string& nome, double preco)
    : id(id), nome(nome), preco(preco) {}

int Plano::getId() const { return id; }
std::string Plano::getNome() const { return nome; }
double Plano::getPreco() const { return preco; }

void Plano::exibirDetalhes() const {
    std::cout << "  [Plano ID: " << id << "] "
              << nome << " - R$ " << preco << std::endl;
}