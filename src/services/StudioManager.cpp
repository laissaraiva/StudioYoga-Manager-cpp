#include "services/StudioManager.h"
#include "models/HotYoga.h"   // <--- Incluímos as classes filhas
#include "models/YogaPets.h"
#include <iostream>
#include <string>
#include <limits>
#include <fstream>   // <--- NOVO: Para leitura/escrita de arquivos
#include <sstream>   // <--- NOVO: Para processar strings de linha
#include <algorithm> // <--- NOVO: Para std::max

// --- NOVO: Constantes para os nomes dos arquivos ---
const std::string ARQUIVO_PLANOS = "planos.dat";
const std::string ARQUIVO_INSTRUTORES = "instrutores.dat";
const std::string ARQUIVO_PRATICANTES = "praticantes.dat";
const std::string ARQUIVO_AULAS = "aulas.dat";

// --- Construtor e Destrutor (MODIFICADOS) ---

StudioManager::StudioManager()
    : proximoIdPessoa(1), proximoIdAula(100), proximoIdPlano(1000) {
    // AGORA o construtor carrega os dados
    std::cout << "Iniciando Studio Manager..." << std::endl;
    carregarDados();
    std::cout << "Sistema pronto." << std::endl;
}

StudioManager::~StudioManager() {
    // Destrutor OBRIGATÓRIO para salvar os dados e limpar a memória
    std::cout << "Encerrando Studio Manager..." << std::endl;

    // 1. Salva tudo antes de sair
    salvarDados();

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
        std::cout << "4. Cadastrar Nova Aula (Hot, Pets, Flow)\n";
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
    std::cout << "Nome (Ex: Mensal, Trimestral): ";
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


// ----- NOVOS MÉTODOS DE PERSISTÊNCIA (IMPLEMENTAÇÃO) -----

void StudioManager::salvarDados() {
    std::ofstream arquivo;
    std::cout << "Salvando dados nos arquivos .dat..." << std::endl;

    // 1. Salvar Planos
    arquivo.open(ARQUIVO_PLANOS);
    if (arquivo.is_open()) {
        for (const auto& plano : planos) {
            // Formato: ID,Nome,Preco
            arquivo << plano.getId() << "," << plano.getNome() << "," << plano.getPreco() << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "ERRO: Nao foi possivel salvar " << ARQUIVO_PLANOS << std::endl;
    }

    // 2. Salvar Instrutores
    arquivo.open(ARQUIVO_INSTRUTORES);
    if (arquivo.is_open()) {
        for (const auto& instrutor : instrutores) {
            // Formato: ID,Nome,Email,Especialidade
            arquivo << instrutor.getId() << "," << instrutor.getNome() << ","
                    << instrutor.getEmail() << "," << instrutor.getEspecialidade() << "\n";
            // Nota: Não salvamos as aulas do instrutor aqui,
            // a aula salvará o ID do instrutor.
        }
        arquivo.close();
    } else {
        std::cerr << "ERRO: Nao foi possivel salvar " << ARQUIVO_INSTRUTORES << std::endl;
    }

    // 3. Salvar Praticantes
    arquivo.open(ARQUIVO_PRATICANTES);
    if (arquivo.is_open()) {
        for (const auto& p : praticantes) {
            // Formato: ID,Nome,Email,ID_Plano
            arquivo << p.getId() << "," << p.getNome() << ","
                    << p.getEmail() << "," << p.getIdPlano(); // Assumindo getIdPlano()
            // Salva a lista de IDs de aulas em que está inscrito
            for (int idAula : p.getAulasInscritas()) { // Assumindo getAulasInscritas()
                arquivo << "," << idAula;
            }
            arquivo << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "ERRO: Nao foi possivel salvar " << ARQUIVO_PRATICANTES << std::endl;
    }

    // 4. Salvar Aulas (Polimorfismo)
    arquivo.open(ARQUIVO_AULAS);
    if (arquivo.is_open()) {
        for (const Aula* aula : aulas) {
            // Formato: TIPO,ID,Horario,Limite,ID_Instrutor
            arquivo << aula->getTipo() << "," << aula->getId() << ","
                    << aula->getHorario() << "," << aula->getLimiteAlunos() << ","
                    << aula->getIdInstrutor(); // Assumindo getIdInstrutor()

            // Salva dados extras das classes filhas
            if (aula->getTipo() == "HotYoga") {
                const HotYoga* hy = dynamic_cast<const HotYoga*>(aula);
                if (hy) arquivo << "," << hy->getTemperatura();
            } else if (aula->getTipo() == "YogaPets") {
                const YogaPets* yp = dynamic_cast<const YogaPets*>(aula);
                if (yp) arquivo << "," << yp->getTipoPet();
            }

            // Salva a lista de IDs de praticantes inscritos
            for (int idPraticante : aula->getIdsPraticantesInscritos()) { // Assumindo getIdsPraticantesInscritos()
                arquivo << "," << idPraticante;
            }
            arquivo << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "ERRO: Nao foi possivel salvar " << ARQUIVO_AULAS << std::endl;
    }
}

void StudioManager::carregarDados() {
    std::ifstream arquivo;
    std::string linha;
    std::cout << "Carregando dados dos arquivos .dat..." << std::endl;

    // --- 1. Carregar Planos ---
    // (Precisa ser carregado antes dos Praticantes)
    int maxPlanoId = 0;
    arquivo.open(ARQUIVO_PLANOS);
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string idStr, nome, precoStr;
            std::getline(ss, idStr, ',');
            std::getline(ss, nome, ',');
            std::getline(ss, precoStr, '\n');
            try {
                int id = std::stoi(idStr);
                double preco = std::stod(precoStr);
                planos.emplace_back(id, nome, preco);
                maxPlanoId = std::max(maxPlanoId, id);
            } catch (const std::exception& e) {
                std::cerr << "Erro ao ler linha de plano: " << linha << std::endl;
            }
        }
        arquivo.close();
        proximoIdPlano = maxPlanoId + 1;
        std::cout << "Carregados " << planos.size() << " planos." << std::endl;
    }

    // --- 2. Carregar Instrutores ---
    // (Precisa ser carregado antes das Aulas)
    int maxPessoaId = 0; // Um contador para Pessoas (Praticantes e Instrutores)
    arquivo.open(ARQUIVO_INSTRUTORES);
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string idStr, nome, email, especialidade;
            std::getline(ss, idStr, ',');
            std::getline(ss, nome, ',');
            std::getline(ss, email, ',');
            std::getline(ss, especialidade, '\n');
            try {
                int id = std::stoi(idStr);
                instrutores.emplace_back(id, nome, email, especialidade);
                maxPessoaId = std::max(maxPessoaId, id);
            } catch (const std::exception& e) {
                std::cerr << "Erro ao ler linha de instrutor: " << linha << std::endl;
            }
        }
        arquivo.close();
        std::cout << "Carregados " << instrutores.size() << " instrutores." << std::endl;
    }

    // --- 3. Carregar Praticantes ---
    arquivo.open(ARQUIVO_PRATICANTES);
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string idStr, nome, email, idPlanoStr, idAulaStr;
            std::getline(ss, idStr, ',');
            std::getline(ss, nome, ',');
            std::getline(ss, email, ',');
            std::getline(ss, idPlanoStr, ',');
            try {
                int id = std::stoi(idStr);
                int idPlano = std::stoi(idPlanoStr);
                praticantes.emplace_back(id, nome, email, idPlano);
                maxPessoaId = std::max(maxPessoaId, id);

                // Recarrega as aulas inscritas
                Praticante* p = findPraticanteById(id);
                while (std::getline(ss, idAulaStr, ',')) {
                    p->inscreverEmAula(std::stoi(idAulaStr));
                }
            } catch (const std::exception& e) {
                std::cerr << "Erro ao ler linha de praticante: " << linha << std::endl;
            }
        }
        arquivo.close();
        std::cout << "Carregados " << praticantes.size() << " praticantes." << std::endl;
    }
    // Atualiza o ID máximo de Pessoas
    proximoIdPessoa = maxPessoaId + 1;

    // --- 4. Carregar Aulas (DEVE SER O ÚLTIMO) ---
    // (Depende de Instrutores e Praticantes já estarem na memória)
    int maxAulaId = 0;
    arquivo.open(ARQUIVO_AULAS);
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string tipo, idStr, horario, limiteStr, idInstrutorStr, extra, idPraticanteStr;

            std::getline(ss, tipo, ',');
            std::getline(ss, idStr, ',');
            std::getline(ss, horario, ',');
            std::getline(ss, limiteStr, ',');
            std::getline(ss, idInstrutorStr, ',');

            try {
                int id = std::stoi(idStr);
                int limite = std::stoi(limiteStr);
                int idInstrutor = std::stoi(idInstrutorStr);

                Instrutor* instrutor = findInstrutorById(idInstrutor);
                if (instrutor == nullptr) {
                    std::cerr << "Instrutor ID " << idInstrutor << " nao encontrado. Pulando aula " << id << ".\n";
                    continue;
                }

                Aula* novaAula = nullptr;
                if (tipo == "HotYoga") {
                    std::getline(ss, extra, ','); // Temperatura
                    novaAula = new HotYoga(id, horario, idInstrutor, limite, std::stoi(extra));
                } else if (tipo == "YogaPets") {
                    std::getline(ss, extra, ','); // Tipo de Pet
                    novaAula = new YogaPets(id, horario, idInstrutor, limite, extra);
                } else {
                    // ----- LINHA CORRIGIDA -----
                    std::cerr << "Tipo de aula desconhecido: " << tipo << "\n";
                    continue;
                }

                // Recarrega os praticantes inscritos
                while (std::getline(ss, idPraticanteStr, ',')) {
                    novaAula->inscreverPraticante(std::stoi(idPraticanteStr));
                }

                aulas.push_back(novaAula);
                instrutor->adicionarAula(id); // Recria o link no instrutor
                maxAulaId = std::max(maxAulaId, id);

            } catch (const std::exception& e) {
                std::cerr << "Erro ao ler linha de aula: " << linha << " (" << e.what() << ")" << std::endl;
            }
        }
        arquivo.close();
        proximoIdAula = maxAulaId + 1;
        std::cout << "Carregadas " << aulas.size() << " aulas." << std::endl;
    }
}


// --- Métodos Auxiliares (Finders e Limpeza) ---
// (Estas funções permanecem IGUAIS)

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
            std::cout << "Entrada invalida. Tente novamente.\n";
        } else {
            limparBufferEntrada();
            if (escolha >= 0 && escolha <= 2) { // Ajuste este '2' se adicionar mais tipos
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