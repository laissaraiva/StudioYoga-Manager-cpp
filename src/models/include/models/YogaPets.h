#ifndef YOGAPETS_H
#define YOGAPETS_H

#include "Aula.h"
#include <string>

class YogaPets : public Aula {
private:
    std::string tipoPetPermitido; // Atributo específico

public:
    YogaPets(int id, const std::string& horario, int idInstrutor, int limiteAlunos, const std::string& tipoPet);

    // Implementação do Contrato (Obrigatório)
    std::string getTipoDeAula() const override;

    // Métodos Específicos
    std::string getTipoPetPermitido() const;
    void exibirDetalhes() const override;
};

#endif // YOGAPETS_H