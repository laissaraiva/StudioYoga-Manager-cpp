#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

/*
 * Namespace estático para validar entradas do usuário.
 * Contém funções utilitárias que podem ser chamadas de qualquer lugar.
 */
namespace Validator {

    // Verifica se uma string não está vazia (após remover espaços)
    bool isStringValida(const std::string& input);

    // Verifica se um email tem um formato básico (contém @ e .)
    bool isEmailValido(const std::string& email);

}

#endif // VALIDATOR_H