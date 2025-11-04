#ifndef AULA_H
#define AULA_H

#include <vector>
#include <string>
#include <iostream>

class Aula {
protected: // protected para que as classes filhas possam acessar
    int id;
    std::string horario;
    int idInstrutor;
    int limiteAlunos;
    std::vector<int> idsPraticantesInscritos;

public:
    //construtor 
    Aula(int id, const std::string& horario, int idInstrutor, int limiteAlunos);

    // destrutor Virtual 
    
    virtual ~Aula();

    // Métodos
    bool isLotada() const;
    bool inscreverPraticante(int idPraticante);
    void cancelarInscricao(int idPraticante);
    bool isPraticanteInscrito(int idPraticante) const;

    //Getters
    int getId() const;
    std::string getHorario() const;
    int getLimiteAlunos() const;
    int getVagasDisponiveis() const;
    const std::vector<int>& getIdsPraticantesInscritos() const;

    // Métodos Virtuais

    /**
     * @brief Retorna o nome/tipo da aula. 
     * Esta é uma "função virtual pura" (= 0), o que torna Aula
     * uma classe abstrata. As classes filhas precisam implementar isto.
     */
    virtual std::string getTipoDeAula() const = 0;

    /**
     * @brief Exibe detalhes específicos da aula. 
     */
    virtual void exibirDetalhes() const;
};

#endif 