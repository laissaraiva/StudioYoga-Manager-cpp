#ifndef COLOR_H
#define COLOR_H

#include <iostream>

/*
 * Namespace para facilitar o uso de cores (códigos ANSI) no console.
 * Funciona na maioria dos terminais modernos (Linux, macOS, Windows 10+).
 */
namespace Color {
    // Reseta a formatação para o padrão
    const std::string RESET = "\033[0m";

    // Cores de Texto (Padrão)
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string WHITE = "\033[37m";
    const std::string CYAN = "\033[36m";

    // Estilos (Brilhante/Negrito - "Bright")
    const std::string B_RED = "\033[1;31m";
    const std::string B_GREEN = "\033[1;32m";
    const std::string B_YELLOW = "\033[1;33m"; // Nosso "Dourado"
    const std::string B_CYAN = "\033[1;36m";
    const std::string B_WHITE = "\033[1;37m"; // Nosso "Branco" brilhante

    // Cores de Fundo (para erros)
    const std::string BG_RED = "\033[41m";
}

#endif // COLOR_H