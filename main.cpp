#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include "trie.h"
#include "dataloader.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Trie trie;

    Dataloader loader("C:\\Users\\santi\\Downloads");

    QJsonObject obj = loader.loadLabelToNodes();
    loader.makeTrie(trie, obj);

    std::cout << "\nDados carregados com sucesso!" << std::endl;
    std::cout << "Abrindo interface gráfica..." << std::endl;

    MainWindow window(trie);
    window.show();

    return app.exec();

    return 0;
}
