#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <string>
// Inclui os cabeçalhos dos modelos que este serviço irá salvar e carregar.
#include "models/Praticante.h"
#include "models/Instrutor.h"
#include "models/Plano.h"


/*
 * O namespace DataManager é um serviço estático para
 * persistir (salvar/carregar) os dados do modelo em arquivos .txt.
 */
namespace DataManager {

    // Salva o vetor de praticantes em um arquivo .txt.
    void salvarPraticantes(const std::vector<Praticante>& praticantes, const std::string& arquivo);
    // Carrega os dados de praticantes de um arquivo .txt e retorna um vetor.
    std::vector<Praticante> carregarPraticantes(const std::string& arquivo);

    
    // Salva o vetor de instrutores em um arquivo .txt.
    void salvarInstrutores(const std::vector<Instrutor>& instrutores, const std::string& arquivo);
    // Carrega os dados de instrutores de um arquivo .txt e retorna um vetor.
    std::vector<Instrutor> carregarInstrutores(const std::string& arquivo);
    
    
    // Salva o vetor de planos em um arquivo .txt.
    void salvarPlanos(const std::vector<Plano>& planos, const std::string& arquivo);
    // Carrega os dados de planos de um arquivo .txt e retorna um vetor.
    std::vector<Plano> carregarPlanos(const std::string& arquivo);
}

#endif // DATAMANAGER_H