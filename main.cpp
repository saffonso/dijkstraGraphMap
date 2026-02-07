#include <QCoreApplication>
#include <iostream>
#include <vector>
#include "trie.h"
#include "dataloader.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    
    std::cout << "Começando" << std::endl << std::endl;
    
    Trie trie;
    Dataloader loader("C:\\Users\\santi\\Downloads");

    QJsonObject labelsJson = loader.loadLabelToNodes();

    loader.makeTrie(trie, labelsJson);

    return 0;
}
