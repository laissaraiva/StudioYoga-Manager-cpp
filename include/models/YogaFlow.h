#ifndef YOGAFLOW_H
#define YOGAFLOW_H

#include "models/Aula.h" // Inclui a classe Mãe
#include <string>

class YogaFlow : public Aula {
public:
    // Construtor (apenas repassa os dados para a Mãe)
    YogaFlow(int id, const std::string& horario, int idInstrutor, int limiteAlunos);

    // --- Implementação do Contrato (Obrigatório) ---

    /**
     * @brief Retorna o tipo da aula.
     */
    std::string getTipo() const override;

    /**
     * @brief Exibe os detalhes da aula.
     * (Neste caso, só chama o da Mãe, pois não há dados extras)
     */
    void exibirDetalhes() const override;
};

#endif // YOGAFLOW_H