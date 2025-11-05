#include "models/Praticante.h"
using namespace std;

Praticante::Praticante(int id, const std::string& nome, const std::string& email, int idPlano)
    : Pessoa(id, nome, email), // Chama o construtor da Mãe
      idPlano(idPlano) {}

int Praticante::getIdPlano() const {
    return idPlano;
}

void Praticante::inscreverEmAula(int idAula) {
    idsAulasInscrito.push_back(idAula);
}

void Praticante::exibirDetalhes() const {
    cout << "--- Praticante (ID: " << id << ") ---" << endl;
    cout << "  Nome: " << nome << endl;
    cout << "  Email: " << email << endl;
    cout << "  Plano ID: " << idPlano << endl;
    cout << "  Aulas Inscrito (IDs): ";
    if (idsAulasInscrito.empty()) {
        cout << "Nenhuma";
    } else {
        for(int id : idsAulasInscrito) {
            cout << id << " ";
        }
    }
    cout << "\n" << endl;
}