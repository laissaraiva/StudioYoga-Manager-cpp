# Versão mínima do CMake necessária
cmake_minimum_required(VERSION 3.10)

# Define o nome do projeto
project(StudioYogaManager LANGUAGES CXX)

# Define o padrão do C++ que queremos usar
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- Configuração de Pastas ---
# Adiciona a pasta "include" ao caminho de busca de headers.
include_directories(include)

# --- Lista de Arquivos-Fonte (.cpp) ---
set(SOURCES
    main.cpp
    src/models/Pessoa.cpp
    src/models/Praticante.cpp
    src/models/Instrutor.cpp
    src/models/Plano.cpp
    src/models/Aula.cpp
    src/models/HotYoga.cpp
    src/models/YogaPets.cpp
    src/models/YogaWorkflow.cpp  # <-- [LINHA ADICIONADA]
    src/data/DataManager.cpp
    src/services/StudioManager.cpp
    src/validator/Validator.cpp
)

# --- Criação do Executável ---
add_executable(StudioYogaManager ${SOURCES})

# Mensagem de status (opcional, mas útil)
message(STATUS "Configuring StudioYogaManager... Build files will be in your build directory.")