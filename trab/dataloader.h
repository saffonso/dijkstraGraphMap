#ifndef DATALOADER_H
#define DATALOADER_H

#include "graph.h"
#include "trie.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <string>
#include <unordered_map>

class DataLoader {
private:
    std::string dataPath;
    
public:
    explicit DataLoader(const std::string& path);
    
    // Carrega nodes.json e popula o grafo
    bool loadNodes(Graph& graph);
    
    // Carrega edges.json e adiciona arestas ao grafo
    bool loadEdges(Graph& graph);
    
    // Lê label_to_nodes.json e retorna o JSON
    QJsonObject loadLabelToNodes();
    
    // Popula a Trie com dados do JSON
    void makeTrie(Trie& trie, const QJsonObject& labelsJson);
    
    // Carrega label_to_nodes.json e popula a Trie diretamente (usa os dois acima)
    bool loadAndPopulateTrie(Trie& trie);
    
    // Carrega nodes_to_label.json (ID -> nome) para exibir rota
    bool loadNodesToLabel(std::unordered_map<long long, std::string>& nodesToLabel);
};

#endif // DATALOADER_H
