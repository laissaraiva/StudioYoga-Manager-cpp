#include "validator/Validator.h"
#include <algorithm> // Para std::find_if
#include <cctype>    // Para std::isspace

// Namespace anônimo para funções auxiliares (privadas a este arquivo)
namespace {
    std::string trim(const std::string& s) {
        auto start = std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        });
        auto end = std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base();
        
        if (start >= end) {
            return ""; // String vazia ou só com espaços
        }
        return std::string(start, end);
    }
}

// Implementação da função pública 'isStringValida'
bool Validator::isStringValida(const std::string& input) {
    return !trim(input).empty();
}

// Implementação da função pública 'isEmailValido'
bool Validator::isEmailValido(const std::string& email) {
    size_t posArroba = email.find('@');
    size_t posPonto = email.find('.', posArroba);

    // Checa se @ foi encontrado, se . foi encontrado depois do @, e se o . não é logo depois do @
    return (posArroba != std::string::npos && 
            posPonto != std::string::npos && 
            posPonto > posArroba + 1 &&
            posPonto != email.length() - 1); // Garante que o . não é o último caractere
}