#include "models/Instrutor.h" // Inclui o cabeçalho do Instrutor.
#include <iostream>           // Necessário para std::cout e std::endl

// Construtor da classe Instrutor.
// Chama o construtor da classe base (Pessoa) e inicializa o atributo 'especialidade'.
Instrutor::Instrutor(int id, const std::string& nome, const std::string& email, const std::string& especialidade)
    : Pessoa(id, nome, email), 
      especialidade(especialidade) {
    // O corpo do construtor fica vazio, pois a inicialização é feita na lista.
}

// Retorna a especialidade do instrutor.
std::string Instrutor::getEspecialidade() const {
    return especialidade;
}

// Adiciona o ID de uma aula ao histórico de aulas ministradas pelo instrutor.
void Instrutor::adicionarAula(int idAula) {
    idsAulasMinistradas.push_back(idAula);
}

// Sobrescreve o método 'exibirDetalhes' para mostrar informações do instrutor.
void Instrutor::exibirDetalhes() const {
    std::cout << "--- Instrutor (ID: " << id << ") ---" << std::endl;
    // Imprime os dados herdados da classe Pessoa (id, nome, email).
    std::cout << "  Nome: " << nome << std::endl;
    std::cout << "  Email: " << email << std::endl;
    // Imprime o dado específico do Instrutor.
    std::cout << "  Especialidade: " << especialidade << std::endl;
    
    // Lista os IDs de todas as aulas que este instrutor ministra.
    std::cout << "  Aulas Ministradas (IDs): ";
    if (idsAulasMinistradas.empty()) {
        std::cout << "Nenhuma";
    } else {
        // Itera pelo vetor de IDs e imprime cada um.
        for(int id : idsAulasMinistradas) {
            std::cout << id << " ";
        }
    }
    std::cout << "\n" << std::endl;
}