#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

/*
 * O namespace Validator contém funções utilitárias estáticas
 * para validar dados de entrada.
 */
namespace Validator {

    /**
     * @brief Verifica se uma string não está vazia (após remover espaços em branco).
     * @param input A string a ser verificada.
     * @return true se a string for válida (não vazia), false caso contrário.
     */
    bool isStringValida(const std::string& input);

    /**
     * @brief Faz uma verificação muito simples se um email contém '@' e '.'.
     * @param email A string do email a ser verificada.
     * @return true se o formato for minimamente válido, false caso contrário.
     */
    bool isEmailValido(const std::string& email);

    

} // namespace Validator

#endif // VALIDATOR_H