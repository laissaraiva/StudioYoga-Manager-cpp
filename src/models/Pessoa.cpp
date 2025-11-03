#include "Pessoa.h" // <--- Inclui o header

Pessoa::Pessoa(int id, const std::string& nome, const std::string& email)
    : id(id), nome(nome), email(email) {}

// Destrutor (importante para herança)
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
    // (Aqui poderia ter uma validação de email)
    this->email = novoEmail;
}