#ifndef YOGAPETS_H
#define YOGAPETS_H

#include "models/Aula.h"
#include <string>

class YogaPets : public Aula {
private:
    std::string tipoPetPermitido; // Atributo específico

public:
    YogaPets(int id, const std::string& horario, int idInstrutor, int limiteAlunos, const std::string& tipoPet);

    // Implementação do Contrato (Obrigatório)
    // --- ATUALIZADO (renomeado) ---
    std::string getTipo() const override;

    // Métodos Específicos
    // --- ATUALIZADO (renomeado) ---
    std::string getTipoPet() const;

    void exibirDetalhes() const override;
};

#endif // YOGAPETS_H