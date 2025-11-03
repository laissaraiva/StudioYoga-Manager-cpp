#ifndef AULA_H
#define AULA_H

#include <vector>
#include <string>
#include <iostream>

class Aula {
protected: // protected para que as classes filhas (como HotYoga) possam acessá-los
    int id;
    std::string horario;
    int idInstrutor;
    int limiteAlunos;
    std::vector<int> idsPraticantesInscritos;

public:
    // --- Construtor ---
    Aula(int id, const std::string& horario, int idInstrutor, int limiteAlunos);

    // --- Destrutor Virtual ---
    // (Obrigatório em classes base de herança)
    virtual ~Aula();

    // --- Métodos Comuns (Lógica de Negócios) ---
    bool isLotada() const;
    bool inscreverPraticante(int idPraticante);
    void cancelarInscricao(int idPraticante);
    bool isPraticanteInscrito(int idPraticante) const;

    // --- Getters Comuns ---
    int getId() const;
    std::string getHorario() const;
    int getLimiteAlunos() const;
    int getVagasDisponiveis() const;
    const std::vector<int>& getIdsPraticantesInscritos() const;

    // --- Métodos Virtuais (O Contrato) ---

    /**
     * @brief Retorna o nome/tipo da aula (ex: "Hot Yoga", "Yoga Normal").
     * Esta é uma "função virtual pura" (= 0), o que torna Aula
     * uma classe abstrata. As classes filhas SÃO OBRIGADAS a implementar isto.
     */
    virtual std::string getTipoDeAula() const = 0;

    /**
     * @brief Exibe detalhes específicos da aula (virtual para que filhas possam adicionar mais info).
     */
    virtual void exibirDetalhes() const;
};

#endif // AULA_H