#ifndef PLANO_H
#define PLANO_H

#include <string>
#include <iostream>

// Classe simples que representa planos de assinatura do estúdio
class Plano {
private:
    // Encapsulamento: atributos privados, acessados por métodos públicos
    int id;
    std::string nome;
    double preco;

public:
    // Construtor para inicialização do objeto
    Plano(int id, const std::string& nome, double preco);

    // Interface pública
    int getId() const;
    std::string getNome() const;
    double getPreco() const;

    void exibirDetalhes() const;
};

#endif // PLANO_H