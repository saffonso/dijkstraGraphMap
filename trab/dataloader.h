#ifndef DATALOADER_H
#define DATALOADER_H

#include "graph.h"
#include "trie.h"
#include <string>
#include <unordered_map>
#include <vector>

class DataLoader {
private:
    std::string dataPath;
    
public:
    explicit DataLoader(const std::string& path);
    
    // Carrega nodes.json e popula o grafo
    bool loadNodes(Graph& graph);
    
    // Carrega edges.json e adiciona arestas ao grafo
    bool loadEdges(Graph& graph);
    
    // Carrega label_to_nodes.json (nome -> lista de IDs)
    bool loadLabelToNodes(std::unordered_map<std::string, std::vector<long long>>& labelToNodes);
    
    // Carrega nodes_to_label.json (ID -> nome)
    bool loadNodesToLabel(std::unordered_map<long long, std::string>& nodesToLabel);
    
    // Popula a Trie com todos os nomes de interseções
    bool populateTrie(Trie& trie, const std::unordered_map<std::string, std::vector<long long>>& labelToNodes);
};

#endif // DATALOADER_H
