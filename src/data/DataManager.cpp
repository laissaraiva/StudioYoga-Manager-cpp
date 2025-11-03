/*
 * Arquivo: src/data/DataManager.cpp
 * Descrição: Implementação do serviço de persistência de dados (lê/escreve .txt).
 */

#include "data/DataManager.h" 
#include <fstream>
#include <sstream>
#include <iostream>

// --- Praticantes ---
void DataManager::salvarPraticantes(const std::vector<Praticante>& praticantes, const std::string& arquivo) {
    std::ofstream outFile(arquivo, std::ios::trunc);
    if (!outFile.is_open()) return;
    
    // Formato: id,nome,email,idPlano
    for (const Praticante& p : praticantes) {
        outFile << p.getId() << ","
                << p.getNome() << ","
                << p.getEmail() << ","
                << p.getIdPlano() << "\n";
    }
    outFile.close();
}

std::vector<Praticante> DataManager::carregarPraticantes(const std::string& arquivo) {
    std::vector<Praticante> praticantes;
    std::ifstream inFile(arquivo);
    if (!inFile.is_open()) return praticantes; // Retorna vetor vazio

    std::string linha;
    while (std::getline(inFile, linha)) {
        std::stringstream ss(linha);
        std::string idStr, nome, email, idPlanoStr;
        
        std::getline(ss, idStr, ',');
        std::getline(ss, nome, ',');
        std::getline(ss, email, ',');
        std::getline(ss, idPlanoStr, ',');

        try {
            int id = std::stoi(idStr);
            int idPlano = std::stoi(idPlanoStr);
            praticantes.emplace_back(id, nome, email, idPlano);
        } catch (const std::exception& e) {
            std::cerr << "Erro ao ler praticante: " << e.what() << std::endl;
        }
    }
    inFile.close();
    return praticantes;
}

// --- Instrutores ---
void DataManager::salvarInstrutores(const std::vector<Instrutor>& instrutores, const std::string& arquivo) {
    std::ofstream outFile(arquivo, std::ios::trunc);
    if (!outFile.is_open()) return;

    // Formato: id,nome,email,especialidade
    for (const Instrutor& i : instrutores) {
        outFile << i.getId() << ","
                << i.getNome() << ","
                << i.getEmail() << ","
                << i.getEspecialidade() << "\n";
    }
    outFile.close();
}

std::vector<Instrutor> DataManager::carregarInstrutores(const std::string& arquivo) {
    std::vector<Instrutor> instrutores;
    std::ifstream inFile(arquivo);
    if (!inFile.is_open()) return instrutores;

    std::string linha;
    while (std::getline(inFile, linha)) {
        std::stringstream ss(linha);
        std::string idStr, nome, email, especialidade;

        std::getline(ss, idStr, ',');
        std::getline(ss, nome, ',');
        std::getline(ss, email, ',');
        std::getline(ss, especialidade, ',');

        try {
            int id = std::stoi(idStr);
            instrutores.emplace_back(id, nome, email, especialidade);
        } catch (const std::exception& e) {
            std::cerr << "Erro ao ler instrutor: " << e.what() << std::endl;
        }
    }
    inFile.close();
    return instrutores;
}

// --- Planos ---
void DataManager::salvarPlanos(const std::vector<Plano>& planos, const std::string& arquivo) {
    std::ofstream outFile(arquivo, std::ios::trunc);
    if (!outFile.is_open()) return;

    // Formato: id,nome,preco
    for (const Plano& p : planos) {
        outFile << p.getId() << ","
                << p.getNome() << ","
                << p.getPreco() << "\n";
    }
    outFile.close();
}

std::vector<Plano> DataManager::carregarPlanos(const std::string& arquivo) {
    std::vector<Plano> planos;
    std::ifstream inFile(arquivo);
    if (!inFile.is_open()) return planos;

    std::string linha;
    while (std::getline(inFile, linha)) {
        std::stringstream ss(linha);
        std::string idStr, nome, precoStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, nome, ',');
        std::getline(ss, precoStr, ',');

        try {
            int id = std::stoi(idStr);
            double preco = std::stod(precoStr);
            planos.emplace_back(id, nome, preco);
        } catch (const std::exception& e) {
            std::cerr << "Erro ao ler plano: " << e.what() << std::endl;
        }
    }
    inFile.close();
    return planos;
}