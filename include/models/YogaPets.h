#ifndef YOGAPETS_H
#define YOGAPETS_H

#include "models/Aula.h"
#include <string>

// Classe herdeira de Aula que representa um tipo de aula
class YogaPets : public Aula {
private:
    std::string tipoPetPermitido;

public:
    YogaPets(int id, const std::string& horario, int idInstrutor, int limiteAlunos, const std::string& tipoPet);

    // Implementação do Contrato
    std::string getTipo() const override;

    // Métodos Específicos
    std::string getTipoPet() const;

    void exibirDetalhes() const override;
};

#endif // YOGAPETS_H