#include "services/StudioManager.h"
#include "models/HotYoga.h"
#include "models/YogaPets.h"
#include "data/DataManager.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

// Helpers simples para validação local
namespace {
    bool isBlank(const string& s) {
        return s.find_first_not_of(" \t\r\n") == string::npos;
    }
    bool isStringValida(const string& s) {
        return !s.empty() && !isBlank(s);
    }
    bool isEmailValido(const string& s) {
        auto at = s.find('@');
        auto dot = s.find('.', at == string::npos ? 0 : at);
        return at != string::npos && dot != string::npos && at < dot;
    }

    int encontrarProximoId(const vector<Praticante>& v) {
        if (v.empty()) return 1;
        auto maxIt = std::max_element(v.begin(), v.end(),
            [](const Praticante& a, const Praticante& b) { return a.getId() < b.getId(); });
        return maxIt->getId() + 1;
    }
    int encontrarProximoId(const vector<Instrutor>& v) {
        if (v.empty()) return 1;
        auto maxIt = std::max_element(v.begin(), v.end(),
            [](const Instrutor& a, const Instrutor& b) { return a.getId() < b.getId(); });
        return maxIt->getId() + 1;
    }
    int encontrarProximoId(const vector<Plano>& v) {
        if (v.empty()) return 1;
        auto maxIt = std::max_element(v.begin(), v.end(),
            [](const Plano& a, const Plano& b) { return a.getId() < b.getId(); });
        return maxIt->getId() + 1;
    }
    int encontrarProximoId(const vector<Aula*>& v) {
        if (v.empty()) return 100;
        auto maxIt = std::max_element(v.begin(), v.end(),
            [](const Aula* a, const Aula* b) { return a->getId() < b->getId(); });
        return (*maxIt)->getId() + 1;
    }
}

// Construtor (carrega dados + modo demo)
StudioManager::StudioManager() {
    std::cout << "Iniciando Studio Manager..." << std::endl;

    DataManager dm;
    dm.carregarDados(this->planos,
                     this->instrutores,
                     this->praticantes,
                     this->aulas,
                     this->proximoIdPessoa,
                     this->proximoIdAula,
                     this->proximoIdPlano);

    // Se algum contador não foi calculado pelo DataManager, calcula aqui como fallback
    if (this->proximoIdPlano <= 0)   this->proximoIdPlano = encontrarProximoId(this->planos);
    if (this->proximoIdPessoa <= 0) {
        int proxPraticante = encontrarProximoId(this->praticantes);
        int proxInstrutor  = encontrarProximoId(this->instrutores);
        this->proximoIdPessoa = std::max(proxPraticante, proxInstrutor);
    }
    if (this->proximoIdAula <= 0)    this->proximoIdAula = encontrarProximoId(this->aulas);

    std::cout << planos.size() << " planos, " << instrutores.size()
              << " instrutores, " << praticantes.size() << " praticantes carregados.\n";

    // MODO DEMONSTRAÇÃO
    if (planos.empty() && instrutores.empty() && praticantes.empty()) {
        std::cout << "\nInfo: Nenhum dado carregado. Criando dados ficticios para demonstracao...\n";

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

        aulas.push_back(aulaHot);
        aulas.push_back(aulaPets);

        std::cout << "Info: Dados ficticios criados com sucesso!\n";
    }
}

// Destrutor
StudioManager::~StudioManager() {
    std::cout << "\nEncerrando Studio Manager..." << std::endl;

    std::cout << "Salvando dados em arquivos .dat..." << std::endl;
    DataManager dm;
    dm.salvarDados(this->planos, this->instrutores, this->praticantes, this->aulas);

    std::cout << "Limpando ponteiros de aulas..." << std::endl;
    for (Aula* aula : aulas) {
        delete aula;
    }
}

// Ponto de Entrada do Menu
void StudioManager::run() {
    int escolha = -1;
    do {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    imprimirMenuPrincipal();
    std::cout << "Digite sua escolha: ";

        if (!(std::cin >> escolha)) {
            std::cout << "\nOpcao invalida. Por favor, digite um numero.\n";
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
                    std::cout << "\n>>> 'relatorio.html' gerado com sucesso! <<<\n";
                    break;
                case 11: atualizarPraticante(); break;
                case 12: removerPraticante(); break;
                case 0:
                    std::cout << "Saindo do sistema. Ate logo!\n";
                    break;
                default:
                    std::cout << "\nOpcao invalida. Tente novamente.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }

        if (escolha != 0) {
            std::cout << "\nPressione Enter para voltar ao menu...";
            limparBufferEntrada();
        }

    } while (escolha != 0);
}

// Exibe o menu principal completo (1 a 12 e 0)
void StudioManager::imprimirMenuPrincipal() const {
    std::cout << "\n========= YOGA STUDIO MANAGEMENT (v2.0) =========\n";
    std::cout << "1. Cadastrar Praticante\n";
    std::cout << "2. Cadastrar Instrutor\n";
    std::cout << "3. Cadastrar Plano\n";
    std::cout << "4. Cadastrar Nova Aula\n";
    std::cout << "------------------------------------------\n";
    std::cout << "5. Matricular Praticante em Aula\n";
    std::cout << "------------------------------------------\n";
    std::cout << "6. Listar Praticantes\n";
    std::cout << "7. Listar Instrutores\n";
    std::cout << "8. Listar Planos\n";
    std::cout << "9. Listar Aulas (com detalhes)\n";
    std::cout << "10. Gerar Relatorio HTML (Consultar)\n";
    std::cout << "------------------------------------------\n";
    std::cout << "11. Atualizar Praticante\n";
    std::cout << "12. Remover Praticante\n";
    std::cout << "------------------------------------------\n";
    std::cout << "0. Sair e Salvar\n";
    std::cout << "==========================================\n";
}

// Métodos de Lógica (C)REATE

void StudioManager::cadastrarPraticante() {
    std::string nome, email;
    int idPlano;
    std::cout << "\n--- Cadastro de Praticante\n";
    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    std::cout << "Email: ";
    std::getline(std::cin, email);

    if (!isStringValida(nome)) {
        std::cout << "Erro: O nome nao pode estar vazio. Cadastro cancelado.\n";
        return;
    }
    if (!isEmailValido(email)) {
        std::cout << "Erro: O formato do email e invalido. Cadastro cancelado.\n";
        return;
    }

    listarPlanos();
    std::cout << "Digite o ID do Plano: ";
    std::cin >> idPlano;
    limparBufferEntrada();

    if (findPlanoById(idPlano) == nullptr) {
        std::cout << "Erro: Plano nao encontrado.\n";
        return;
    }

    int novoId = proximoIdPessoa++;
    praticantes.emplace_back(novoId, nome, email, idPlano);
    std::cout << "Praticante '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n";
}

void StudioManager::cadastrarInstrutor() {
    std::string nome, email, especialidade;
    std::cout << "\n--- Cadastro de Instrutor\n";
    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    std::cout << "Email: ";
    std::getline(std::cin, email);
    std::cout << "Especialidade: ";
    std::getline(std::cin, especialidade);

    if (!isStringValida(nome) || !isStringValida(especialidade)) {
        std::cout << "Erro: Nome e Especialidade nao podem estar vazios. Cadastro cancelado.\n";
        return;
    }
    if (!isEmailValido(email)) {
        std::cout << "Erro: O formato do email e invalido. Cadastro cancelado.\n";
        return;
    }

    int novoId = proximoIdPessoa++;
    instrutores.emplace_back(novoId, nome, email, especialidade);
    std::cout << "Instrutor '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n";
}

void StudioManager::cadastrarPlano() {
    std::string nome;
    double preco;
    std::cout << "\n--- Cadastro de Plano\n";
    std::cout << "Nome (Ex: Mensal, Trimestral): ";
    std::getline(std::cin, nome);
    std::cout << "Preco (Ex: 99.90): ";
    std::cin >> preco;
    limparBufferEntrada();

    if (!isStringValida(nome)) {
        std::cout << "Erro: O nome do plano nao pode estar vazio. Cadastro cancelado.\n";
        return;
    }
    if (preco <= 0) {
        std::cout << "Erro: O preco deve ser um valor positivo. Cadastro cancelado.\n";
        return;
    }

    int novoId = proximoIdPlano++;
    planos.emplace_back(novoId, nome, preco);
    std::cout << "Plano '" << nome << "' cadastrado com sucesso! (ID: " << novoId << ")\n";
}

void StudioManager::cadastrarAula() {
    std::cout << "\n--- Cadastro de Nova Aula\n";
    if (instrutores.empty()) {
        std::cout << "Erro: Cadastre um instrutor primeiro.\n";
        return;
    }

    int tipoAula = selecionarTipoAulaMenu();
    if (tipoAula == 0) return;

    std::string horario;
    int limiteAlunos;
    std::cout << "Horario (Ex: Seg 18:00): ";
    std::getline(std::cin, horario);
    std::cout << "Limite de Alunos: ";
    std::cin >> limiteAlunos;
    limparBufferEntrada();

    if (!isStringValida(horario)) {
        std::cout << "Erro: O horario nao pode estar vazio. Cadastro cancelado.\n";
        return;
    }
    if (limiteAlunos <= 0) {
        std::cout << "Erro: O limite de alunos deve ser positivo. Cadastro cancelado.\n";
        return;
    }

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
        case 1: {
            std::cout << "Digite a Temperatura da Sala (em C): ";
            int temp;
            std::cin >> temp;
            limparBufferEntrada();
            novaAula = new HotYoga(novoId, horario, idInstrutor, limiteAlunos, temp);
            break;
        }
        case 2: {
            std::cout << "Tipo de Pet Permitido (Ex: Gatos, Cachorros docil): ";
            std::string tipoPet;
            std::getline(std::cin, tipoPet);
            if (!isStringValida(tipoPet)) {
                std::cout << "Erro: O tipo de pet nao pode estar vazio. Cadastro cancelado.\n";
                proximoIdAula--;
                return;
            }
            novaAula = new YogaPets(novoId, horario, idInstrutor, limiteAlunos, tipoPet);
            break;
        }
        default:
            std::cout << "Erro: Tipo de aula invalido.\n";
            proximoIdAula--;
            return;
    }

    aulas.push_back(novaAula);
    instrutor->adicionarAula(novoId);

    std::cout << "Aula (ID: " << novoId << ") cadastrada com sucesso!\n";
}

void StudioManager::matricularPraticanteEmAula() {
    std::cout << "\n--- Matricular Praticante em Aula\n";
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

// Métodos de Lógica (R)EAD

void StudioManager::listarPraticantes() {
    std::cout << "\n--- Lista de Praticantes\n";
    if (praticantes.empty()) { std::cout << "Nenhum praticante cadastrado.\n"; return; }
    for (const auto& p : praticantes) p.exibirDetalhes();
}

void StudioManager::listarInstrutores() {
    std::cout << "\n--- Lista de Instrutores\n";
    if (instrutores.empty()) { std::cout << "Nenhum instrutor cadastrado.\n"; return; }
    for (const auto& i : instrutores) i.exibirDetalhes();
}

void StudioManager::listarPlanos() {
    std::cout << "\n--- Lista de Planos\n";
    if (planos.empty()) { std::cout << "Nenhum plano cadastrado.\n"; return; }
    for (const auto& p : planos) p.exibirDetalhes();
}

void StudioManager::listarAulas() {
    std::cout << "\n--- Lista de Aulas (Total: " << aulas.size() << ")\n";
    if (aulas.empty()) { std::cout << "Nenhuma aula cadastrada.\n"; return; }
    for (const Aula* aulaPtr : aulas) {
        aulaPtr->exibirDetalhes();
        std::cout << "---------------------------------\n";
    }
}

// Update/Delete

void StudioManager::atualizarPraticante() {
    std::cout << "\n--- Atualizar Praticante\n";
    if (praticantes.empty()) { std::cout << "Erro: Nenhum praticante cadastrado.\n"; return; }

    listarPraticantes();
    std::cout << "Digite o ID do Praticante que deseja atualizar: ";
    int id;
    std::cin >> id;
    limparBufferEntrada();

    Praticante* praticante = findPraticanteById(id);
    if (praticante == nullptr) {
        std::cout << "Erro: Praticante com ID " << id << " nao encontrado.\n";
        return;
    }

    int escolha = 0;
    std::cout << "Praticante encontrado: " << praticante->getNome() << "\n";
    std::cout << "O que deseja atualizar?\n";
    std::cout << "1. Nome\n2. Email\n3. Plano\n0. Cancelar\n> ";
    std::cin >> escolha;
    limparBufferEntrada();

    switch (escolha) {
        case 1: {
            std::string novoNome;
            std::cout << "Digite o novo Nome: ";
            std::getline(std::cin, novoNome);
            if (isStringValida(novoNome)) {
                praticante->setNome(novoNome);
                std::cout << "Nome atualizado com sucesso!\n";
            } else {
                std::cout << "Erro: Nome invalido.\n";
            }
            break;
        }
        case 2: {
            std::string novoEmail;
            std::cout << "Digite o novo Email: ";
            std::getline(std::cin, novoEmail);
            if (isEmailValido(novoEmail)) {
                praticante->setEmail(novoEmail);
                std::cout << "Email atualizado com sucesso!\n";
            } else {
                std::cout << "Erro: Email invalido.\n";
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
                std::cout << "Plano atualizado com sucesso!\n";
            } else {
                std::cout << "Erro: Plano nao encontrado.\n";
            }
            break;
        }
        case 0:
            std::cout << "Atualizacao cancelada.\n";
            break;
        default:
            std::cout << "Opcao invalida.\n";
            break;
    }
}

void StudioManager::removerPraticante() {
    std::cout << "\n--- Remover Praticante\n";
    if (praticantes.empty()) { std::cout << "Erro: Nenhum praticante cadastrado.\n"; return; }

    listarPraticantes();
    std::cout << "Digite o ID do Praticante que deseja REMOVER (acao irreversivel!): ";
    int id;
    std::cin >> id;
    limparBufferEntrada();

    auto iter = std::find_if(praticantes.begin(), praticantes.end(), [id](const Praticante& p) {
        return p.getId() == id;
    });

    if (iter == praticantes.end()) {
        std::cout << "Erro: Praticante com ID " << id << " nao encontrado.\n";
        return;
    }

    std::string nomePraticante = iter->getNome();
    char confirmacao;
    std::cout << "Tem certeza que deseja remover '" << nomePraticante << "'? (s/n): ";
    std::cin >> confirmacao;
    limparBufferEntrada();

    if (confirmacao == 's' || confirmacao == 'S') {
        praticantes.erase(iter);
        // TODO: Remover este id de todas as aulas
        std::cout << "Praticante '" << nomePraticante << "' removido com sucesso.\n";
    } else {
        std::cout << "Remocao cancelada.\n";
    }
}

// Auxiliares

int StudioManager::selecionarTipoAulaMenu() {
    int escolha = 0;
    while (true) {
        std::cout << "  Selecione o Tipo de Aula:\n";
        std::cout << "  1. Hot Yoga\n";
        std::cout << "  2. Yoga com Pets\n";
        std::cout << "  0. Cancelar\n";
        std::cout << "  > ";
        std::cin >> escolha;

        if (std::cin.fail()) {
            std::cin.clear();
            limparBufferEntrada();
            std::cout << "Entrada invalida. Tente novamente.\n";
        } else {
            limparBufferEntrada();
            if (escolha >= 0 && escolha <= 2) {
                return escolha;
            }
            std::cout << "Opcao invalida. Tente novamente.\n";
        }
    }
}

void StudioManager::limparBufferEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // <--- removido std::
}

Praticante* StudioManager::findPraticanteById(int id) {
    for (auto& p : praticantes) if (p.getId() == id) return &p;
    return nullptr;
}
Instrutor* StudioManager::findInstrutorById(int id) {
    for (auto& i : instrutores) if (i.getId() == id) return &i;
    return nullptr;
}
Aula* StudioManager::findAulaById(int id) {
    for (auto* a : aulas) if (a->getId() == id) return a;
    return nullptr;
}
Plano* StudioManager::findPlanoById(int id) {
    for (auto& p : planos) if (p.getId() == id) return &p;
    return nullptr;
}

// Relatório HTML
void StudioManager::gerarRelatorioHTML() {
    std::ofstream relatorio("relatorio.html", std::ios::trunc);
    if (!relatorio.is_open()) {
        std::cout << "Erro ao tentar criar o arquivo relatorio.html\n";
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
        relatorio << "<div class=\"card\">\n";
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
        relatorio << "  <p><strong>Tipo de Aula:</strong> " << a->getTipo() << "</p>\n";
        relatorio << "  <p><strong>ID da Aula:</strong> " << a->getId() << "</p>\n";
        relatorio << "  <p><strong>Horario:</strong> " << a->getHorario() << "</p>\n";
        relatorio << "  <p><strong>Vagas:</strong> " << a->getVagasDisponiveis() << " / " << a->getLimiteAlunos() << "</p>\n";

        const HotYoga* hot = dynamic_cast<const HotYoga*>(a);
        if (hot) {
            relatorio << "  <p><strong>Temperatura:</strong> " << hot->getTemperatura() << "C</p>\n";
        }
        const YogaPets* pets = dynamic_cast<const YogaPets*>(a);
        if (pets) {
            relatorio << "  <p><strong>Pets:</strong> " << pets->getTipoPet() << "</p>\n";
        }
        relatorio << "</div>\n";
    }

    relatorio << "<footer><p>Relatorio gerado pelo StudioYogaManager C++</p></footer>\n";
    relatorio << "</div>\n</body>\n</html>\n";
    relatorio.close();
}