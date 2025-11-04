cmake_minimum_required(VERSION 3.10)

# Define o nome do projeto.
project(StudioYogaManager)


# Define o padrão da linguagem C++ a ser utilizado (C++ 17 é recomendado).
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Adiciona o diretório 'include' à lista de locais onde o compilador
# deve procurar por arquivos de cabeçalho (.h).
include_directories(include)


# Encontra todos os arquivos de implementação (.cpp) recursivamente.
# O 'GLOB_RECURSE' busca em todas as subpastas dos caminhos listados.
file(GLOB_RECURSE SOURCES 
    "src/models/*.cpp"
    "src/services/*.cpp"
    "src/data/*.cpp"
    "src/validator/*.cpp"  # Inclui os novos arquivos de validação
)


# Cria o executável final do projeto.
# O nome do executável será 'StudioYogaManager'.
# Ele será construído a partir do 'main.cpp' e de todos os arquivos
# .cpp encontrados e armazenados na variável 'SOURCES'.
add_executable(StudioYogaManager
    main.cpp
    ${SOURCES}
)