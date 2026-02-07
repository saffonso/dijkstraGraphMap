cmake_minimum_required(VERSION 3.16)

project(final_project LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(TS_FILES final_project_pt_BR.ts)

add_executable(final_project
  main.cpp
  ${TS_FILES}
  dataloader.h dataloader.cpp
  trie.h trie.cpp
  grafo.h grafo.cpp
  autocompletewidget.h autocompletewidget.cpp
  mainwindow.h mainwindow.cpp

)
target_link_libraries(final_project PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(final_project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

include(GNUInstallDirs)
install(TARGETS final_project
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
