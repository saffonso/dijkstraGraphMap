#include "graph.h"

void Graph::addNode(long long id, double x, double y) {
    nodes[id] = Node(id, x, y);
    // Inicializa lista de adjacência vazia para o nó
    if (adjacencyList.find(id) == adjacencyList.end()) {
        adjacencyList[id] = std::vector<std::pair<long long, double>>();
    }
}

void Graph::addEdge(long long u, long long v, double weight) {
    adjacencyList[u].emplace_back(v, weight);
}

const std::vector<std::pair<long long, double>>& Graph::getNeighbors(long long nodeId) const {
    static const std::vector<std::pair<long long, double>> empty;
    auto it = adjacencyList.find(nodeId);
    if (it != adjacencyList.end()) {
        return it->second;
    }
    return empty;
}

bool Graph::hasNode(long long nodeId) const {
    return nodes.find(nodeId) != nodes.end();
}

const Node& Graph::getNode(long long nodeId) const {
    return nodes.at(nodeId);
}

size_t Graph::getNodeCount() const {
    return nodes.size();
}

size_t Graph::getEdgeCount() const {
    size_t count = 0;
    for (const auto& pair : adjacencyList) {
        count += pair.second.size();
    }
    return count;
}
