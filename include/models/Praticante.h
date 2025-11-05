#ifndef PRATICANTE_H
#define PRATICANTE_H

#include "models/Pessoa.h" // Inclui a classe Mãe
#include <vector>
#include <iostream>

class Praticante : public Pessoa {
private:
    int idPlano; // ID do plano que o praticante assinou
    std::vector<int> idsAulasInscrito; // Lista de IDs das aulas

public:
    // Construtor
    Praticante(int id, const std::string& nome, const std::string& email, int idPlano);

    // Getters
    int getIdPlano() const;

    // Lógica de Negócio
    void inscreverEmAula(int idAula);
    // Exposição de leitura das aulas inscritas (para persistência)
    const std::vector<int>& getAulasInscritas() const { return idsAulasInscrito; }
    
    // Método de exibição (polimorfismo)
    void exibirDetalhes() const override;
    
    // Define um novo nome (herdado de Pessoa)
    void setNome(const std::string& novoNome) {
        this->nome = novoNome; 
    }
    // Define um novo email (herdado de Pessoa)
    void setEmail(const std::string& novoEmail) {
        this->email = novoEmail; 
    }
    // Define um novo plano
    void setIdPlano(int novoIdPlano) {
        this->idPlano = novoIdPlano; 
    }
};

#endif // PRATICANTE_H