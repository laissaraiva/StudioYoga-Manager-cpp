#ifndef AULA_H
#define AULA_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

// Classe base ABSTRATA para diferentes tipos de aula
// Polimorfismo: as filhas herdam e especializam com suas características.
class Aula {
protected:
    // Encapsulamento: atributos comuns às aulas (usa protected para permitir acesso controlado pelas classes filhas).
    int id;
    string horario;
    int idInstrutor;
    int limiteAlunos;
    vector<int> idsPraticantesInscritos;

public:
    Aula(int id, const string& horario, int idInstrutor, int limiteAlunos);
    virtual ~Aula(); // Destruição correta por ponteiro para a base

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

    // Método virtual: obriga as filhas a informar seu tipo
    virtual string getTipo() const = 0;
    virtual void exibirDetalhes() const;
};

#endif // AULA_H