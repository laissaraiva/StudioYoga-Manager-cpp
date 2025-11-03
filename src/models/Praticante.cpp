#include "Praticante.h" // <--- Inclui o header

Praticante::Praticante(int id, const std::string& nome, const std::string& email, int idPlano)
    : Pessoa(id, nome, email), // <--- Chama o construtor da Mãe
      idPlano(idPlano) {}

int Praticante::getIdPlano() const {
    return idPlano;
}

void Praticante::inscreverEmAula(int idAula) {
    idsAulasInscrito.push_back(idAula);
}

void Praticante::exibirDetalhes() const {
    std::cout << "--- Praticante (ID: " << id << ") ---" << std::endl;
    std::cout << "  Nome: " << nome << std::endl;
    std::cout << "  Email: " << email << std::endl;
    std::cout << "  Plano ID: " << idPlano << std::endl;
    std::cout << "  Aulas Inscrito (IDs): ";
    if (idsAulasInscrito.empty()) {
        std::cout << "Nenhuma";
    } else {
        for(int id : idsAulasInscrito) {
            std::cout << id << " ";
        }
    }
    std::cout << "\n" << std::endl;
}