#include "validator/Validator.h" 
#include <algorithm> 
#include <cctype>    

// Namespace anônimo para funções auxiliares
// Funções aqui são visíveis apenas para este arquivo (.cpp)
namespace {
    // Remove espaços em branco do início da string
    std::string trim_left(const std::string& s) {
        auto it = std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        });
        return std::string(it, s.end());
    }

    // Remove espaços em branco do fim da string
    std::string trim_right(const std::string& s) {
        auto it = std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base();
        return std::string(s.begin(), it);
    }

    // Remove espaços em branco de ambos os lados
    std::string trim(const std::string& s) {
        return trim_left(trim_right(s));
    }
} // Fim do namespace anônimo

// Implementação da função pública 'isStringValida'
bool Validator::isStringValida(const std::string& input) {
    // Retorna 'true' se a string, após "limpa" (trim), não estiver vazia.
    return !trim(input).empty();
}

// Implementação da função pública 'isEmailValido'
bool Validator::isEmailValido(const std::string& email) {
    // Validação simples: checa se existe um '@' e um '.' após o '@'.
    
    size_t posArroba = email.find('@');
    size_t posPonto = email.find('.', posArroba);

    // Retorna true se encontrou '@' e '.' na ordem correta
    return (posArroba != std::string::npos && posPonto != std::string::npos && posPonto > posArroba);
}