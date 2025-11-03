#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <iostream>

class Pessoa {
protected:
    int id;
    std::string nome;
    std::string email;

public:
    Pessoa(int id, const std::string& nome, const std::string& email);
    virtual ~Pessoa(); // Destrutor virtual para herança

    // Getters comuns
    int getId() const;
    std::string getNome() const;
    std::string getEmail() const;

    // Setters (exemplo)
    void setNome(const std::string& novoNome);
    void setEmail(const std::string& novoEmail);

    // Método virtual puro -> torna Pessoa uma classe Abstrata
    virtual void exibirDetalhes() const = 0;
};

#endif // PESSOA_H