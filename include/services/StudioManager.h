#include "services/StudioManager.h"
#include "models/HotYoga.h"   // Inclui a classe filha HotYoga
#include "models/YogaPets.h"  // Inclui a classe filha YogaPets
#include <iostream>
#include <string>
#include <limits>
#include "data/DataManager.h"   // Inclui o serviço de persistência
#include <algorithm>           // Necessário para std::max_element
#include "validator/Validator.h" // Inclui o serviço de validação

// Define os nomes dos arquivos .txt para salvar os dados.
const std::string ARQ_PRATICANTES = "praticantes.txt";
const std::string ARQ_INSTRUTORES = "instrutores.txt";
const std::string ARQ_PLANOS = "planos.txt";
// const std::string ARQ_AULAS = "aulas.txt"; // Salvar aulas polimórficas é mais complexo

// Encontra o maior ID em um vetor de Praticantes e retorna o próximo ID.
int encontrarProximoId(const std::vector<Praticante>& v) {
    if (v.empty()) return 1;
    auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Praticante& a, const Praticante& b) {
            return a.getId() < b.getId();
    });
    return maxIt->getId() + 1;
}
// Encontra o maior ID em um vetor de Instrutores e retorna o próximo ID.
int encontrarProximoId(const std::vector<Instrutor>& v) {
     if (v.empty()) return 1;
     auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Instrutor& a, const Instrutor& b) {
            return a.getId() < b.getId();
    });
    return maxIt->getId() + 1;
}
// Encontra o maior ID em um vetor de Planos e retorna o próximo ID.
int encontrarProximoId(const std::vector<Plano>& v) {
     if (v.empty()) return 1;
     auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Plano& a, const Plano& b) {
            return a.getId() < b.getId();
    });
    return maxIt->getId() + 1;
}
// Encontra o maior ID em um vetor de Aulas (ponteiros) e retorna o próximo ID.
int encontrarProximoId(const std::vector<Aula*>& v) {
     if (v.empty()) return 100; // Define 100 como o ID inicial para aulas
     auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Aula* a, const Aula* b) {
            return a->getId() < b->getId();
    });
    return (*maxIt)->getId() + 1;
}


// Construtor do StudioManager.
StudioManager::StudioManager() {
    std::cout << "Iniciando Studio Manager..." << std::endl;
    
    // Carrega os dados dos arquivos .txt para os vetores em memória.
    std::cout << "Carregando dados dos arquivos .txt..." << std::endl;
    this->planos = DataManager::carregarPlanos(ARQ_PLANOS);
    this->instrutores = DataManager::carregarInstrutores(ARQ_INSTRUTORES);
    this->praticantes = DataManager::carregarPraticantes(ARQ_PRATICANTES);
    // this->aulas = DataManager::carregarAulas(ARQ_AULAS); // Implementação futura

    // Inicializa os contadores de ID com base nos dados carregados.
    this->proximoIdPlano = encontrarProximoId(this->planos);
    int proxPraticante = encontrarProximoId(this->praticantes);
    int proxInstrutor = encontrarProximoId(this->instrutores);
    // Usa o maior ID entre praticantes e instrutores para o contador de pessoas.
    this->proximoIdPessoa = std::max(proxPraticante, proxInstrutor); 
    this->proximoIdAula = encontrarProximoId(this->aulas);
    
    std::cout << planos.size() << " planos, " << instrutores.size() << " instrutores, " << praticantes.size() << " praticantes carregados.\n";
}

// Destrutor do StudioManager.
StudioManager::~StudioManager() {
    std::cout << "Encerrando Studio Manager..." << std::endl;
    
    // Salva os dados atuais dos vetores de volta nos arquivos .txt.
    std::cout << "Salvando dados em arquivos .txt..." << std::endl;
    DataManager::salvarPlanos(this->planos, ARQ_PLANOS);
    DataManager::salvarInstrutores(this->instrutores, ARQ_INSTRUTORES);
    DataManager::salvarPraticantes(this->praticantes, ARQ_PRATICANTES);
    // DataManager::salvarAulas(this->aulas, ARQ_AULAS); // Implementação futura

    // Libera a memória alocada dinamicamente para cada Aula.
    std::cout << "Limpando ponteiros de aulas..." << std::endl;
    for (Aula* aula : aulas) {
        delete aula; // Chama o destrutor de cada objeto Aula alocado com 'new'.
    }
}

// Loop principal do menu da aplicação.
void StudioManager::run() {
    int escolha = -1;
    do { // O loop executa até o usuário digitar 0.
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

        // Verifica se a entrada do usuário falhou (ex: digitou uma letra).
        if (!(std::cin >> escolha)) {
            std::cout << "Opção inválida. Por favor, digite um número.\n";
            std::cin.clear(); // Limpa o estado de erro.
            limparBufferEntrada(); // Remove a entrada inválida do buffer.
            continue; // Pula para a próxima iteração do loop.
        }

        limparBufferEntrada(); // Limpa o '\n' deixado pelo std::cin.

        try { // Bloco try-catch para capturar exceções inesperadas.
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

    } while (escolha != 0); // Repete até o usuário escolher 0.
}


// Coleta dados e cadastra um novo praticante no sistema.
void StudioManager::cadastrarPraticante() {
    std::string nome, email;
    int idPlano;
    std::cout << "\n--- Cadastro de Praticante ---\n";
    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    std::cout << "Email: ";
    std::getline(std::cin, email);

    // Chama o Validator para checar se o nome é válido.
    if (!Validator::isStringValida(nome)) {
        std::cout << "Erro: O nome nao pode estar vazio. Cadastro cancelado.\n";
        return; // Retorna ao menu.
    }
    // Chama o Validator para checar se o email é válido.
    if (!Validator::isEmailValido(email)) {
        std::cout << "Erro: O formato do email e invalido (ex: nome@dominio.com). Cadastro cancelado.\n";
        return; // Retorna ao menu.
    }

    listarPlanos(); // Mostra os planos disponíveis para o usuário escolher.
    std::cout << "Digite o ID do Plano: ";
    std::cin >> idPlano;
    limparBufferEntrada();

    // Busca o plano no vetor para garantir que o ID é válido.
    if (findPlanoById(idPlano) == nullptr) {
        std::cout << "Erro: Plano não encontrado.\n";
        return;
    }

    int novoId = proximoIdPessoa++; // Calcula o novo ID.
    praticantes.emplace_back(novoId, nome, email, idPlano); // Adiciona o novo praticante ao vetor.
    std::cout << "Praticante '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n";
}

// Coleta dados e cadastra um novo instrutor no sistema.
void StudioManager::cadastrarInstrutor() {
    std::string nome, email, especialidade;
    std::cout << "\n--- Cadastro de Instrutor ---\n";
    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    std::cout << "Email: ";
    std::getline(std::cin, email);
    std::cout << "Especialidade: ";
    std::getline(std::cin, especialidade);

    // Validação da entrada de dados.
    if (!Validator::isStringValida(nome) || !Validator::isStringValida(especialidade)) {
        std::cout << "Erro: Nome e Especialidade nao podem estar vazios. Cadastro cancelado.\n";
        return;
    }
    if (!Validator::isEmailValido(email)) {
        std::cout << "Erro: O formato do email e invalido. Cadastro cancelado.\n";
        return;
    }

    int novoId = proximoIdPessoa++;
    instrutores.emplace_back(novoId, nome, email, especialidade); // Adiciona o novo instrutor ao vetor.
    std::cout << "Instrutor '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n";
}

// Coleta dados e cadastra um novo plano no sistema.
void StudioManager::cadastrarPlano() {
    std::string nome;
    double preco;
    std::cout << "\n--- Cadastro de Plano ---\n";
    std::cout << "Nome (Ex: Mensal, Trimestral): ";
    std::getline(std::cin, nome);
    std::cout << "Preço (Ex: 99.90): ";
    std::cin >> preco;
    limparBufferEntrada();

    // Validação da entrada de dados.
    if (!Validator::isStringValida(nome)) {
        std::cout << "Erro: O nome do plano nao pode estar vazio. Cadastro cancelado.\n";
        return;
    }
    if (preco <= 0) {
        std::cout << "Erro: O preco deve ser um valor positivo. Cadastro cancelado.\n";
        return;
    }

    int novoId = proximoIdPlano++;
    planos.emplace_back(novoId, nome, preco); // Adiciona o novo plano ao vetor.
    std::cout << "Plano '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n";
}

// Coleta dados e cadastra uma nova aula (polimórfica) no sistema.
void StudioManager::cadastrarAula() {
    std::cout << "\n--- Cadastro de Nova Aula ---\n";
    // Pré-condição: Precisa de instrutores para criar uma aula.
    if (instrutores.empty()) {
        std::cout << "Erro: Cadastre um instrutor primeiro.\n";
        return;
    }

    // Pergunta ao usuário qual tipo de aula (HotYoga, YogaPets, etc.)
    int tipoAula = selecionarTipoAulaMenu();
    if (tipoAula == 0) return; // Usuário cancelou.

    // Coleta dados comuns a todas as Aulas.
    std::string horario;
    int limiteAlunos;
    std::cout << "Horário (Ex: Seg 18:00): ";
    std::getline(std::cin, horario);
    std::cout << "Limite de Alunos: ";
    std::cin >> limiteAlunos;
    limparBufferEntrada();

    // Validação dos dados comuns.
    if (!Validator::isStringValida(horario)) {
        std::cout << "Erro: O horario nao pode estar vazio. Cadastro cancelado.\n";
        return;
    }
    if (limiteAlunos <= 0) {
        std::cout << "Erro: O limite de alunos deve ser positivo. Cadastro cancelado.\n";
        return;
    }

    // Seleção do instrutor para a aula.
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

    // Lógica de Polimorfismo: Cria o tipo específico de aula.
    Aula* novaAula = nullptr; // Ponteiro da classe base.
    int novoId = proximoIdAula++;

    switch (tipoAula) {
        case 1: { // Caso Hot Yoga
            std::cout << "Digite a Temperatura da Sala (em °C): ";
            int temp;
            std::cin >> temp;
            limparBufferEntrada();
            // Cria um objeto HotYoga e armazena no ponteiro da base.
            novaAula = new HotYoga(novoId, horario, idInstrutor, limiteAlunos, temp);
            break;
        }
        case 2: { // Caso Yoga com Pets
            std::cout << "Tipo de Pet Permitido (Ex: Gatos, Cachorros dócil): ";
            std::string tipoPet;
            std::getline(std::cin, tipoPet);
             if (!Validator::isStringValida(tipoPet)) {
                std::cout << "Erro: O tipo de pet nao pode estar vazio. Cadastro cancelado.\n";
                proximoIdAula--; // Reverte o ID, pois a aula falhou.
                return;
            }
            // Cria um objeto YogaPets e armazena no ponteiro da base.
            novaAula = new YogaPets(novoId, horario, idInstrutor, limiteAlunos, tipoPet);
            break;
        }
        default:
            std::cout << "Erro: Tipo de aula inválido.\n";
            proximoIdAula--; // Reverte o ID.
            return;
    }

    // Adiciona o ponteiro da nova aula ao vetor de aulas.
    aulas.push_back(novaAula);
    instrutor->adicionarAula(novoId); // Linka a aula ao instrutor.

    std::cout << "Aula (ID: " << novoId << ") cadastrada com sucesso!\n";
}

// Matricula um praticante existente em uma aula existente.
void StudioManager::matricularPraticanteEmAula() {
    std::cout << "\n--- Matricular Praticante em Aula ---\n";
    // Pré-condições: Precisa ter praticantes e aulas.
    if (praticantes.empty()) {
        std::cout << "Erro: Nenhum praticante cadastrado.\n"; return;
    }
    if (aulas.empty()) {
        std::cout << "Erro: Nenhuma aula cadastrada.\n"; return;
    }

    // Seleção do Praticante
    listarPraticantes();
    std::cout << "Digite o ID do Praticante: ";
    int idPraticante;
    std::cin >> idPraticante;
    limparBufferEntrada();
    Praticante* praticante = findPraticanteById(idPraticante);
    if (praticante == nullptr) {
        std::cout << "Erro: Praticante não encontrado.\n"; return;
    }

    // Seleção da Aula
    listarAulas();
    std::cout << "Digite o ID da Aula: ";
    int idAula;
    std::cin >> idAula;
    limparBufferEntrada();
    Aula* aula = findAulaById(idAula);
    if (aula == nullptr) {
        std::cout << "Erro: Aula não encontrada.\n"; return;
    }

    // Chama os métodos de lógica de negócio para registrar a matrícula.
    if (aula->inscreverPraticante(praticante->getId())) {
        praticante->inscreverEmAula(aula->getId()); // Cria o link bidirecional.
        std::cout << "Matrícula de '" << praticante->getNome() << "' realizada com sucesso!\n";
    } else {
        std::cout << "Não foi possível matricular. A aula pode estar lotada.\n";
    }
}

// Lista todos os praticantes cadastrados.
void StudioManager::listarPraticantes() {
    std::cout << "\n--- Lista de Praticantes ---\n";
    if (praticantes.empty()) {
        std::cout << "Nenhum praticante cadastrado.\n"; return;
    }
    // Itera pelo vetor e chama o método de exibição de cada praticante.
    for (const auto& p : praticantes) {
        p.exibirDetalhes();
    }
}

// Lista todos os instrutores cadastrados.
void StudioManager::listarInstrutores() {
    std::cout << "\n--- Lista de Instrutores ---\n";
    if (instrutores.empty()) {
        std::cout << "Nenhum instrutor cadastrado.\n"; return;
    }
    // Itera pelo vetor e chama o método de exibição de cada instrutor.
    for (const auto& i : instrutores) {
        i.exibirDetalhes();
    }
}

// Lista todos os planos cadastrados.
void StudioManager::listarPlanos() {
    std::cout << "\n--- Lista de Planos ---\n";
    if (planos.empty()) {
        std::cout << "Nenhum plano cadastrado.\n"; return;
    }
    // Itera pelo vetor e chama o método de exibição de cada plano.
    for (const auto& p : planos) {
        p.exibirDetalhes();
    }
}

// Lista todas as aulas cadastradas.
void StudioManager::listarAulas() {
    std::cout << "\n--- Lista de Aulas --- (Total: " << aulas.size() << ")\n";
    if (aulas.empty()) {
        std::cout << "Nenhuma aula cadastrada.\n"; return;
    }
    // Itera pelo vetor de ponteiros de Aula.
    for (const Aula* aulaPtr : aulas) {
        // POLIMORFISMO: O C++ chama o 'exibirDetalhes' da classe correta
        // (HotYoga, YogaPets, etc.) automaticamente.
        aulaPtr->exibirDetalhes();
        std::cout << "---------------------------------\n";
    }
}

// Menu auxiliar para seleção do tipo de aula (polimorfismo).
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

// Limpa o buffer de entrada do std::cin para evitar bugs com getline.
void StudioManager::limparBufferEntrada() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Procura um Praticante no vetor 'praticantes' pelo ID.
Praticante* StudioManager::findPraticanteById(int id) {
    // Itera pelo vetor usando 'auto&' para performance.
    for (auto& p : praticantes) {
        if (p.getId() == id) return &p; // Retorna o endereço do objeto.
    }
    return nullptr; // Retorna nulo se não encontrar.
}

// Procura um Instrutor no vetor 'instrutores' pelo ID.
Instrutor* StudioManager::findInstrutorById(int id) {
    for (auto& i : instrutores) {
        if (i.getId() == id) return &i;
    }
    return nullptr;
}

// Procura uma Aula no vetor 'aulas' pelo ID.
Aula* StudioManager::findAulaById(int id) {
    for (auto* a : aulas) { // Itera sobre ponteiros.
        if (a->getId() == id) return a; // Retorna o ponteiro.
    }
    return nullptr;
}

// Procura um Plano no vetor 'planos' pelo ID.
Plano* StudioManager::findPlanoById(int id) {
    for (auto& p : planos) {
        if (p.getId() == id) return &p;
    }
    return nullptr;
}