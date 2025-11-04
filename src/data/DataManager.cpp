#include "data/DataManager.h" // Inclui o cabeçalho correspondente
#include <fstream>  
#include <sstream>  
#include <iostream> 

// Implementação dos praticantes 

void DataManager::salvarPraticantes(const std::vector<Praticante>& praticantes, const std::string& arquivo) {
    std::ofstream outFile(arquivo, std::ios::trunc); // Abre o arquivo para escrita, apagando o conteúdo anterior
    if (!outFile.is_open()) {
        std::cerr << "Erro ao abrir " << arquivo << " para escrita.\n";
        return;
    }
    
    // Formato de saída: id,nome,email,idPlano
    for (const Praticante& p : praticantes) {
        outFile << p.getId() << ","
                << p.getNome() << ","
                << p.getEmail() << ","
                << p.getIdPlano() << "\n"; // '\n' para nova linha
    }
    outFile.close(); 
}

std::vector<Praticante> DataManager::carregarPraticantes(const std::string& arquivo) {
    std::vector<Praticante> praticantes;
    std::ifstream inFile(arquivo); // Abre o arquivo para leitura
    if (!inFile.is_open()) {
        std::cerr << "Info: Arquivo " << arquivo << " nao encontrado. Um novo sera criado ao salvar.\n";
        return praticantes; // Retorna um vetor vazio
    }

    std::string linha;
    while (std::getline(inFile, linha)) { // Lê o arquivo linha por linha
        std::stringstream ss(linha); // Cria um stream para a linha lida
        std::string idStr, nome, email, idPlanoStr;
        
        // Extrai os dados da linha usando a vírgula como delimitador
        std::getline(ss, idStr, ',');
        std::getline(ss, nome, ',');
        std::getline(ss, email, ',');
        std::getline(ss, idPlanoStr, ',');

        try {
            int id = std::stoi(idStr); // Converte string para int
            int idPlano = std::stoi(idPlanoStr); // Converte string para int
            praticantes.emplace_back(id, nome, email, idPlano); // Cria e adiciona o praticante
        } catch (const std::exception& e) {
            // Caso uma linha esteja mal formatada, ignora e reporta o erro
            std::cerr << "Erro ao ler praticante do arquivo: " << e.what() << std::endl;
        }
    }
    inFile.close(); // Fecha o arquivo
    return praticantes;
}

// Implementação dos Instrutores

void DataManager::salvarInstrutores(const std::vector<Instrutor>& instrutores, const std::string& arquivo) {
    std::ofstream outFile(arquivo, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Erro ao abrir " << arquivo << " para escrita.\n";
        return;
    }

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
    if (!inFile.is_open()) {
        std::cerr << "Info: Arquivo " << arquivo << " nao encontrado. Um novo sera criado ao salvar.\n";
        return instrutores;
    }

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
            instrutores.emplace_back(id, nome, email, especialidade); // Cria e adiciona o instrutor
        } catch (const std::exception& e) {
            std::cerr << "Erro ao ler instrutor do arquivo: " << e.what() << std::endl;
        }
    }
    inFile.close();
    return instrutores;
}

//  Implementação dos planos 

void DataManager::salvarPlanos(const std::vector<Plano>& planos, const std::string& arquivo) {
    std::ofstream outFile(arquivo, std::ios::trunc);
    if (!outFile.is_open()) {
         std::cerr << "Erro ao abrir " << arquivo << " para escrita.\n";
        return;
    }

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
    if (!inFile.is_open()) {
        std::cerr << "Info: Arquivo " << arquivo << " nao encontrado. Um novo sera criado ao salvar.\n";
        return planos;
    }

    std::string linha;
    while (std::getline(inFile, linha)) {
        std::stringstream ss(linha);
        std::string idStr, nome, precoStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, nome, ',');
        std::getline(ss, precoStr, ',');

        try {
            int id = std::stoi(idStr);
            double preco = std::stod(precoStr); // Converte string para double
            planos.emplace_back(id, nome, preco); // Cria e adiciona o plano
        } catch (const std::exception& e) {
            std::cerr << "Erro ao ler plano do arquivo: " << e.what() << std::endl;
        }
    }
    inFile.close();
    return planos;
}