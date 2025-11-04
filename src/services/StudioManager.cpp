#include "services/StudioManager.h"
#include "models/HotYoga.h"
#include "models/YogaPets.h"
#include "models/YogaFlow.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm> // Necessário para std::max

// --- Construtor e Destrutor (MODIFICADOS) ---

StudioManager::StudioManager()
    : proximoIdPessoa(1), proximoIdAula(100), proximoIdPlano(1000) {
    // AGORA o construtor delega o carregamento para o DataManager
    std::cout << "Iniciando Studio Manager..." << std::endl;
    dataManager.carregarDados(planos, instrutores, praticantes, aulas,
                              proximoIdPessoa, proximoIdAula, proximoIdPlano);
    std::cout << "Sistema pronto." << std::endl;
}

StudioManager::~StudioManager() {
    std::cout << "Encerrando Studio Manager..." << std::endl;

    // 1. Salva tudo antes de sair, delegando ao DataManager
    dataManager.salvarDados(planos, instrutores, praticantes, aulas);

    // 2. Deleta cada ponteiro de Aula* que foi criado com 'new'
    std::cout << "Limpando memoria..." << std::endl;
    for (Aula* aula : aulas) {
        delete aula;
    }
    aulas.clear(); // Limpa o vetor de ponteiros
}

// --- Ponto de Entrada do Menu ---

void StudioManager::run() {
    int escolha = -1;
    do {
        std::cout << "\n========= YOGA STUDIO MANAGEMENT (v2.0) =========\n";
        std::cout << "1. Cadastrar Praticante\n";
        std::cout << "2. Cadastrar Instrutor\n";
        std::cout << "3. Cadastrar Plano\n";
        std::cout << "4. Cadastrar Nova Aula (Hot, Pets, Flow)\n"; // (Texto já estava ok)
        std::cout << "------------------------------------------\n";
        std::cout << "5. Matricular Praticante em Aula\n";
        std::cout << "------------------------------------------\n";
        std::cout << "6. Listar Praticantes\n";
        std::cout << "7. Listar Instrutores\n";
        std::cout << "8. Listar Planos\n";
        std::cout << "9. Listar Aulas (com detalhes)\n";
        std::cout << "------------------------------------------\n";
        std::cout << "0. Sair\n";
        std::cout << "==========================================\n";
        std::cout << "Digite sua escolha: ";

        if (!(std::cin >> escolha)) {
            std::cout << "Opcao invalida. Por favor, digite um numero.\n";
            std::cin.clear();
            limparBufferEntrada();
            continue;
        }

        limparBufferEntrada(); // Limpa o '\n' deixado pelo cin

        try {
            switch (escolha) {
                case 1: cadastrarPraticante(); break;
                case 2: cadastrarInstrutor(); break;
                case 3: cadastrarPlano(); break;
                case 4: cadastrarAula(); break;
                case 5: matricularPraticanteEmAula(); break;
                case 6: listarPraticantes(); break;
                case 7: listarInstrutores(); break;
                case 8: listarPlanos(); break;
                case 9: listarAulas(); break;
                case 0: std::cout << "Saindo do sistema. Ate logo!\n"; break;
                default: std::cout << "Opcao invalida. Tente novamente.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }

    } while (escolha != 0);
}


// --- Métodos de Lógica do Menu (Implementação) ---
// (Estas funções permanecem IGUAIS, pois já manipulam os vetores em memória)

void StudioManager::cadastrarPraticante() {
    std::string nome, email;
    int idPlano;
    std::cout << "\n--- Cadastro de Praticante ---\n";
    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    std::cout << "Email: ";
    std::getline(std::cin, email);

    listarPlanos();
    std::cout << "Digite o ID do Plano: ";
    std::cin >> idPlano;
    limparBufferEntrada();

    if (findPlanoById(idPlano) == nullptr) {
        std::cout << "Erro: Plano nao encontrado.\n";
        return;
    }

    int novoId = proximoIdPessoa++;
    // Assumindo construtor: Praticante(id, nome, email, idPlano)
    praticantes.emplace_back(novoId, nome, email, idPlano);
    std::cout << "Praticante '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n";
}

void StudioManager::cadastrarInstrutor() {
    std::string nome, email, especialidade;
    std::cout << "\n--- Cadastro de Instrutor ---\n";
    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    std::cout << "Email: ";
    std::getline(std::cin, email);
    std::cout << "Especialidade: ";
    std::getline(std::cin, especialidade);

    int novoId = proximoIdPessoa++;
    // Assumindo construtor: Instrutor(id, nome, email, especialidade)
    instrutores.emplace_back(novoId, nome, email, especialidade);
    std::cout << "Instrutor '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n";
}

void StudioManager::cadastrarPlano() {
    std::string nome;
    double preco;
    std::cout << "\n--- Cadastro de Plano ---\n";
    std::cout << "Nome (Ex: Mensal, Trimestra): ";
    std::getline(std::cin, nome);
    std::cout << "Preco (Ex: 99.90): ";
    std::cin >> preco;
    limparBufferEntrada();

    int novoId = proximoIdPlano++;
    // Assumindo construtor: Plano(id, nome, preco)
    planos.emplace_back(novoId, nome, preco);
    std::cout << "Plano '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n";
}

void StudioManager::cadastrarAula() {
    std::cout << "\n--- Cadastro de Nova Aula ---\n";
    if (instrutores.empty()) {
        std::cout << "Erro: Cadastre um instrutor primeiro.\n";
        return;
    }

    int tipoAula = selecionarTipoAulaMenu();
    if (tipoAula == 0) return;

    std::string horario;
    int limiteAlunos;
    std::cout << "Horario (Ex: Segunda 18:00): ";
    std::getline(std::cin, horario);

    std::cout << "Limite de Alunos: ";
    std::cin >> limiteAlunos;
    limparBufferEntrada();

    listarInstrutores();
    std::cout << "Digite o ID do Instrutor: ";
    int idInstrutor;
    std::cin >> idInstrutor;
    limparBufferEntrada();

    Instrutor* instrutor = findInstrutorById(idInstrutor);
    if (instrutor == nullptr) {
        std::cout << "Erro: Instrutor nao encontrado.\n";
        return;
    }

    Aula* novaAula = nullptr;
    int novoId = proximoIdAula++;

    switch (tipoAula) {
        case 1: { // Hot Yoga
            std::cout << "Digite a Temperatura da Sala (em C): ";
            int temp;
            std::cin >> temp;
            limparBufferEntrada();
            // Assumindo construtor: HotYoga(id, horario, idInstrutor, limite, temp)
            novaAula = new HotYoga(novoId, horario, idInstrutor, limiteAlunos, temp);
            break;
        }
        case 2: { // Yoga com Pets
            std::cout << "Tipo de Pet Permitido (Ex: Gatos, Cachorros dócil): ";
            std::string tipoPet;
            std::getline(std::cin, tipoPet);
            // Assumindo construtor: YogaPets(id, horario, idInstrutor, limite, tipoPet)
            novaAula = new YogaPets(novoId, horario, idInstrutor, limiteAlunos, tipoPet);
            break;
        }
        case 3: { // Yoga Flow
            // Esta aula não pede dados extras, então criamos direto
            novaAula = new YogaFlow(novoId, horario, idInstrutor, limiteAlunos);
            std::cout << "Aula de Yoga Flow cadastrada.\n";
            break;
        }
        default:
            std::cout << "Erro: Tipo de aula invalido.\n";
            return;
    }

    aulas.push_back(novaAula);
    instrutor->adicionarAula(novoId);

    std::cout << "Aula (ID: " << novoId << ") cadastrada com sucesso!\n";
}

void StudioManager::matricularPraticanteEmAula() {
    std::cout << "\n--- Matricular Praticante em Aula ---\n";
    if (praticantes.empty()) {
        std::cout << "Erro: Nenhum praticante cadastrado.\n"; return;
    }
    if (aulas.empty()) {
        std::cout << "Erro: Nenhuma aula cadastrada.\n"; return;
    }

    listarPraticantes();
    std::cout << "Digite o ID do Praticante: ";
    int idPraticante;
    std::cin >> idPraticante;
    limparBufferEntrada();
    Praticante* praticante = findPraticanteById(idPraticante);
    if (praticante == nullptr) {
        std::cout << "Erro: Praticante nao encontrado.\n"; return;
    }

    listarAulas();
    std::cout << "Digite o ID da Aula: ";
    int idAula;
    std::cin >> idAula;
    limparBufferEntrada();
    Aula* aula = findAulaById(idAula);
    if (aula == nullptr) {
        std::cout << "Erro: Aula nao encontrada.\n"; return;
    }

    if (aula->inscreverPraticante(praticante->getId())) {
        praticante->inscreverEmAula(aula->getId());
        std::cout << "Matricula de '" << praticante->getNome() << "' realizada com sucesso!\n";
    } else {
        std::cout << "Nao foi possivel matricular. A aula pode estar lotada.\n";
    }
}

// --- Métodos de Listagem ---
// (Estas funções permanecem IGUAIS)

void StudioManager::listarPraticantes() {
    std::cout << "\n--- Lista de Praticantes ---\n";
    if (praticantes.empty()) {
        std::cout << "Nenhum praticante cadastrado.\n"; return;
    }
    for (const auto& p : praticantes) {
        p.exibirDetalhes(); // Assumindo que Praticante tem exibirDetalhes()
    }
}

void StudioManager::listarInstrutores() {
    std::cout << "\n--- Lista de Instrutores ---\n";
    if (instrutores.empty()) {
        std::cout << "Nenhum instrutor cadastrado.\n"; return;
    }
    for (const auto& i : instrutores) {
        i.exibirDetalhes(); // Assumindo que Instrutor tem exibirDetalhes()
    }
}

void StudioManager::listarPlanos() {
    std::cout << "\n--- Lista de Planos ---\n";
    if (planos.empty()) {
        std::cout << "Nenhum plano cadastrado.\n"; return;
    }
    for (const auto& p : planos) {
        p.exibirDetalhes(); // Assumindo que Plano tem exibirDetalhes()
    }
}

void StudioManager::listarAulas() {
    std::cout << "\n--- Lista de Aulas --- (Total: " << aulas.size() << ")\n";
    if (aulas.empty()) {
        std::cout << "Nenhuma aula cadastrada.\n"; return;
    }
    for (const Aula* aulaPtr : aulas) {
        aulaPtr->exibirDetalhes(); // Polimorfismo
        std::cout << "---------------------------------\n";
    }
}


// --- Métodos Auxiliares (Finders e Limpeza) ---
// (Estas funções permanecem IGUAIS, pois a UI precisa delas)

// --- 4. FUNÇÃO ATUALIZADA ---
int StudioManager::selecionarTipoAulaMenu() {
    int escolha = 0;
    while (true) {
        std::cout << "  Selecione o Tipo de Aula:\n";
        std::cout << "  1. Hot Yoga\n";
        std::cout << "  2. Yoga com Pets\n";
        std::cout << "  3. Yoga Flow\n"; // <--- ADICIONADO
        std::cout << "  0. Cancelar\n";
        std::cout << "  > ";
        std::cin >> escolha;

        if (std::cin.fail()) {
            std::cin.clear();
            limparBufferEntrada();
            std::cout << "Entrada invalida. Tente novamente.\n";
        } else {
            limparBufferEntrada();
            if (escolha >= 0 && escolha <= 3) { // <--- LIMITE ATUALIZADO DE 2 PARA 3
                return escolha;
            }
            std::cout << "Opção invalida. Tente novamente.\n";
        }
    }
}

void StudioManager::limparBufferEntrada() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Finders (Iteram nos vetores para encontrar por ID)
Praticante* StudioManager::findPraticanteById(int id) {
    for (auto& p : praticantes) {
        if (p.getId() == id) return &p;
    }
    return nullptr;
}

Instrutor* StudioManager::findInstrutorById(int id) {
    for (auto& i : instrutores) {
        if (i.getId() == id) return &i;
    }
    return nullptr;
}

Aula* StudioManager::findAulaById(int id) {
    for (auto* a : aulas) { // Note o ponteiro
        if (a->getId() == id) return a;
    }
    return nullptr;
}

Plano* StudioManager::findPlanoById(int id) {
    for (auto& p : planos) {
        if (p.getId() == id) return &p;
    }
    return nullptr;
}