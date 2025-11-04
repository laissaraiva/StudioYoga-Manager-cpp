/*
 * Arquivo: src/validator/Validator.cpp
 * Descrição: Implementação das funções de validação.
 */

#include "validator/Validator.h" // (O CMake vai achar o caminho)
#include <algorithm> // Para std::find_if
#include <cctype>    // Para std::isspace (verificar espaço em branco)

// --- Funções Auxiliares (privadas para este arquivo) ---
// namespace anônimo torna as funções 'trim' visíveis apenas neste .cpp
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
} // namespace anônimo

// --- Implementação das Funções Públicas ---

bool Validator::isStringValida(const std::string& input) {
    // Retorna 'true' se a string, após ser "limpa" (trim), não estiver vazia.
    return !trim(input).empty();
}

bool Validator::isEmailValido(const std::string& email) {
    // É uma validação SIMPLES (não perfeita).
    // Apenas checa se existe um '@' e se existe um '.' depois do '@'.
    
    size_t posArroba = email.find('@');
    size_t posPonto = email.find('.', posArroba);

    // Retorna true se:
    // 1. O '@' foi encontrado (posArroba != std::string::npos)
    // 2. O '.' foi encontrado DEPOIS do '@' (posPonto != std::string::npos && posPonto > posArroba)
    return (posArroba != std::string::npos && posPonto != std::string::npos && posPonto > posArroba);
}