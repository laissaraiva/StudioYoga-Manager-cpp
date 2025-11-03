#include <iostream>
#include <stdexcept>
#include "services/StudioManager.h"

int main() {
    try {
        // 1. Cria o objeto principal que gerencia tudo
        StudioManager meuStudio;

        // 2. Chama o loop principal do menu (o "run")
        // A função "run()" lá dentro do StudioManager é que
        // contém o "do-while" e o "switch-case" do seu exemplo.
        meuStudio.run();

    } catch (const std.exception& e) {
        std::cerr << "Ocorreu um erro fatal no sistema: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Ocorreu um erro desconhecido e fatal." << std::endl;
        return 1;
    }

    return 0; // O programa termina quando o usuário sai do menu
}