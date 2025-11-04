#include "services/StudioManager.h"
#include "models/HotYoga.h"   // Inclui a classe filha HotYoga
#include "models/YogaPets.h"  // Inclui a classe filha YogaPets
#include <iostream>
#include <string>
#include <limits>
#include "data/DataManager.h"   // Inclui o serviço de persistência
#include <algorithm>           // Para std::max_element (cálculo de IDs)
#include "validator/Validator.h" // Inclui o serviço de validação

// Nomes dos arquivos de persistência (constantes)
const std::string ARQ_PRATICANTES = "praticantes.txt";
const std::string ARQ_INSTRUTORES = "instrutores.txt";
const std::string ARQ_PLANOS = "planos.txt";
// const std::string ARQ_AULAS = "aulas.txt"; // Salvar aulas é mais complexo

// --- Funções Auxiliares (privadas) para encontrar IDs ---
// Encontra o maior ID em um vetor de Praticantes e retorna o próximo ID
int encontrarProximoId(const std::vector<Praticante>& v) {
    if (v.empty()) return 1;
    auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Praticante& a, const Praticante& b) {
            return a.getId() < b.getId();
    });
    return maxIt->getId() + 1;
}
// Encontra o maior ID em um vetor de Instrutores e retorna o próximo ID
int encontrarProximoId(const std::vector<Instrutor>& v) {
     if (v.empty()) return 1;
     auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Instrutor& a, const Instrutor& b) {
            return a.getId() < b.getId();
    });
    return maxIt->getId() + 1;
}
// Encontra o maior ID em um vetor de Planos e retorna o próximo ID
int encontrarProximoId(const std::vector<Plano>& v) {
     if (v.empty()) return 1;
     auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Plano& a, const Plano& b) {
            return a.getId() < b.getId();
    });
    return maxIt->getId() + 1;
}
// Encontra o maior ID em um vetor de Aulas (ponteiros) e retorna o próximo ID
int encontrarProximoId(const std::vector<Aula*>& v) {
     if (v.empty()) return 100; // Define 100 como o ID inicial para aulas
     auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Aula* a, const Aula* b) {
            return a->getId() < b->getId();
    });
    return (*maxIt)->getId() + 1;
}

// --- Construtor e Destrutor ---

StudioManager::StudioManager() {
    std::cout << "Iniciando Studio Manager..." << std::endl;
    
    // Carrega os dados dos arquivos .txt para os vetores em memória
    std::cout << "Carregando dados dos arquivos .txt..." << std::endl;
    this->planos = DataManager::carregarPlanos(ARQ_PLANOS);
    this->instrutores = DataManager::carregarInstrutores(ARQ_INSTRUTORES);
    this->praticantes = DataManager::carregarPraticantes(ARQ_PRATICANTES);
    // this->aulas = DataManager::carregarAulas(ARQ_AULAS); // Implementação futura

    // Inicializa os contadores de ID de forma segura, com base nos dados carregados
    this->proximoIdPlano = encontrarProximoId(this->planos);
    int proxPraticante = encontrarProximoId(this->praticantes);
    int proxInstrutor = encontrarProximoId(this->instrutores);
    this->proximoIdPessoa = std::max(proxPraticante, proxInstrutor); // Usa o maior ID entre pessoas
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
    // DataManager::salvarAulas(this->aulas, ARQ_AULAS); // Implementação futura

    // Destrutor OBRIGATÓRIO para limpar a memória dos ponteiros
    std::cout << "Limpando ponteiros de aulas..." << std::endl;
    for (Aula* aula : aulas) {
        delete aula; // Libera a memória alocada com 'new' para cada aula
    }
}

// --- Ponto de Entrada do Menu ---

void StudioManager::run() {
    int escolha = -1;
    do { // Loop principal do menu
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

        if (!(std::cin >> escolha)) { // Verifica se a entrada é um número
            std::cout << "Opção inválida. Por favor, digite um número.\n";
            std::cin.clear(); // Limpa o estado de erro do cin
            limparBufferEntrada(); // Limpa o buffer
            continue; // Volta ao início do loop
        }

        limparBufferEntrada(); // Limpa o '\n' deixado pelo cin

        try { // Bloco try-catch para capturar exceções
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

    } while (escolha != 0); // Repete até o usuário escolher 0
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

    // Validação da entrada usando o Validator
    if (!Validator::isStringValida(nome)) {
        std::cout << "Erro: O nome nao pode estar vazio. Cadastro cancelado.\n";
        return; // Sai da função
    }
    if (!Validator::isEmailValido(email)) {
        std::cout << "Erro: O formato do email e invalido (ex: nome@dominio.com). Cadastro cancelado.\n";
        return; // Sai da função
    }

    listarPlanos(); // Mostra os planos disponíveis
    std::cout << "Digite o ID do Plano: ";
    std::cin >> idPlano;
    limparBufferEntrada();

    // Validação da lógica de negócio
    if (findPlanoById(idPlano) == nullptr) {
        std::cout << "Erro: Plano não encontrado.\n";
        return;
    }

    int novoId = proximoIdPessoa++; // Pega o próximo ID disponível
    praticantes.emplace_back(novoId, nome, email, idPlano); // Cria e adiciona o praticante ao vetor
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

    // Validação da entrada
    if (!Validator::isStringValida(nome) || !Validator::isStringValida(especialidade)) {
        std::cout << "Erro: Nome e Especialidade nao podem estar vazios. Cadastro cancelado.\n";
        return;
    }
    if (!Validator::isEmailValido(email)) {
        std::cout << "Erro: O formato do email e invalido. Cadastro cancelado.\n";
        return;
    }

    int novoId = proximoIdPessoa++;
    instrutores.emplace_back(novoId, nome, email, especialidade); // Cria e adiciona o instrutor
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

    // Validação da entrada
    if (!Validator::isStringValida(nome)) {
        std::cout << "Erro: O nome do plano nao pode estar vazio. Cadastro cancelado.\n";
        return;
    }
    if (preco <= 0) {
        std::cout << "Erro: O preco deve ser um valor positivo. Cadastro cancelado.\n";
        return;
    }

    int novoId = proximoIdPlano++;
    planos.emplace_back(novoId, nome, preco); // Cria e adiciona o plano
    std::cout << "Plano '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n";
}

void StudioManager::cadastrarAula() {
    std::cout << "\n--- Cadastro de Nova Aula ---\n";
    if (instrutores.empty()) {
        std::cout << "Erro: Cadastre um instrutor primeiro.\n";
        return;
    }

    //Seleciona o Tipo (Polimorfismo)
    int tipoAula = selecionarTipoAulaMenu();
    if (tipoAula == 0) return; // Usuário cancelou

    //  Coleta dados comuns da "Mãe" Aula
    std::string horario;
    int limiteAlunos;
    std::cout << "Horário (Ex: Seg 18:00): ";
    std::getline(std::cin, horario);
    std::cout << "Limite de Alunos: ";
    std::cin >> limiteAlunos;
    limparBufferEntrada();

    // Validação da entrada
    if (!Validator::isStringValida(horario)) {
        std::cout << "Erro: O horario nao pode estar vazio. Cadastro cancelado.\n";
        return;
    }
    if (limiteAlunos <= 0) {
        std::cout << "Erro: O limite de alunos deve ser positivo. Cadastro cancelado.\n";
        return;
    }

    // Seleciona Instrutor
    listarInstrutores();
    std::cout << "Digite o ID do Instrutor: ";
    int idInstrutor;
    std::cin >> idInstrutor;
    limparBufferEntrada();

    Instrutor* instrutor = findInstrutorById(idInstrutor); // Busca o instrutor
    if (instrutor == nullptr) {
        std::cout << "Erro: Instrutor não encontrado.\n";
        return;
    }

    // Cria a Aula específica (POLIMORFISMO)
    Aula* novaAula = nullptr; // Ponteiro da classe base
    int novoId = proximoIdAula++;

    switch (tipoAula) {
        case 1: { // Hot Yoga
            std::cout << "Digite a Temperatura da Sala (em °C): ";
            int temp;
            std::cin >> temp;
            limparBufferEntrada();
            // Cria um objeto HotYoga, mas armazena em um ponteiro Aula*
            novaAula = new HotYoga(novoId, horario, idInstrutor, limiteAlunos, temp);
            break;
        }
        case 2: { // Yoga com Pets
            std::cout << "Tipo de Pet Permitido (Ex: Gatos, Cachorros dócil): ";
            std::string tipoPet;
            std::getline(std::cin, tipoPet);
             if (!Validator::isStringValida(tipoPet)) {
                std::cout << "Erro: O tipo de pet nao pode estar vazio. Cadastro cancelado.\n";
                proximoIdAula--; // Reverte o incremento do ID
                return;
            }
            // Cria um objeto YogaPets, mas armazena em um ponteiro Aula*
            novaAula = new YogaPets(novoId, horario, idInstrutor, limiteAlunos, tipoPet);
            break;
        }
        default:
            std::cout << "Erro: Tipo de aula inválido.\n";
            proximoIdAula--; // Reverte o incremento do ID
            return;
    }

    //  Salva a aula (o ponteiro) no vetor
    aulas.push_back(novaAula);
    instrutor->adicionarAula(novoId); // Linka a aula ao instrutor (lógica de negócio)

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

    //Selecionar Praticante
    listarPraticantes();
    std::cout << "Digite o ID do Praticante: ";
    int idPraticante;
    std::cin >> idPraticante;
    limparBufferEntrada();
    Praticante* praticante = findPraticanteById(idPraticante); // Busca o praticante
    if (praticante == nullptr) {
        std::cout << "Erro: Praticante não encontrado.\n"; return;
    }

    // Selecionar Aula
    listarAulas();
    std::cout << "Digite o ID da Aula: ";
    int idAula;
    std::cin >> idAula;
    limparBufferEntrada();
    Aula* aula = findAulaById(idAula); // Busca a aula
    if (aula == nullptr) {
        std::cout << "Erro: Aula não encontrada.\n"; return;
    }

    //  Realizar a Matrícula 
    if (aula->inscreverPraticante(praticante->getId())) {
        praticante->inscreverEmAula(aula->getId()); // Link bidirecional
        std::cout << "Matrícula de '" << praticante->getNome() << "' realizada com sucesso!\n";
    } else {
        std::cout << "Não foi possível matricular. A aula pode estar lotada.\n";
    }
}

// Métodos da Listagem

void StudioManager::listarPraticantes() {
    std::cout << "\n--- Lista de Praticantes ---\n";
    if (praticantes.empty()) {
        std::cout << "Nenhum praticante cadastrado.\n"; return;
    }
    for (const auto& p : praticantes) {
        p.exibirDetalhes(); // Chama o método de exibição de cada praticante
    }
}

void StudioManager::listarInstrutores() {
    std::cout << "\n--- Lista de Instrutores ---\n";
    if (instrutores.empty()) {
        std::cout << "Nenhum instrutor cadastrado.\n"; return;
    }
    for (const auto& i : instrutores) {
        i.exibirDetalhes(); // Chama o método de exibição de cada instrutor
    }
}

void StudioManager::listarPlanos() {
    std::cout << "\n--- Lista de Planos ---\n";
    if (planos.empty()) {
        std::cout << "Nenhum plano cadastrado.\n"; return;
    }
    for (const auto& p : planos) {
        p.exibirDetalhes(); // Chama o método de exibição de cada plano
    }
}

void StudioManager::listarAulas() {
    std::cout << "\n--- Lista de Aulas --- (Total: " << aulas.size() << ")\n";
    if (aulas.empty()) {
        std::cout << "Nenhuma aula cadastrada.\n"; return;
    }
    for (const Aula* aulaPtr : aulas) {
        
        //para o poliformis:  O C++ chama automaticamente o 'exibirDetalhes'
        // da classe filha correta (como HotYoga e  YogaPets)
        aulaPtr->exibirDetalhes();
        std::cout << "---------------------------------\n";
    }
}

// Métodos Auxiliares 

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

        if (std::cin.fail()) { // Se a entrada não for um número
            std::cin.clear();
            limparBufferEntrada();
            std::cout << "Entrada inválida. Tente novamente.\n";
        } else {
            limparBufferEntrada();
            if (escolha >= 0 && escolha <= 2) { // Valida a faixa de opções
                return escolha;
            }
            std::cout << "Opção inválida. Tente novamente.\n";
        }
    }
}

void StudioManager::limparBufferEntrada() {
    // Limpa o buffer de entrada do std::cin para evitar bugs com getline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Finders (Iteram nos vetores para encontrar por ID)
Praticante* StudioManager::findPraticanteById(int id) {
    for (auto& p : praticantes) { // Itera sobre o vetor de praticantes
        if (p.getId() == id) return &p; // Retorna o endereço do praticante encontrado
    }
    return nullptr; // Retorna nulo se não encontrar
}

Instrutor* StudioManager::findInstrutorById(int id) {
    for (auto& i : instrutores) { // Itera sobre o vetor de instrutores
        if (i.getId() == id) return &i; // Retorna o endereço do instrutor encontrado
    }
    return nullptr; // Retorna nulo se não encontrar
}

Aula* StudioManager::findAulaById(int id) {
    for (auto* a : aulas) { // Itera sobre o vetor de ponteiros de aula
        if (a->getId() == id) return a; // Retorna o ponteiro da aula encontrada
    }
    return nullptr; // Retorna nulo se não encontrar
}

Plano* StudioManager::findPlanoById(int id) {
    for (auto& p : planos) { // Itera sobre o vetor de planos
        if (p.getId() == id) return &p; // Retorna o endereço do plano encontrado
    }
    return nullptr; // Retorna nulo se não encontrar
}