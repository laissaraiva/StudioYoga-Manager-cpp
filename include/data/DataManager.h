#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <string>
using namespace std;

#include "models/Plano.h"
#include "models/Instrutor.h"
#include "models/Praticante.h"
#include "models/Aula.h"
#include "models/HotYoga.h"
#include "models/YogaPets.h"
#include "models/YogaFlow.h"

class DataManager {
private:
    const string ARQUIVO_PLANOS = "planos.dat";
    const string ARQUIVO_INSTRUTORES = "instrutores.dat";
    const string ARQUIVO_PRATICANTES = "praticantes.dat";
    const string ARQUIVO_AULAS = "aulas.dat";

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
        vector<Plano>& planos,
        vector<Instrutor>& instrutores,
        vector<Praticante>& praticantes,
        vector<Aula*>& aulas,
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
        const vector<Plano>& planos,
        const vector<Instrutor>& instrutores,
        const vector<Praticante>& praticantes,
        const vector<Aula*>& aulas
    );
};

#endif // DATAMANAGER_H