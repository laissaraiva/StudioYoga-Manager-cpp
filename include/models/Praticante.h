#ifndef PRATICANTE_H
#define PRATICANTE_H

#include "models/Pessoa.h"
#include "models/Plano.h"    // <--- Inclui o Plano (Composição)
#include <vector>

class Praticante : public Pessoa {
private:
    int idPlano; // ID do plano que o praticante assinou
    std::vector<int> idsAulasInscrito;

public:
    Praticante(int id, const std::string& nome, const std::string& email, int idPlano);

    int getIdPlano() const;
    void inscreverEmAula(int idAula);

    // ----- NOVO MÉTODO ADICIONADO -----
    /**
     * @brief Retorna uma referência constante ao vetor de IDs das aulas inscritas.
     * Necessário para a função salvarDados() do StudioManager.
     */
    const std::vector<int>& getAulasInscritas() const { return idsAulasInscrito; }
    // ---------------------------------

    // Implementação do método abstrato da Mãe
    void exibirDetalhes() const override;
};

#endif // PRATICANTE_H