# Versão mínima do CMake necessária
cmake_minimum_required(VERSION 3.10)

# Define o nome do projeto (ex: StudioYogaManager.sln no Visual Studio)
project(StudioYogaManager LANGUAGES CXX)

# Define o padrão do C++ que queremos usar (C++ 17 é moderno e recomendado)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- Configuração de Pastas ---

# Adiciona a pasta "include" ao caminho de busca de headers.
# Isso permite que nossos arquivos .cpp usem: #include "models/Pessoa.h"
# em vez de #include "../include/models/Pessoa.h"
include_directories(include)

# --- Lista de Arquivos-Fonte (.cpp) ---

# Lista todos os arquivos .cpp que precisam ser compilados.
set(SOURCES
    main.cpp
    src/models/Pessoa.cpp
    src/models/Praticante.cpp
    src/models/Instrutor.cpp
    src/models/Plano.cpp
    src/models/Aula.cpp
    src/models/HotYoga.cpp
    src/models/YogaPets.cpp
    src/data/DataManager.cpp
    src/services/StudioManager.cpp
    src/validator/Validator.cpp  # <-- AQUI ESTÁ O NOVO ARQUIVO
)

# --- Criação do Executável ---

# Cria o executável final chamado "StudioYogaManager".
# Este comando pega todos os arquivos listados em ${SOURCES} e os compila juntos.
add_executable(StudioYogaManager ${SOURCES})

# Mensagem de status (opcional, mas útil)
message(STATUS "Configuring StudioYogaManager... Build files will be in your build directory.")