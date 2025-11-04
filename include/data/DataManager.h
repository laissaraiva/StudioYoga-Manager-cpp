#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <string>
#include "models/Plano.h"
#include "models/Instrutor.h"
#include "models/Praticante.h"
#include "models/Aula.h"
// Inclua aqui os .h das classes filhas de Aula
#include "models/HotYoga.h"
#include "models/YogaPets.h"
#include "models/YogaFlow.h"

class DataManager {
private:
    // Os nomes dos arquivos agora são responsabilidade desta classe
    const std::string ARQUIVO_PLANOS = "planOS.dat";
    const std::string ARQUIVO_INSTRUTORES = "instrutores.dat";
    const std::string ARQUIVO_PRATICANTES = "praticantes.dat";
    const std::string ARQUIVO_AULAS = "aulas.dat";

public:
    /**
     * @brief Carrega todos os dados dos arquivos .dat para os vetores em memória.
     * @param planos Vetor de Planos (passado por referência para ser preenchido)
     * @param instrutores Vetor de Instrutores (passado por referência)
     * @param praticantes Vetor de Praticantes (passado por referência)
     * @param aulas Vetor de ponteiros de Aula (passado por referência)
     * @param proximoIdPessoa Contador de ID (passado por referência para ser atualizado)
     * @param proximoIdAula Contador de ID (passado por referência)
     * @param proximoIdPlano Contador de ID (passado por referência)
     */
    void carregarDados(
        std::vector<Plano>& planos,
        std::vector<Instrutor>& instrutores,
        std::vector<Praticante>& praticantes,
        std::vector<Aula*>& aulas,
        int& proximoIdPessoa,
        int& proximoIdAula,
        int& proximoIdPlano
    );

    /**
     * @brief Salva todos os dados dos vetores em memória para os arquivos .dat
     * @param planos Vetor de Planos (constante, pois só vamos ler)
     * @param instrutores Vetor de Instrutores (constante)
     * @param praticantes Vetor de Praticantes (constante)
     * @param aulas Vetor de ponteiros de Aula (constante)
     */
    void salvarDados(
        const std::vector<Plano>& planos,
        const std::vector<Instrutor>& instrutores,
        const std::vector<Praticante>& praticantes,
        const std::vector<Aula*>& aulas
    );

    // Métodos auxiliares 'find' necessários para carregar dados
    // (Sim, eles ficam duplicados, mas isso é parte de uma separação de responsabilidade)
    // Para simplificar, vamos deixar os 'find' apenas no StudioManager por enquanto,
    // e o carregarDados vai ter que recriar os links depois.
    // ... No seu código, 'carregarDados' já usa 'find', então ele precisa deles.
    // Para manter MÍNIMA ALTERAÇÃO, vamos deixar os finders no StudioManager
    // e ajustar o carregarDados para não depender deles.
    // ...
    // ATUALIZAÇÃO: O seu 'carregarDados' original é muito complexo e
    // depende dos 'finders'. A forma mais simples de mover é
    // mover os finders para o DataManager também.
    // Mas isso é uma GRANDE alteração.
    //
    // VAMOS FAZER O MAIS SIMPLES:
    // O StudioManager VAI PASSAR ponteiros para suas funções 'find'
    // ... Não, isso é muito complexo.
    //
    // A Lógica mais simples é a que está no seu código.
    // Vamos apenas COPIAR E COLAR.
};

#endif // DATAMANAGER_H