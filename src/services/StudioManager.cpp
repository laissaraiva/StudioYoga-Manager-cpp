#include "services/StudioManager.h"
#include "models/HotYoga.h"
#include "models/YogaPets.h" 
#include "models/YogaWorkflow.h" // <-- [LINHA ADICIONADA]
#include <iostream>
#include <string>
#include <limits>
#include "data/DataManager.h"
#include <algorithm>
#include "validator/Validator.h"
#include <cstdlib> // Para system("cls") ou system("clear")
#include "utils/Color.h" // Nosso header de cores
#include <fstream> // Para gerar o HTML

// Nomes dos arquivos de persistência
const std::string ARQ_PRATICANTES = "praticantes.dat"; // (Você mencionou que usa .dat)
const std::string ARQ_INSTRUTORES = "instrutores.dat";
const std::string ARQ_PLANOS = "planos.dat";

// --- Funções Auxiliares de ID ---
int encontrarProximoId(const std::vector<Praticante>& v) {
    if (v.empty()) return 1;
    auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Praticante& a, const Praticante& b) { return a.getId() < b.getId(); });
    return maxIt->getId() + 1;
}
int encontrarProximoId(const std::vector<Instrutor>& v) {
     if (v.empty()) return 1;
     auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Instrutor& a, const Instrutor& b) { return a.getId() < b.getId(); });
    return maxIt->getId() + 1;
}
int encontrarProximoId(const std::vector<Plano>& v) {
     if (v.empty()) return 1;
     auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Plano& a, const Plano& b) { return a.getId() < b.getId(); });
    return maxIt->getId() + 1;
}
int encontrarProximoId(const std::vector<Aula*>& v) {
     // ID inicial (como visto no seu print)
     if (v.empty()) return 190;
     auto maxIt = std::max_element(v.begin(), v.end(), 
        [](const Aula* a, const Aula* b) { return a->getId() < b->getId(); });
    return (*maxIt)->getId() + 1;
}

// --- Construtor (com Modo Demo) ---
StudioManager::StudioManager() {
    std::cout << "Iniciando Studio Manager..." << std::endl;
    
    std::cout << "Carregando dados dos arquivos .dat..." << std::endl; // (Mudei para .dat)
    this->planos = DataManager::carregarPlanos(ARQ_PLANOS);
    this->instrutores = DataManager::carregarInstrutores(ARQ_INSTRUTORES);
    this->praticantes = DataManager::carregarPraticantes(ARQ_PRATICANTES);

    this->proximoIdPlano = encontrarProximoId(this->planos);
    int proxPraticante = encontrarProximoId(this->praticantes);
    int proxInstrutor = encontrarProximoId(this->instrutores);
    this->proximoIdPessoa = std::max(proxPraticante, proxInstrutor); 
    this->proximoIdAula = encontrarProximoId(this->aulas);
    
    std::cout << planos.size() << " planos, " << instrutores.size() << " instrutores, " << praticantes.size() << " praticantes carregados.\n";

    // --- MODO DE DEMONSTRAÇÃO (MVP) ---
    if (planos.empty() && instrutores.empty() && praticantes.empty()) {
        std::cout << Color::B_YELLOW << "\nInfo: Nenhum dado carregado. Criando dados ficticios para demonstracao...\n" << Color::RESET;

        planos.emplace_back(proximoIdPlano++, "Plano Demo Mensal", 150.0);
        planos.emplace_back(proximoIdPlano++, "Plano Demo Avulso", 60.0);
        
        instrutores.emplace_back(proximoIdPessoa++, "Instrutora Demo", "demo@yoga.com", "Todas");
        Instrutor* instrutorDemo = &instrutores.back();

        praticantes.emplace_back(proximoIdPessoa++, "Aluno Ficticio 1", "aluno1@mail.com", planos[0].getId());
        praticantes.emplace_back(proximoIdPessoa++, "Aluno Ficticio 2", "aluno2@mail.com", planos[1].getId());
        Praticante* aluno1 = &praticantes[0];
        
        Aula* aulaHot = new HotYoga(proximoIdAula++, "Segunda 18:00", instrutorDemo->getId(), 20, 40);
        Aula* aulaPets = new YogaPets(proximoIdAula++, "Sabado 10:00", instrutorDemo->getId(), 15, "Cachorros de pequeno porte");
        
        aulaHot->inscreverPraticante(aluno1->getId());
        aluno1->inscreverEmAula(aulaHot->getId());

        this->aulas.push_back(aulaHot);
        this->aulas.push_back(aulaPets);
        
        std::cout << Color::B_GREEN << "Info: Dados ficticios criados com sucesso!\n" << Color::RESET;
    }
}

// --- Destrutor ---
StudioManager::~StudioManager() {
    std::cout << Color::B_YELLOW << "\nEncerrando Studio Manager..." << Color::RESET << std::endl;
    
    std::cout << "Salvando dados em arquivos .dat..." << std::endl; // (Mudei para .dat)
    DataManager::salvarPlanos(this->planos, ARQ_PLANOS);
    DataManager::salvarInstrutores(this->instrutores, ARQ_INSTRUTORES);
    DataManager::salvarPraticantes(this->praticantes, ARQ_PRATICANTES);

    std::cout << "Limpando ponteiros de aulas..." << std::endl;
    for (Aula* aula : aulas) {
        delete aula;
    }
}

// --- Ponto de Entrada do Menu (O "FRONT-END" TUI) ---
void StudioManager::run() {
    int escolha = -1;
    do { 
        #ifdef _WIN32
            system("cls"); // Comando do Windows
        #else
            system("clear"); // Comando do Linux/Mac
        #endif

        // Menu com a paleta de cores (Amarelo/Branco)
        std::cout << Color::B_YELLOW << "\n========= YOGA STUDIO MANAGEMENT (v2.0) =========\n" << Color::RESET;
        std::cout << "1. Cadastrar Praticante\n";
        std::cout << "2. Cadastrar Instrutor\n";
        std::cout << "3. Cadastrar Plano\n";
        std::cout << "4. Cadastrar Nova Aula\n";
        std::cout << "------------------------------------------\n";
        std::cout << "5. Matricular Praticante em Aula\n";
        std::cout << "------------------------------------------\n";
        std::cout << Color::B_WHITE << "6. Listar Praticantes\n"; 
        std::cout << "7. Listar Instrutores\n";
        std::cout << "8. Listar Planos\n";
        std::cout << "9. Listar Aulas (com detalhes)\n" << Color::RESET;
        std::cout << "10. " << Color::B_CYAN << "Gerar Relatorio HTML (Consultar)\n" << Color::RESET;
        
        std::cout << Color::B_WHITE << "------------------------------------------\n";
        std::cout << "11. Atualizar Praticante\n";
        std::cout << "12. Remover Praticante\n" << Color::RESET;

        std::cout << "------------------------------------------\n";
        std::cout << Color::YELLOW << "0. Sair e Salvar\n" << Color::RESET;
        std::cout << "==========================================\n";
        std::cout << Color::B_YELLOW << "Digite sua escolha: " << Color::RESET;

        if (!(std::cin >> escolha)) {
            std::cout << Color::B_RED << "\nOpção inválida. Por favor, digite um número.\n" << Color::RESET;
            std::cin.clear(); 
            limparBufferEntrada(); 
            std::cout << "\nPressione Enter para continuar...";
            limparBufferEntrada();
            continue; 
        }

        limparBufferEntrada(); 

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
                case 10: 
                    gerarRelatorioHTML(); 
                    std::cout << Color::B_GREEN << "\n>>> 'relatorio.html' gerado com sucesso! <<<\n" << Color::RESET;
                    break;
                case 11: atualizarPraticante(); break;
                case 12: removerPraticante(); break;
                case 0: 
                    std::cout << Color::B_YELLOW << "Saindo do sistema. Até logo!\n" << Color::RESET; 
                    break;
                default: 
                    std::cout << Color::B_RED << "\nOpção inválida. Tente novamente.\n" << Color::RESET;
            }
        } catch (const std::exception& e) {
            std::cerr << Color::BG_RED << "ERRO: " << e.what() << Color::RESET << std::endl;
        }

        // Pausa a tela após cada ação (exceto sair)
        if (escolha != 0) {
            std::cout << Color::YELLOW << "\nPressione Enter para voltar ao menu..." << Color::RESET;
            limparBufferEntrada();
        }

    } while (escolha != 0);
}


// --- Métodos de Lógica (C)REATE ---

void StudioManager::cadastrarPraticante() {
    std::string nome, email;
    int idPlano;
    std::cout << Color::B_WHITE << "\n--- Cadastro de Praticante ---\n" << Color::RESET;
    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    std::cout << "Email: ";
    std::getline(std::cin, email);

    if (!Validator::isStringValida(nome)) {
        std::cout << Color::B_RED << "Erro: O nome nao pode estar vazio. Cadastro cancelado.\n" << Color::RESET;
        return;
    }
    if (!Validator::isEmailValido(email)) {
        std::cout << Color::B_RED << "Erro: O formato do email e invalido. Cadastro cancelado.\n" << Color::RESET;
        return;
    }

    listarPlanos();
    std::cout << "Digite o ID do Plano: ";
    std::cin >> idPlano;
    limparBufferEntrada();

    if (findPlanoById(idPlano) == nullptr) {
        std::cout << Color::B_RED << "Erro: Plano não encontrado.\n" << Color::RESET;
        return;
    }

    int novoId = proximoIdPessoa++;
    praticantes.emplace_back(novoId, nome, email, idPlano);
    std::cout << Color::B_GREEN << "Praticante '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n" << Color::RESET;
}

void StudioManager::cadastrarInstrutor() {
    std::string nome, email, especialidade;
    std::cout << Color::B_WHITE << "\n--- Cadastro de Instrutor ---\n" << Color::RESET;
    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    std::cout << "Email: ";
    std::getline(std::cin, email);
    std::cout << "Especialidade: ";
    std::getline(std::cin, especialidade);

    if (!Validator::isStringValida(nome) || !Validator::isStringValida(especialidade)) {
        std::cout << Color::B_RED << "Erro: Nome e Especialidade nao podem estar vazios. Cadastro cancelado.\n" << Color::RESET;
        return;
    }
    if (!Validator::isEmailValido(email)) {
        std::cout << Color::B_RED << "Erro: O formato do email e invalido. Cadastro cancelado.\n" << Color::RESET;
        return;
    }

    int novoId = proximoIdPessoa++;
    instrutores.emplace_back(novoId, nome, email, especialidade);
    std::cout << Color::B_GREEN << "Instrutor '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n" << Color::RESET;
}

void StudioManager::cadastrarPlano() {
    std::string nome;
    double preco;
    std::cout << Color::B_WHITE << "\n--- Cadastro de Plano ---\n" << Color::RESET;
    std::cout << "Nome (Ex: Mensal, Trimestral): ";
    std::getline(std::cin, nome);
    std::cout << "Preço (Ex: 99.90): ";
    std::cin >> preco;
    limparBufferEntrada();

    if (!Validator::isStringValida(nome)) {
        std::cout << Color::B_RED << "Erro: O nome do plano nao pode estar vazio. Cadastro cancelado.\n" << Color::RESET;
        return;
    }
    if (preco <= 0) {
        std::cout << Color::B_RED << "Erro: O preco deve ser um valor positivo. Cadastro cancelado.\n" << Color::RESET;
        return;
    }

    int novoId = proximoIdPlano++;
    planos.emplace_back(novoId, nome, preco);
    std::cout << Color::B_GREEN << "Plano '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n" << Color::RESET;
}

void StudioManager::cadastrarAula() {
    std::cout << Color::B_WHITE << "\n--- Cadastro de Nova Aula ---\n" << Color::RESET;
    if (instrutores.empty()) {
        std::cout << Color::B_RED << "Erro: Cadastre um instrutor primeiro.\n" << Color::RESET;
        return;
    }

    int tipoAula = selecionarTipoAulaMenu();
    if (tipoAula == 0) return; 

    std::string horario;
    int limiteAlunos;
    std::cout << "Horário (Ex: Seg 18:00): ";
    std::getline(std::cin, horario);
    std::cout << "Limite de Alunos: ";
    std::cin >> limiteAlunos;
    limparBufferEntrada();

    if (!Validator::isStringValida(horario)) {
        std::cout << Color::B_RED << "Erro: O horario nao pode estar vazio. Cadastro cancelado.\n" << Color::RESET;
        return;
    }
    if (limiteAlunos <= 0) {
        std::cout << Color::B_RED << "Erro: O limite de alunos deve ser positivo. Cadastro cancelado.\n" << Color::RESET;
        return;
    }

    listarInstrutores();
    std::cout << "Digite o ID do Instrutor: ";
    int idInstrutor;
    std::cin >> idInstrutor;
    limparBufferEntrada();

    Instrutor* instrutor = findInstrutorById(idInstrutor);
    if (instrutor == nullptr) {
        std::cout << Color::B_RED << "Erro: Instrutor não encontrado.\n" << Color::RESET;
        return;
    }

    Aula* novaAula = nullptr;
    int novoId = proximoIdAula++;

    switch (tipoAula) {
        case 1: { 
            std::cout << "Digite a Temperatura da Sala (em °C): ";
            int temp;
            std::cin >> temp;
            limparBufferEntrada();
            novaAula = new HotYoga(novoId, horario, idInstrutor, limiteAlunos, temp);
            break;
        }
        case 2: {
            std::cout << "Tipo de Pet Permitido (Ex: Gatos, Cachorros dócil): ";
            std::string tipoPet;
            std::getline(std::cin, tipoPet);
             if (!Validator::isStringValida(tipoPet)) {
                std::cout << Color::B_RED << "Erro: O tipo de pet nao pode estar vazio. Cadastro cancelado.\n" << Color::RESET;
                proximoIdAula--;
                return;
            }
            novaAula = new YogaPets(novoId, horario, idInstrutor, limiteAlunos, tipoPet);
            break;
        }
        // --- [LÓGICA ADICIONADA] ---
        case 3: { 
            std::cout << "Foco do Workflow (Ex: Força, Flexibilidade): ";
            std::string foco;
            std::getline(std::cin, foco);
            if (!Validator::isStringValida(foco)) {
                std::cout << Color::B_RED << "Erro: O foco nao pode estar vazio. Cadastro cancelado.\n" << Color::RESET;
                proximoIdAula--;
                return;
            }
            novaAula = new YogaWorkflow(novoId, horario, idInstrutor, limiteAlunos, foco);
            break;
        }
        // --- [FIM DA LÓGICA] ---
        default:
            std::cout << Color::B_RED << "Erro: Tipo de aula inválido.\n" << Color::RESET;
            proximoIdAula--; 
            return;
    }

    aulas.push_back(novaAula);
    instrutor->adicionarAula(novoId); 

    std::cout << Color::B_GREEN << "Aula (ID: " << novoId << ") cadastrada com sucesso!\n" << Color::RESET;
}

void StudioManager::matricularPraticanteEmAula() {
    std::cout << Color::B_WHITE << "\n--- Matricular Praticante em Aula ---\n" << Color::RESET;
    if (praticantes.empty()) {
        std::cout << Color::B_RED << "Erro: Nenhum praticante cadastrado.\n" << Color::RESET; return;
    }
    if (aulas.empty()) {
        std::cout << Color::B_RED << "Erro: Nenhuma aula cadastrada.\n" << Color::RESET; return;
    }

    listarPraticantes();
    std::cout << "Digite o ID do Praticante: ";
    int idPraticante;
    std::cin >> idPraticante;
    limparBufferEntrada();
    Praticante* praticante = findPraticanteById(idPraticante);
    if (praticante == nullptr) {
        std::cout << Color::B_RED << "Erro: Praticante não encontrado.\n" << Color::RESET; return;
    }

    listarAulas();
    std::cout << "Digite o ID da Aula: ";
    int idAula;
    std::cin >> idAula;
    limparBufferEntrada();
    Aula* aula = findAulaById(idAula);
    if (aula == nullptr) {
        std::cout << Color::B_RED << "Erro: Aula não encontrada.\n" << Color::RESET; return;
    }

    if (aula->inscreverPraticante(praticante->getId())) {
        praticante->inscreverEmAula(aula->getId());
        std::cout << Color::B_GREEN << "Matrícula de '" << praticante->getNome() << "' realizada com sucesso!\n" << Color::RESET;
    } else {
        std::cout << Color::B_RED << "Não foi possível matricular. A aula pode estar lotada.\n" << Color::RESET;
    }
}

// --- Métodos de Lógica (R)EAD ---

void StudioManager::listarPraticantes() {
    std::cout << Color::B_WHITE << "\n--- Lista de Praticantes ---\n" << Color::RESET;
    if (praticantes.empty()) {
        std::cout << "Nenhum praticante cadastrado.\n"; return;
    }
    for (const auto& p : praticantes) {
        p.exibirDetalhes();
    }
}

void StudioManager::listarInstrutores() {
    std::cout << Color::B_WHITE << "\n--- Lista de Instrutores ---\n" << Color::RESET;
    if (instrutores.empty()) {
        std::cout << "Nenhum instrutor cadastrado.\n"; return;
    }
    for (const auto& i : instrutores) {
        i.exibirDetalhes();
    }
}

void StudioManager::listarPlanos() {
    std::cout << Color::B_WHITE << "\n--- Lista de Planos ---\n" << Color::RESET;
    if (planos.empty()) {
        std::cout << "Nenhum plano cadastrado.\n"; return;
    }
    for (const auto& p : planos) {
        p.exibirDetalhes();
    }
}

void StudioManager::listarAulas() {
    std::cout << Color::B_WHITE << "\n--- Lista de Aulas --- (Total: " << aulas.size() << ")\n" << Color::RESET;
    if (aulas.empty()) {
        std::cout << "Nenhuma aula cadastrada.\n"; return;
    }
    for (const Aula* aulaPtr : aulas) {
        aulaPtr->exibirDetalhes();
        std::cout << "---------------------------------\n";
    }
}

// --- Métodos de Lógica (U)PDATE E (D)ELETE ---

void StudioManager::atualizarPraticante() {
    std::cout << Color::B_WHITE << "\n--- Atualizar Praticante ---\n" << Color::RESET;
    if (praticantes.empty()) {
        std::cout << Color::B_RED << "Erro: Nenhum praticante cadastrado.\n" << Color::RESET; return;
    }

    listarPraticantes();
    std::cout << "Digite o ID do Praticante que deseja atualizar: ";
    int id;
    std::cin >> id;
    limparBufferEntrada();

    Praticante* praticante = findPraticanteById(id);
    if (praticante == nullptr) {
        std::cout << Color::B_RED << "Erro: Praticante com ID " << id << " não encontrado.\n" << Color::RESET;
        return;
    }

    int escolha = 0;
    std::cout << "Praticante encontrado: " << praticante->getNome() << "\n";
    std::cout << "O que deseja atualizar?\n";
    std::cout << "1. Nome\n";
    std::cout << "2. Email\n";
    std::cout << "3. Plano\n";
    std::cout << "0. Cancelar\n";
    std::cout << "> ";
    std::cin >> escolha;
    limparBufferEntrada();

    switch (escolha) {
        case 1: { 
            std::string novoNome;
            std::cout << "Digite o novo Nome: ";
            std::getline(std::cin, novoNome);
            if (Validator::isStringValida(novoNome)) {
                praticante->setNome(novoNome);
                std::cout << Color::B_GREEN << "Nome atualizado com sucesso!\n" << Color::RESET;
            } else {
                std::cout << Color::B_RED << "Erro: Nome inválido.\n" << Color::RESET;
            }
            break;
        }
        case 2: { 
            std::string novoEmail;
            std::cout << "Digite o novo Email: ";
            std::getline(std::cin, novoEmail);
            if (Validator::isEmailValido(novoEmail)) {
                praticante->setEmail(novoEmail);
                std::cout << Color::B_GREEN << "Email atualizado com sucesso!\n" << Color::RESET;
            } else {
                std::cout << Color::B_RED << "Erro: Email inválido.\n" << Color::RESET;
            }
            break;
        }
        case 3: { 
            listarPlanos();
            std::cout << "Digite o ID do novo Plano: ";
            int idPlano;
            std::cin >> idPlano;
            limparBufferEntrada();
            if (findPlanoById(idPlano) != nullptr) {
                praticante->setIdPlano(idPlano);
                std::cout << Color::B_GREEN << "Plano atualizado com sucesso!\n" << Color::RESET;
            } else {
                std::cout << Color::B_RED << "Erro: Plano não encontrado.\n" << Color::RESET;
            }
            break;
        }
        case 0:
            std::cout << "Atualização cancelada.\n";
            break;
        default:
            std::cout << Color::B_RED << "Opção inválida.\n" << Color::RESET;
            break;
    }
}

void StudioManager::removerPraticante() {
    std::cout << Color::B_WHITE << "\n--- Remover Praticante ---\n" << Color::RESET;
    if (praticantes.empty()) {
        std::cout << Color::B_RED << "Erro: Nenhum praticante cadastrado.\n" << Color::RESET; return;
    }

    listarPraticantes();
    std::cout << "Digite o ID do Praticante que deseja REMOVER (ação irreversível!): ";
    int id;
    std::cin >> id;
    limparBufferEntrada();

    auto iter = std::find_if(praticantes.begin(), praticantes.end(), [id](const Praticante& p) {
        return p.getId() == id;
    });

    if (iter == praticantes.end()) {
        std::cout << Color::B_RED << "Erro: Praticante com ID " << id << " não encontrado.\n" << Color::RESET;
        return;
    }
    
    std::string nomePraticante = iter->getNome();
    char confirmacao;
    std::cout << Color::B_RED << "Tem certeza que deseja remover '" << nomePraticante << "'? (s/n): " << Color::RESET;
    std::cin >> confirmacao;
    limparBufferEntrada();

    if (confirmacao == 's' || confirmacao == 'S') {
        praticantes.erase(iter);
        std::cout << Color::B_GREEN << "Praticante '" << nomePraticante << "' removido com sucesso.\n" << Color::RESET;
    } else {
        std::cout << "Remoção cancelada.\n";
    }
}


// --- Métodos Auxiliares (Limpeza e Finders) ---

int StudioManager::selecionarTipoAulaMenu() {
    int escolha = 0;
    while (true) {
        std::cout << Color::B_WHITE << "  Selecione o Tipo de Aula:\n" << Color::RESET;
        std::cout << "  1. Hot Yoga\n";
        std::cout << "  2. Yoga com Pets\n";
        std::cout << "  3. Yoga Workflow\n"; // <-- [LINHA ADICIONADA]
        std::cout << "  0. " << Color::YELLOW << "Cancelar\n" << Color::RESET;
        std::cout << "  > ";
        std::cin >> escolha;

        if (std::cin.fail()) {
            std::cin.clear();
            limparBufferEntrada();
            std::cout << Color::B_RED << "Entrada inválida. Tente novamente.\n" << Color::RESET;
        } else {
            limparBufferEntrada();
            // --- [LÓGICA MODIFICADA] ---
            if (escolha >= 0 && escolha <= 3) { // Alterado de 2 para 3
                return escolha;
            }
            // --- [FIM DA LÓGICA] ---
            std::cout << Color::B_RED << "Opção inválida. Tente novamente.\n" << Color::RESET;
        }
    }
}

void StudioManager::limparBufferEntrada() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

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
    for (auto* a : aulas) {
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

// --- Geração do Relatório HTML (o "front" de consulta) ---
void StudioManager::gerarRelatorioHTML() {
    std::ofstream relatorio("relatorio.html", std::ios::trunc);
    if (!relatorio.is_open()) {
        std::cout << Color::B_RED << "Erro ao tentar criar o arquivo relatorio.html\n" << Color::RESET;
        return;
    }

    relatorio << "<!DOCTYPE html>\n<html lang=\"pt-br\">\n<head>\n";
    relatorio << "<meta charset=\"UTF-8\">\n";
    relatorio << "<title>Relatorio - Studio Yoga</title>\n";
    relatorio << "<style>\n";
    relatorio << "  body { font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Arial, sans-serif; margin: 20px; background-color: #f9f9f9; color: #333; }\n";
    relatorio << "  .container { max-width: 800px; margin: auto; background-color: #fff; border-radius: 8px; box-shadow: 0 4px 12px rgba(0,0,0,0.05); padding: 20px 40px; }\n";
    relatorio << "  h1 { color: #2c3e50; text-align: center; border-bottom: 2px solid #DAA520; padding-bottom: 10px; }\n";
    relatorio << "  h2 { color: #34495e; border-bottom: 1px solid #ecf0f1; padding-bottom: 5px; margin-top: 30px; }\n";
    relatorio << "  .card { border: 1px solid #ddd; border-radius: 8px; padding: 10px 20px; margin-bottom: 15px; }\n";
    relatorio << "  .card p { margin: 8px 0; }\n";
    relatorio << "  .card strong { color: #555; min-width: 120px; display: inline-block; }\n";
    relatorio << "  footer { text-align: center; margin-top: 40px; color: #888; font-size: 0.9em; }\n";
    relatorio << "</style>\n</head>\n<body>\n<div class=\"container\">\n";
    relatorio << "<h1>Relatorio do Sistema - Studio Yoga Manager</h1>\n";

    relatorio << "<h2>Praticantes Cadastrados (" << praticantes.size() << ")</h2>\n";
    for (const auto& p : praticantes) {
        relatorio << "<div class=\"card\">\n";
        relatorio << "  <p><strong>Nome:</strong> " << p.getNome() << "</p>\n";
        relatorio << "  <p><strong>Email:</strong> " << p.getEmail() << "</p>\n";
        relatorio << "  <p><strong>ID do Plano:</strong> " << p.getIdPlano() << "</p>\n";
        relatorio << "</div>\n";
    }

    relatorio << "<h2>Instrutores Cadastrados (" << instrutores.size() << ")</h2>\n";
    for (const auto& i : instrutores) {
        relatorio << "<div classcard\">\n";
        relatorio << "  <p><strong>Nome:</strong> " << i.getNome() << "</p>\n";
        relatorio << "  <p><strong>Email:</strong> " << i.getEmail() << "</p>\n";
        relatorio << "  <p><strong>Especialidade:</strong> " << i.getEspecialidade() << "</p>\n";
        relatorio << "</div>\n";
    }
    
    relatorio << "<h2>Planos Disponiveis (" << planos.size() << ")</h2>\n";
    for (const auto& pl : planos) {
        relatorio << "<div class=\"card\">\n";
        relatorio << "  <p><strong>Nome:</strong> " << pl.getNome() << "</p>\n";
        relatorio << "  <p><strong>Preco:</strong> R$ " << pl.getPreco() << "</p>\n";
        relatorio << "  <p><strong>ID:</strong> " << pl.getId() << "</p>\n";
        relatorio << "</div>\n";
    }

    relatorio << "<h2>Aulas Agendadas (" << aulas.size() << ")</h2>\n";
    if (aulas.empty()) {
        relatorio << "<p>Nenhuma aula agendada.</p>\n";
    }
    for (const Aula* a : aulas) {
        relatorio << "<div class=\"card\">\n";
        relatorio << "  <p><strong>Tipo de Aula:</strong> " << a->getTipoDeAula() << "</p>\n";
        relatorio << "  <p><strong>ID da Aula:</strong> " << a->getId() << "</p>\n";
        relatorio << "  <p><strong>Horario:</strong> " << a->getHorario() << "</p>\n";
        relatorio << "  <p><strong>Vagas:</strong> " << a->getVagasDisponiveis() << " / " << a->getLimiteAlunos() << "</p>\n";
        
        // Polimorfismo para detalhes extras no HTML
        const HotYoga* hot = dynamic_cast<const HotYoga*>(a);
        if (hot) {
            relatorio << "  <p><strong>Temperatura:</strong> " << hot->getTemperatura() << "°C</p>\n";
        }
        const YogaPets* pets = dynamic_cast<const YogaPets*>(a);
        if (pets) {
            relatorio << "  <p><strong>Pets:</strong> " << pets->getTipoPetPermitido() << "</p>\n";
        }
        // --- [LÓGICA ADICIONADA] ---
        const YogaWorkflow* workflow = dynamic_cast<const YogaWorkflow*>(a);
        if (workflow) {
            relatorio << "  <p><strong>Foco:</strong> " << workflow->getFoco() << "</p>\n";
        }
        // --- [FIM DA LÓGICA] ---

        relatorio << "</div>\n";
    }

    relatorio << "<footer><p>Relatorio gerado pelo StudioYogaManager C++</p></footer>\n";
    relatorio << "</div>\n</body>\n</html>\n";
    relatorio.close();
}