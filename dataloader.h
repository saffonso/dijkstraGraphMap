#ifndef DATALOADER_H
#define DATALOADER_H

#include "grafo.h"
#include "trie.h"
#include <string>
#include <unordered_map>
#include <vector>

class Dataloader
{
public:
    Dataloader(const std::string& path);

    bool loadNodes(Grafo& grafo);

    bool loadEdges(Grafo& grafo);

    bool loadLabelToNodes(std::unordered_map<std::string, std::vector<long long>>& labelToNodes);

    bool loadNodeToLabel(std::unordered_map<long long, std::string>& nodesToLabel);

    bool makeTrie(Trie& trie, const std::unordered_map<std::string, std::vector<long long>>& labelToNodes);

};

#endif // DATALOADER_H
