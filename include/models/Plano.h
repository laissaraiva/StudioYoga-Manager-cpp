#ifndef PLANO_H
#define PLANO_H

#include <string>
#include <iostream>

class Plano {
private:
    int id;
    std::string nome; // Ex: "Mensal", "Trimestral"
    double preco;

public:
    Plano(int id, const std::string& nome, double preco);

    int getId() const;
    std::string getNome() const;
    double getPreco() const;

    void exibirDetalhes() const;
};

#endif 