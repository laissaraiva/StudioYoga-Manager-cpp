#ifndef HOTYOGA_H
#define HOTYOGA_H

#include "models/Aula.h"


class HotYoga : public Aula {
private:
    int temperaturaSala; // Atributo específico da HotYoga

public:
    // Construtor 
  
    HotYoga(int id, const std::string& horario, int idInstrutor, int limiteAlunos, int temperatura);

    // Implementação do Contrato 
    std::string getTipoDeAula() const override;

    //Métodos Específicos
    int getTemperatura() const;
    void exibirDetalhes() const override; // Sobrescreve para adicionar a temperatura
};

#endif 