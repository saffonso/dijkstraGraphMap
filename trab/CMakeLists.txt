cmake_minimum_required(VERSION 3.10)
project(SistemaNavegacao)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Arquivos fonte
add_executable(navegacao
    main.cpp
    trie.cpp
    graph.cpp
    dijkstra.cpp
    dataloader.cpp
)

# Incluir diretório atual para headers
target_include_directories(navegacao PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
