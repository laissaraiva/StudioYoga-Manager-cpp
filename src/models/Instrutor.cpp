#include "models/Instrutor.h" // <--- Inclui o header

Instrutor::Instrutor(int id, const std::string& nome, const std::string& email, const std::string& especialidade)
    : Pessoa(id, nome, email), // <--- Chama o construtor da Mãe
      especialidade(especialidade) {}

std::string Instrutor::getEspecialidade() const {
    return especialidade;
}

void Instrutor::adicionarAula(int idAula) {
    idsAulasMinistradas.push_back(idAula);
}

void Instrutor::exibirDetalhes() const {
    std::cout << "--- Instrutor (ID: " << id << ") ---" << std::endl;
    std::cout << "  Nome: " << nome << std::endl;
    std::cout << "  Email: " << email << std::endl;
    std::cout << "  Especialidade: " << especialidade << std::endl;
    std::cout << "  Aulas Ministradas (IDs): ";
    if (idsAulasMinistradas.empty()) {
        std::cout << "Nenhuma";
    } else {
        for(int id : idsAulasMinistradas) {
            std::cout << id << " ";
        }
    }
    std::cout << "\n" << std::endl;
}