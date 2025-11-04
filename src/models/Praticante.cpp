#include "models/Praticante.h" // Inclui o cabeçalho do Praticante.
#include <iostream>            // Necessário para std::cout e std::endl

// Construtor da classe Praticante.
// Chama o construtor da classe base (Pessoa) e inicializa o atributo 'idPlano'.
Praticante::Praticante(int id, const std::string& nome, const std::string& email, int idPlano)
    : Pessoa(id, nome, email), 
      idPlano(idPlano) {
    // O corpo do construtor fica vazio, pois a inicialização é feita na lista.
}

// Retorna o ID do plano ao qual o praticante está associado.
int Praticante::getIdPlano() const {
    return idPlano;
}

// Adiciona o ID de uma aula ao histórico de aulas do praticante.
void Praticante::inscreverEmAula(int idAula) {
    idsAulasInscrito.push_back(idAula);
}

// Sobrescreve o método 'exibirDetalhes' para mostrar informações do praticante.
void Praticante::exibirDetalhes() const {
    std::cout << "--- Praticante (ID: " << id << ") ---" << std::endl;
    // Imprime os dados herdados da classe Pessoa (id, nome, email).
    std::cout << "  Nome: " << nome << std::endl;
    std::cout << "  Email: " << email << std::endl;
    // Imprime os dados específicos do Praticante.
    std::cout << "  Plano ID: " << idPlano << std::endl;
    
    // Lista os IDs de todas as aulas em que o praticante está inscrito.
    std::cout << "  Aulas Inscrito (IDs): ";
    if (idsAulasInscrito.empty()) {
        std::cout << "Nenhuma";
    } else {
        // Itera pelo vetor de IDs e imprime cada um.
        for(int id : idsAulasInscrito) {
            std::cout << id << " ";
        }
    }
    std::cout << "\n" << std::endl;
}