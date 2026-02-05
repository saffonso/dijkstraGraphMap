#include "dataloader.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

DataLoader::DataLoader(const std::string& path) : dataPath(path) {}

bool DataLoader::loadNodes(Graph& graph) {
    std::string filePath = dataPath + "/nodes.json";
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir " << filePath << std::endl;
        return false;
    }
    
    try {
        json nodesJson;
        file >> nodesJson;
        
        for (const auto& node : nodesJson) {
            long long id = node["id"].get<long long>();
            double x = node["x"].get<double>();
            double y = node["y"].get<double>();
            graph.addNode(id, x, y);
        }
        
        std::cout << "Carregados " << graph.getNodeCount() << " nodos." << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao parsear nodes.json: " << e.what() << std::endl;
        return false;
    }
}

bool DataLoader::loadEdges(Graph& graph) {
    std::string filePath = dataPath + "/edges.json";
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir " << filePath << std::endl;
        return false;
    }
    
    try {
        json edgesJson;
        file >> edgesJson;
        
        size_t edgeCount = 0;
        for (const auto& edge : edgesJson) {
            long long u = edge["u"].get<long long>();
            long long v = edge["v"].get<long long>();
            double length = edge["data"]["length"].get<double>();
            
            graph.addEdge(u, v, length);
            edgeCount++;
        }
        
        std::cout << "Carregadas " << edgeCount << " arestas." << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao parsear edges.json: " << e.what() << std::endl;
        return false;
    }
}

bool DataLoader::loadLabelToNodes(std::unordered_map<std::string, std::vector<long long>>& labelToNodes) {
    std::string filePath = dataPath + "/label_to_nodes.json";
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir " << filePath << std::endl;
        return false;
    }
    
    try {
        json labelsJson;
        file >> labelsJson;
        
        for (auto it = labelsJson.begin(); it != labelsJson.end(); ++it) {
            std::string label = it.key();
            std::vector<long long> nodeIds;
            
            for (const auto& id : it.value()) {
                nodeIds.push_back(id.get<long long>());
            }
            
            labelToNodes[label] = nodeIds;
        }
        
        std::cout << "Carregados " << labelToNodes.size() << " labels." << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao parsear label_to_nodes.json: " << e.what() << std::endl;
        return false;
    }
}

bool DataLoader::loadNodesToLabel(std::unordered_map<long long, std::string>& nodesToLabel) {
    std::string filePath = dataPath + "/nodes_to_label.json";
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir " << filePath << std::endl;
        return false;
    }
    
    try {
        json labelsJson;
        file >> labelsJson;
        
        for (auto it = labelsJson.begin(); it != labelsJson.end(); ++it) {
            long long nodeId = std::stoll(it.key());
            std::string label = it.value().get<std::string>();
            nodesToLabel[nodeId] = label;
        }
        
        std::cout << "Carregados " << nodesToLabel.size() << " mapeamentos ID->label." << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao parsear nodes_to_label.json: " << e.what() << std::endl;
        return false;
    }
}

bool DataLoader::populateTrie(Trie& trie, const std::unordered_map<std::string, std::vector<long long>>& labelToNodes) {
    for (const auto& pair : labelToNodes) {
        trie.insert(pair.first);
    }
    
    std::cout << "Trie populada com " << labelToNodes.size() << " nomes." << std::endl;
    return true;
}
