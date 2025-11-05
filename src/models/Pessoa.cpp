#include "models/Pessoa.h"

//Encapsulamento com atributos privados e acesso controlado por getters/setters.
Pessoa::Pessoa(int id, const std::string& nome, const std::string& email)
    : id(id), nome(nome), email(email) {}

// Destrutor
Pessoa::~Pessoa() {}

// Getters
int Pessoa::getId() const { return id; }
std::string Pessoa::getNome() const { return nome; }
std::string Pessoa::getEmail() const { return email; }

// Setters
void Pessoa::setNome(const std::string& novoNome) {
    this->nome = novoNome;
}
void Pessoa::setEmail(const std::string& novoEmail) {
    this->email = novoEmail;
}