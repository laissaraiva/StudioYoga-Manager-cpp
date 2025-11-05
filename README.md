# 🧘‍♀️ Studio Yoga Manager (C++)

Relatório do Projeto **STUDIOYOGA-MANAGER**, desenvolvido para a disciplina **Estrutura de Dados Orientada a Objetos**, ministrada por **Francisco Paulo Magalhães Simões** no curso de **Sistemas de Informação 2025.2**.

---

## Equipe

<div align="center">
    <table>
        <tr>
            <td align="center"><a href="https://github.com/anaraque-lS" target="_blank"><img src="https://avatars.githubusercontent.com/u/169409525?v=4" width="100px"><br /><sub><b>Ana Raquel</b></sub></a></td>
            <td align="center"><a href="https://github.com/Izadora1" target="_blank"><img src="https://avatars.githubusercontent.com/u/129686992?v=4" width="100px"><br /><sub><b>Izadora Andrade</b></sub></a></td>
            <td align="center"><a href="https://github.com/lauravfonseca" target="_blank"><img src="https://avatars.githubusercontent.com/u/211055257?v=4" width="100px"><br /><sub><b>Laura Fonseca</b></sub></a></td>
            <td align="center"><a href="https://github.com/laissaraiva" target="_blank"><img src="https://avatars.githubusercontent.com/u/224659710?v=4" width="100px"><br /><sub><b>Lais Saraiva</b></sub></a></td>
            <td align="center"><a href="https://github.com/sannathan" target="_blank"><img src="https://avatars.githubusercontent.com/u/126609244?v=4" width="100px"><br /><sub><b>Nathan Barbosa</b></sub></a></td>
        </tr>
    </table>
</div>

---

## Sumário
- [Visão Geral](#visão-geral)
- [Arquitetura do Sistema](#arquitetura-do-sistema)
- [Classes Principais](#classes-principais)
- [Relacionamentos e Padrões](#relacionamentos-e-padrões)
- [Funcionalidades Implementadas](#funcionalidades-implementadas)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Como Executar](#como-executar)

---

## Visão Geral

O **Studio Yoga Manager** é um sistema modular e extensível que simula o funcionamento de um estúdio de yoga.  
Ele permite o cadastro de **pessoas (praticantes e instrutores)**, gerenciamento de **planos de assinatura**, controle de **aulas e inscrições**, e a criação de diferentes **tipos de aula** com requisitos específicos.

A proposta central é aplicar conceitos de **Programação Orientada a Objetos (POO)** — incluindo **herança**, **polimorfismo**, **encapsulamento** e **composição** — em um contexto prático e aplicado.

---

## Arquitetura do Sistema

A estrutura segue um modelo **UML orientado a objetos**, com separação clara entre **modelos**, **serviços** e **dados**, garantindo **reuso e manutenibilidade**.

---

## Classes Principais

### Pessoa
Classe base que representa qualquer indivíduo no estúdio.

**Atributos:**
- `nome`, `E-mail`, `gênero`

**Métodos:**
- `exibirDetalhes()`, `getNome()`, `getEmail()`, `getGenero()`

---

### Praticante
Herdeira de `Pessoa`, representa um aluno.

**Atributos:**
- `Plano* plano`
- `Aula* aulas[]`

**Métodos:**
- `setPlano()`, `inscreverEmAula()`, `cancelarInscricao()`, `listarAulasInscritas()`

---

### Instrutor
Herdeira de `Pessoa`, representa um professor.

**Atributos:**
- `especialidade`

**Métodos:**
- `listarAulasMinistradas()`, `exibirDetalhes()`

---

### Plano
Define os planos de assinatura (mensal, anual, etc.).

**Atributos:**
- `id`, `tipo`, `valor`

**Métodos:**
- `getTipo()`, `getValor()`, `getId()`

---

### Aula
Centraliza as informações de uma aula.

**Atributos:**
- `id`, `dataHora`, `tipo`, `instrutor`, `praticantes`, `capacidadeMaxima`

**Métodos:**
- `adicionarPraticante()`, `removerPraticante()`, `verificarVagas()`, `exibirDetalhesCompletos()`

---

### TipoDeAula (classe base abstrata)
Define o comportamento padrão para diferentes modalidades.

**Subclasses:**
- `HotYoga` — inclui atributo `temperaturaSala`
- `YogaComPets` — inclui atributo `regrasPets`

Cada uma redefine `getRequisitos()` e `exibirDetalhes()` conforme suas particularidades.

---

## Relacionamentos e Padrões

| Tipo de Relação     | Exemplo                            | Descrição |
|---------------------|------------------------------------|------------|
| **Herança**         | `Pessoa` → `Instrutor`, `Praticante` | Reutiliza comportamento comum |
| **Polimorfismo**    | `TipoDeAula` → `HotYoga`, `YogaComPets` | Permite especialização de comportamento |
| **Composição**      | `Praticante` contém `Plano`          | Um plano não existe sem o praticante |
| **Associação**      | `Aula` ↔ `Praticante`               | Uma aula tem muitos praticantes e vice-versa |

---

## Funcionalidades Implementadas

✅ Cadastro de **praticantes** e **instrutores**  
✅ Associação de **planos** aos praticantes  
✅ Criação e gerenciamento de **aulas**  
✅ Inscrição e cancelamento em aulas  
✅ Listagem de **aulas ministradas e inscritas**  
✅ Extensibilidade para **novos tipos de aula**  

---

## Estrutura do Projeto

```bash
StudioYoga-Manager-cpp/
├── docs/ # Documentação, diagramas e relatórios
├── include/
│ ├── data/ # Headers de persistência e estruturas de dados
│ ├── models/ # Classes do domínio → Pessoa, Aula, Plano, etc.
│ └── services/ # Lógica de negócio → StudioManager.h
├── src/
│ ├── data/ # Implementações de persistência
│ ├── models/ # Implementações das classes do domínio
│ ├── services/ # Implementações de serviços e controladores
│ └── main.cpp # Ponto de entrada
├── CMakeLists.txt # Configuração de build
├── README.md # Documentação geral
└── cmake-build-debug/ # Arquivos temporários de build
```

---

## Como Executar

## Clone o repositório
git clone https://github.com/laissaraiva/StudioYoga-Manager-cpp.git

# Entre na pasta
cd StudioYoga-Manager-cpp

# Compile o projeto
cmake .
make

# Execute
./studio_yoga