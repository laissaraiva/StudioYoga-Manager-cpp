#ifndef HOTYOGA_H
#define HOTYOGA_H

#include "models/Aula.h"

// HotYoga É-UM tipo de Aula
class HotYoga : public Aula {
private:
    int temperaturaSala; // Atributo específico da HotYoga

public:
    // --- Construtor ---
    // (Note como ele chama o construtor da "Mãe" (Aula::Aula))
    HotYoga(int id, const std::string& horario, int idInstrutor, int limiteAlunos, int temperatura);

    // --- Implementação do Contrato (Obrigatório) ---
    // --- ATUALIZADO (renomeado) ---
    std::string getTipo() const override;

    // --- Métodos Específicos ---
    int getTemperatura() const;
    void exibirDetalhes() const override; // Sobrescreve para adicionar a temperatura
};

#endif // HOTYOGA_H