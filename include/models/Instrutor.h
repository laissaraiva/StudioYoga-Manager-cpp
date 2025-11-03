#ifndef INSTRUTOR_H
#define INSTRUTOR_H

#include "models/Pessoa.h"
#include <vector>

class Instrutor : public Pessoa {
private:
    std::string especialidade;
    std::vector<int> idsAulasMinistradas; // IDs das aulas que ele(a) dá

public:
    Instrutor(int id, const std::string& nome, const std::string& email, const std::string& especialidade);

    // Getters/Setters específicos
    std::string getEspecialidade() const;
    void adicionarAula(int idAula);

    // Implementação do método abstrato da Mãe
    void exibirDetalhes() const override;
};

#endif // INSTRUTOR_H