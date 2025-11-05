#ifndef AULA_H
#define AULA_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Aula {
protected:
    int id;
    string horario;
    int idInstrutor;
    int limiteAlunos;
    vector<int> idsPraticantesInscritos;

public:
    Aula(int id, const string& horario, int idInstrutor, int limiteAlunos);
    virtual ~Aula();

    bool isLotada() const;
    bool inscreverPraticante(int idPraticante);
    void cancelarInscricao(int idPraticante);
    bool isPraticanteInscrito(int idPraticante) const;

    int getId() const;
    string getHorario() const;
    int getLimiteAlunos() const;
    int getVagasDisponiveis() const;
    const vector<int>& getIdsPraticantesInscritos() const;

    int getIdInstrutor() const { return idInstrutor; }

    virtual string getTipo() const = 0;
    virtual void exibirDetalhes() const;
};

#endif // AULA_H