#include "models/Pessoa.h" // Inclui o cabeçalho da classe Pessoa.

// Construtor da classe base Pessoa.
// Inicializa os atributos básicos (id, nome, email) usando a lista de inicialização.
Pessoa::Pessoa(int id, const std::string& nome, const std::string& email)
    : id(id), nome(nome), email(email) {
    // O corpo do construtor fica vazio.
}

// Destrutor virtual da classe Pessoa.
// É virtual para garantir que os destrutores das classes filhas sejam chamados corretamente.
Pessoa::~Pessoa() {}

// Retorna o ID da pessoa.
int Pessoa::getId() const { 
    return id; 
}

// Retorna o Nome da pessoa.
std::string Pessoa::getNome() const { 
    return nome; 
}

// Retorna o Email da pessoa.
std::string Pessoa::getEmail() const { 
    return email; 
}

// Define ou atualiza o Nome da pessoa.
void Pessoa::setNome(const std::string& novoNome) {
    this->nome = novoNome;
}

// Define ou atualiza o Email da pessoa.
void Pessoa::setEmail(const std::string& novoEmail) {
    // (Aqui poderia ter uma validação de email)
    this->email = novoEmail;
}