#ifndef HOTYOGA_H
#define HOTYOGA_H

#include "models/Aula.h"

class HotYoga : public Aula {
private:
    int temperaturaSala; // Atributo específico da HotYoga

public:
    // Construtor: herda atributos de Aula
    HotYoga(int id, const std::string& horario, int idInstrutor, int limiteAlunos, int temperatura);

    std::string getTipo() const override;

    // Métodos Específicos
    int getTemperatura() const;
    void exibirDetalhes() const override; // Sobrescrita para adicionar a temperatura
};

#endif // HOTYOGA_H