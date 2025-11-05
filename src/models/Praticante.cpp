#include "models/Praticante.h"
using namespace std;

// Implementação da classe Praticante (herda de Pessoa)
// Herança: reaproveita id, nome, email de pessoa.
// Encapsulamento: acessa e manipula seus próprios dados via métodos.
Praticante::Praticante(int id, const std::string& nome, const std::string& email, int idPlano)
    : Pessoa(id, nome, email),
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