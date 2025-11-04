#include <iostream>
#include <stdexcept>
#include "services/StudioManager.h" // Inclui a classe de serviço principal

// Arquivo principal do projeto;
int main() {
    try {
        //  Cria o objeto principal que gerencia tudo
        StudioManager meuStudio; //Instancia o objeto da classe de serviço

        //  Chama o loop principal do menu
        // A função "run()" contém o loop "do-while" e o "switch-case".
        meuStudio.run();

    } catch (const std::exception& e) {
        // Captura um erro fatal e inesperado
        std::cerr << "Ocorreu um erro fatal no sistema: " << e.what() << std::endl;
        return 1; 
    } catch (...) {
        // Captura qualquer outro erro desconhecido
        std::cerr << "Ocorreu um erro desconhecido e fatal." << std::endl;
        return 1;
    }

    return 0; 
}