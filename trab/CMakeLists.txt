cmake_minimum_required(VERSION 3.10)
project(SistemaNavegacao)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt MOC
set(CMAKE_AUTOMOC ON)

# Find Qt6
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

# Arquivos fonte
add_executable(navegacao
    main.cpp
    mainwindow.cpp
    autocompletewidget.cpp
    trie.cpp
    graph.cpp
    dijkstra.cpp
    dataloader.cpp
)

# Link Qt libraries
target_link_libraries(navegacao PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

# Incluir diretório atual para headers
target_include_directories(navegacao PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
