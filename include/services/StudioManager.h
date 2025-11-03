#include "services/StudioManager.h"
#include "models/HotYoga.h"
#include "models/YogaPets.h" 
#include <iostream>
#include <string>
#include <limits>

// Inclui o serviço de dados e os nomes dos arquivos
#include "data/DataManager.h"
#include <algorithm> // Para std::max_element

// Nomes dos arquivos de persistência
const std::string ARQ_PRATICANTES = "praticantes.txt";
const std::string ARQ_INSTRUTORES = "instrutores.txt";
const std::string ARQ_PLANOS = "planos.txt";
// const std::string ARQ_AULAS = "aulas.txt"; // Salvar aulas polimórficas é complexo


// --- Funções Auxiliares (privadas) para encontrar IDs ---
// (Você precisará dos getters getId() nas suas classes para isto funcionar)
int encontrarProximoId(const std::vector<Praticante>& v) {
    if (v.empty()) return 1;
    auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Praticante& a, const Praticante& b) {
            return a.getId() < b.getId();
    });
    return maxIt->getId() + 1;
}
int encontrarProximoId(const std::vector<Instrutor>& v) {
     if (v.empty()) return 1;
     auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Instrutor& a, const Instrutor& b) {
            return a.getId() < b.getId();
    });
    return maxIt->getId() + 1;
}
int encontrarProximoId(const std::vector<Plano>& v) {
     if (v.empty()) return 1;
     auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Plano& a, const Plano& b) {
            return a.getId() < b.getId();
    });
    return maxIt->getId() + 1;
}
int encontrarProximoId(const std::vector<Aula*>& v) {
     if (v.empty()) return 100; // Começa em 100
     auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Aula* a, const Aula* b) {
            return a->getId() < b->getId();
    });
    return (*maxIt)->getId() + 1;
}


// --- Construtor e Destrutor ---

StudioManager::StudioManager() {
    std::cout << "Iniciando Studio Manager..." << std::endl;
    
    // Carrega os dados dos arquivos .txt para os vetores
    std::cout << "Carregando dados dos arquivos .txt..." << std::endl;
    this->planos = DataManager::carregarPlanos(ARQ_PLANOS);
    this->instrutores = DataManager::carregarInstrutores(ARQ_INSTRUTORES);
    this->praticantes = DataManager::carregarPraticantes(ARQ_PRATICANTES);
    // this->aulas = DataManager::carregarAulas(ARQ_AULAS); // (Implementação futura)

    // Inicializa os contadores de ID de forma segura
    this->proximoIdPlano = encontrarProximoId(this->planos);
    // (IDs de Praticante e Instrutor podem compartilhar o mesmo contador "proximoIdPessoa")
    int proxPraticante = encontrarProximoId(this->praticantes);
    int proxInstrutor = encontrarProximoId(this->instrutores);
    this->proximoIdPessoa = std::max(proxPraticante, proxInstrutor);
    
    this->proximoIdAula = encontrarProximoId(this->aulas);
    
    std::cout << planos.size() << " planos, " << instrutores.size() << " instrutores, " << praticantes.size() << " praticantes carregados.\n";
}

StudioManager::~StudioManager() {
    std::cout << "Encerrando Studio Manager..." << std::endl;
    
    // Salva os dados dos vetores em memória de volta para os arquivos .txt
    std::cout << "Salvando dados em arquivos .txt..." << std::endl;
    DataManager::salvarPlanos(this->planos, ARQ_PLANOS);
    DataManager::salvarInstrutores(this->instrutores, ARQ_INSTRUTORES);
    DataManager::salvarPraticantes(this->praticantes, ARQ_PRATICANTES);
    // DataManager::salvarAulas(this->aulas, ARQ_AULAS); // (Implementação futura)

    // Destrutor OBRIGATÓRIO para limpar a memória
    std::cout << "Limpando ponteiros de aulas..." << std::endl;
    for (Aula* aula : aulas) {
        delete aula;
    }
}

// --- Ponto de Entrada do Menu ---

void StudioManager::run() {
    int escolha = -1;
    do {
        std::cout << "\n========= YOGA STUDIO MANAGEMENT (v2.0) =========\n";
        std::cout << "1. Cadastrar Praticante\n";
        std::cout << "2. Cadastrar Instrutor\n";
        std::cout << "3. Cadastrar Plano\n";
        std::cout << "4. Cadastrar Nova Aula (Hot, Pets, etc.)\n";
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
            std::cout << "Opção inválida. Por favor, digite um número.\n";
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
                case 0: std::cout << "Saindo do sistema. Até logo!\n"; break;
                default: std::cout << "Opção inválida. Tente novamente.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }

    } while (escolha != 0);
}


// --- Métodos de Lógica do Menu (Implementação) ---

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

    // Validação (simples)
    if (findPlanoById(idPlano) == nullptr) {
        std::cout << "Erro: Plano não encontrado.\n";
        return;
    }

    int novoId = proximoIdPessoa++;
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
    instrutores.emplace_back(novoId, nome, email, especialidade);
    std::cout << "Instrutor '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n";
}

void StudioManager::cadastrarPlano() {
    std::string nome;
    double preco;
    std::cout << "\n--- Cadastro de Plano ---\n";
    std::cout << "Nome (Ex: Mensal, Trimestral): ";
    std::getline(std::cin, nome);
    std::cout << "Preço (Ex: 99.90): ";
    std::cin >> preco;
    limparBufferEntrada();

    int novoId = proximoIdPlano++;
    planos.emplace_back(novoId, nome, preco);
    std::cout << "Plano '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n";
}

void StudioManager::cadastrarAula() {
    std::cout << "\n--- Cadastro de Nova Aula ---\n";
    if (instrutores.empty()) {
        std::cout << "Erro: Cadastre um instrutor primeiro.\n";
        return;
    }

    // 1. Seleciona o Tipo (agora usando Herança)
    int tipoAula = selecionarTipoAulaMenu();
    if (tipoAula == 0) return; // Usuário cancelou

    // 2. Coleta dados comuns da "Mãe" Aula
    std::string horario;
    int limiteAlunos;
    std::cout << "Horário (Ex: Seg 18:00): ";
    std::getline(std::cin, horario);

    std::cout << "Limite de Alunos: ";
    std::cin >> limiteAlunos;
    limparBufferEntrada();

    // 3. Seleciona Instrutor
    listarInstrutores();
    std::cout << "Digite o ID do Instrutor: ";
    int idInstrutor;
    std::cin >> idInstrutor;
    limparBufferEntrada();

    Instrutor* instrutor = findInstrutorById(idInstrutor);
    if (instrutor == nullptr) {
        std::cout << "Erro: Instrutor não encontrado.\n";
        return;
    }

    // 4. Cria a Aula específica (POLIMORFISMO)
    Aula* novaAula = nullptr;
    int novoId = proximoIdAula++;

    switch (tipoAula) {
        case 1: { // Hot Yoga
            std::cout << "Digite a Temperatura da Sala (em °C): ";
            int temp;
            std::cin >> temp;
            limparBufferEntrada();
            novaAula = new HotYoga(novoId, horario, idInstrutor, limiteAlunos, temp);
            break;
        }
        case 2: { // Yoga com Pets
            std::cout << "Tipo de Pet Permitido (Ex: Gatos, Cachorros dócil): ";
            std::string tipoPet;
            std::getline(std::cin, tipoPet);
            novaAula = new YogaPets(novoId, horario, idInstrutor, limiteAlunos, tipoPet);
            break;
        }
        // (Adicione 'case 3:' para uma 'YogaNormal.h' se você a criar)
        default:
            std::cout << "Erro: Tipo de aula inválido.\n";
            return;
    }

    // 5. Salva a aula (o ponteiro) no vetor
    aulas.push_back(novaAula);
    instrutor->adicionarAula(novoId); // Linka a aula ao instrutor

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

    // 1. Selecionar Praticante
    listarPraticantes();
    std::cout << "Digite o ID do Praticante: ";
    int idPraticante;
    std::cin >> idPraticante;
    limparBufferEntrada();
    Praticante* praticante = findPraticanteById(idPraticante);
    if (praticante == nullptr) {
        std::cout << "Erro: Praticante não encontrado.\n"; return;
    }

    // 2. Selecionar Aula
    listarAulas();
    std::cout << "Digite o ID da Aula: ";
    int idAula;
    std::cin >> idAula;
    limparBufferEntrada();
    Aula* aula = findAulaById(idAula);
    if (aula == nullptr) {
        std::cout << "Erro: Aula não encontrada.\n"; return;
    }

    // 3. Realizar a Matrícula (usando a lógica de negócios da Aula)
    if (aula->inscreverPraticante(praticante->getId())) {
        praticante->inscreverEmAula(aula->getId()); // Link bidirecional
        std::cout << "Matrícula de '" << praticante->getNome() << "' realizada com sucesso!\n";
    } else {
        std::cout << "Não foi possível matricular. A aula pode estar lotada.\n";
    }
}

// --- Métodos de Listagem ---

void StudioManager::listarPraticantes() {
    std::cout << "\n--- Lista de Praticantes ---\n";
    if (praticantes.empty()) {
        std::cout << "Nenhum praticante cadastrado.\n"; return;
    }
    for (const auto& p : praticantes) {
        p.exibirDetalhes();
    }
}

void StudioManager::listarInstrutores() {
    std::cout << "\n--- Lista de Instrutores ---\n";
    if (instrutores.empty()) {
        std::cout << "Nenhum instrutor cadastrado.\n"; return;
    }
    for (const auto& i : instrutores) {
        i.exibirDetalhes();
    }
}

void StudioManager::listarPlanos() {
    std::cout << "\n--- Lista de Planos ---\n";
    if (planos.empty()) {
        std::cout << "Nenhum plano cadastrado.\n"; return;
    }
    for (const auto& p : planos) {
        p.exibirDetalhes();
    }
}

void StudioManager::listarAulas() {
    std::cout << "\n--- Lista de Aulas --- (Total: " << aulas.size() << ")\n";
    if (aulas.empty()) {
        std::cout << "Nenhuma aula cadastrada.\n"; return;
    }
    for (const Aula* aulaPtr : aulas) {
        // POLIMORFISMO em ação:
        // O C++ chama automaticamente o 'exibirDetalhes'
        // da classe filha correta (HotYoga, YogaPets, etc.)
        aulaPtr->exibirDetalhes();
        std::cout << "---------------------------------\n";
    }
}

// --- Métodos Auxiliares (Finders e Limpeza) ---

int StudioManager::selecionarTipoAulaMenu() {
    int escolha = 0;
    while (true) {
        std::cout << "  Selecione o Tipo de Aula:\n";
        std::cout << "  1. Hot Yoga\n";
        std::cout << "  2. Yoga com Pets\n";
        // (Adicione '3. Yoga Normal' se criar a classe)
        std::cout << "  0. Cancelar\n";
        std::cout << "  > ";
        std::cin >> escolha;

        if (std::cin.fail()) {
            std::cin.clear();
            limparBufferEntrada();
            std::cout << "Entrada inválida. Tente novamente.\n";
        } else {
            limparBufferEntrada();
            if (escolha >= 0 && escolha <= 2) { // Ajuste este '2' se adicionar mais tipos
                return escolha;
            }
            std::cout << "Opção inválida. Tente novamente.\n";
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