#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include "trie.h"
#include "dataloader.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    std::cout << "========================================" << std::endl;
    std::cout << "  Carregando dados de Pelotas..." << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Estrutura de dados
    Trie trie;
    
    // Carrega dados
    DataLoader loader(".");  // Arquivos JSON no diretório atual
    
    if (!loader.loadAndPopulateTrie(trie)) {
        std::cerr << "Erro fatal: não foi possível carregar label_to_nodes.json" << std::endl;
        return 1;
    }
    
    std::cout << "\nDados carregados com sucesso!" << std::endl;
    std::cout << "Abrindo interface gráfica..." << std::endl;
    
    // Create and show main window
    MainWindow window(trie);
    window.show();
    
    return app.exec();
}

