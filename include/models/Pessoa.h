#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <iostream>
using namespace std;

class Pessoa {
protected:
    int id;
    string nome;
    string email;

public:
    Pessoa(int id, const string& nome, const string& email);
    virtual ~Pessoa();

    int getId() const;
    string getNome() const;
    string getEmail() const;

    void setNome(const string& novoNome);
    void setEmail(const string& novoEmail);

    virtual void exibirDetalhes() const = 0;
};

#endif // PESSOA_H