#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <string>
#include "models/Praticante.h"
#include "models/Instrutor.h"
#include "models/Plano.h"


/*
 *  serviço estático para persistir (salvar/carregar) os dados do modelo em arquivos .txt.
 */
namespace DataManager {

    // --- Métodos para Praticantes ---
    // (Assume que Praticante tem: getId, getNome, getEmail, getIdPlano)
    void salvarPraticantes(const std::vector<Praticante>& praticantes, const std::string& arquivo);
    // (Assume que Praticante tem construtor: Praticante(id, nome, email, idPlano))
    std::vector<Praticante> carregarPraticantes(const std::string& arquivo);

    // --- Métodos para Instrutores ---
    // (Assume que Instrutor tem: getId, getNome, getEmail, getEspecialidade)
    void salvarInstrutores(const std::vector<Instrutor>& instrutores, const std::string& arquivo);
    // (Assume que Instrutor tem construtor: Instrutor(id, nome, email, especialidade))
    std::vector<Instrutor> carregarInstrutores(const std::string& arquivo);
    
    // --- Métodos para Planos ---
    // (Assume que Plano tem: getId, getNome, getPreco)
    void salvarPlanos(const std::vector<Plano>& planos, const std::string& arquivo);
    // (Assume que Plano tem construtor: Plano(id, nome, preco))
    std::vector<Plano> carregarPlanos(const std::string& arquivo);
}

#endif 