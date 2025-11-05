#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <iostream>
using namespace std;

// Classe abstrata, base para as que herdarão dela
class Pessoa {
protected:
    int id;
    string nome;
    string email;

public:
    // Construtor
    Pessoa(int id, const string& nome, const string& email);
    virtual ~Pessoa();

    int getId() const;
    string getNome() const;
    string getEmail() const;

    void setNome(const string& novoNome);
    void setEmail(const string& novoEmail);

    // Método virtual
    virtual void exibirDetalhes() const = 0;
};

#endif // PESSOA_H