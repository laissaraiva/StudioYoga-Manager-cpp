#include "models/Instrutor.h"
using namespace std;

Instrutor::Instrutor(int id, const std::string& nome, const std::string& email, const std::string& especialidade)
    : Pessoa(id, nome, email), // Chama o construtor da Mãe
      especialidade(especialidade) {}

// Getter
std::string Instrutor::getEspecialidade() const {
    return especialidade;
}

// Lógica de Negócios Comum
void Instrutor::adicionarAula(int idAula) {
    idsAulasMinistradas.push_back(idAula);
}

void Instrutor::exibirDetalhes() const {
    cout << "--- Instrutor (ID: " << id << ") ---" << endl;
    cout << "  Nome: " << nome << endl;
    cout << "  Email: " << email << endl;
    cout << "  Especialidade: " << especialidade << endl;
    cout << "  Aulas Ministradas (IDs): ";
    if (idsAulasMinistradas.empty()) {
        cout << "Nenhuma";
    } else {
        for(int id : idsAulasMinistradas) {
            cout << id << " ";
        }
    }
    cout << "\n" << endl;
}