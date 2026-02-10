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

    std::cout << "Dados carregados com sucesso!" << std::endl;

    MainWindow window(trie);
    window.show();

    app.exec();

    std::cout << window.getSelectedLocationName().toStdString() << std::endl;

    return 0;
}
