#include <iostream>
#include <string>
#include <limits>
#include "trie.h"
#include "graph.h"
#include "dijkstra.h"
#include "dataloader.h"

// Limpa buffer do cin após ler números
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Exibe o menu principal
void showMenu() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "  Sistema de Navegacao de Pelotas" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. Buscar local (autocomplete)" << std::endl;
    std::cout << "2. Calcular rota" << std::endl;
    std::cout << "3. Sair" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Escolha uma opcao: ";
}

// Função para busca com autocomplete
void searchLocation(const Trie& trie) {
    std::cout << "\nDigite o inicio do nome do local: ";
    std::string prefix;
    std::getline(std::cin, prefix);
    
    if (prefix.empty()) {
        std::cout << "Prefixo vazio. Tente novamente." << std::endl;
        return;
    }
    
    auto suggestions = trie.autocomplete(prefix, 10);
    
    if (suggestions.empty()) {
        std::cout << "Nenhuma sugestao encontrada para \"" << prefix << "\"" << std::endl;
    } else {
        std::cout << "\nSugestoes encontradas:" << std::endl;
        for (size_t i = 0; i < suggestions.size(); i++) {
            std::cout << "  " << (i + 1) << ". " << suggestions[i] << std::endl;
        }
    }
}

// Seleciona um local com autocomplete
std::string selectLocation(const Trie& trie, const std::string& prompt) {
    std::cout << prompt;
    std::string prefix;
    std::getline(std::cin, prefix);
    
    if (prefix.empty()) {
        return "";
    }
    
    auto suggestions = trie.autocomplete(prefix, 10);
    
    if (suggestions.empty()) {
        std::cout << "Nenhuma sugestao encontrada." << std::endl;
        return "";
    }
    
    std::cout << "\nSelecione uma opcao:" << std::endl;
    for (size_t i = 0; i < suggestions.size(); i++) {
        std::cout << "  " << (i + 1) << ". " << suggestions[i] << std::endl;
    }
    std::cout << "Opcao (1-" << suggestions.size() << "): ";
    
    int choice;
    std::cin >> choice;
    clearInputBuffer();
    
    if (choice < 1 || choice > static_cast<int>(suggestions.size())) {
        std::cout << "Opcao invalida." << std::endl;
        return "";
    }
    
    return suggestions[choice - 1];
}

// Função para calcular e exibir rota
void calculateRoute(const Graph& graph, const Trie& trie, 
                   const std::unordered_map<std::string, std::vector<long long>>& labelToNodes,
                   const std::unordered_map<long long, std::string>& nodesToLabel) {
    
    std::cout << "\n=== Calcular Rota ===" << std::endl;
    
    // Seleciona origem
    std::string originLabel = selectLocation(trie, "\nDigite o inicio do nome da ORIGEM: ");
    if (originLabel.empty()) {
        std::cout << "Origem nao selecionada." << std::endl;
        return;
    }
    std::cout << "Origem: " << originLabel << std::endl;
    
    // Seleciona destino
    std::string destLabel = selectLocation(trie, "\nDigite o inicio do nome do DESTINO: ");
    if (destLabel.empty()) {
        std::cout << "Destino nao selecionado." << std::endl;
        return;
    }
    std::cout << "Destino: " << destLabel << std::endl;
    
    // Obtém IDs dos nós
    auto originIt = labelToNodes.find(originLabel);
    auto destIt = labelToNodes.find(destLabel);
    
    if (originIt == labelToNodes.end() || destIt == labelToNodes.end()) {
        std::cout << "Erro: local nao encontrado no mapa." << std::endl;
        return;
    }
    
    // Usa o primeiro nó de cada label (pode haver múltiplos)
    long long originId = originIt->second[0];
    long long destId = destIt->second[0];
    
    std::cout << "\nCalculando rota..." << std::endl;
    
    // Executa Dijkstra
    PathResult result = Dijkstra::shortestPath(graph, originId, destId);
    
    if (!result.found) {
        std::cout << "\nNao foi possivel encontrar uma rota entre os locais." << std::endl;
        std::cout << "(Verifique se ha conexao viaria entre os pontos)" << std::endl;
        return;
    }
    
    // Exibe resultado
    std::cout << "\n========================================" << std::endl;
    std::cout << "          ROTA ENCONTRADA!" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Origem:  " << originLabel << std::endl;
    std::cout << "Destino: " << destLabel << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Distancia total: " << result.totalDistance << " metros" << std::endl;
    std::cout << "                 (" << (result.totalDistance / 1000.0) << " km)" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Caminho (" << result.path.size() << " pontos):" << std::endl;
    
    // Mostra os pontos do caminho (limitado para não poluir a tela)
    size_t maxDisplay = 15;
    for (size_t i = 0; i < result.path.size() && i < maxDisplay; i++) {
        long long nodeId = result.path[i];
        auto labelIt = nodesToLabel.find(nodeId);
        
        if (labelIt != nodesToLabel.end()) {
            std::cout << "  " << (i + 1) << ". " << labelIt->second << std::endl;
        } else {
            std::cout << "  " << (i + 1) << ". [No " << nodeId << "]" << std::endl;
        }
    }
    
    if (result.path.size() > maxDisplay) {
        std::cout << "  ... (" << (result.path.size() - maxDisplay) << " pontos omitidos)" << std::endl;
        
        // Mostra o último ponto
        long long lastNode = result.path.back();
        auto labelIt = nodesToLabel.find(lastNode);
        if (labelIt != nodesToLabel.end()) {
            std::cout << "  " << result.path.size() << ". " << labelIt->second << std::endl;
        }
    }
    
    std::cout << "========================================" << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Carregando dados de Pelotas..." << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Estruturas de dados
    Graph graph;
    Trie trie;
    std::unordered_map<std::string, std::vector<long long>> labelToNodes;
    std::unordered_map<long long, std::string> nodesToLabel;
    
    // Carrega dados
    DataLoader loader(".");  // Arquivos JSON no diretório atual
    
    if (!loader.loadNodes(graph)) {
        std::cerr << "Erro fatal: nao foi possivel carregar nodes.json" << std::endl;
        return 1;
    }
    
    if (!loader.loadEdges(graph)) {
        std::cerr << "Erro fatal: nao foi possivel carregar edges.json" << std::endl;
        return 1;
    }
    
    if (!loader.loadLabelToNodes(labelToNodes)) {
        std::cerr << "Erro fatal: nao foi possivel carregar label_to_nodes.json" << std::endl;
        return 1;
    }
    
    if (!loader.loadNodesToLabel(nodesToLabel)) {
        std::cerr << "Erro fatal: nao foi possivel carregar nodes_to_label.json" << std::endl;
        return 1;
    }
    
    loader.populateTrie(trie, labelToNodes);
    
    std::cout << "\nDados carregados com sucesso!" << std::endl;
    std::cout << "Grafo: " << graph.getNodeCount() << " nos, " << graph.getEdgeCount() << " arestas" << std::endl;
    
    // Loop principal
    int option;
    do {
        showMenu();
        std::cin >> option;
        clearInputBuffer();
        
        switch (option) {
            case 1:
                searchLocation(trie);
                break;
            case 2:
                calculateRoute(graph, trie, labelToNodes, nodesToLabel);
                break;
            case 3:
                std::cout << "\nAte logo!" << std::endl;
                break;
            default:
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
        }
    } while (option != 3);
    
    return 0;
}
