#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <utility>

struct Node {
    long long id;
    double x;  // longitude
    double y;  // latitude
    
    Node() : id(0), x(0), y(0) {}
    Node(long long id, double x, double y) : id(id), x(x), y(y) {}
};

class Graph {
private:
    // Mapa de ID do nó para informações do nó
    std::unordered_map<long long, Node> nodes;
    
    // Lista de adjacência: nó origem -> vetor de (nó destino, peso/distância)
    std::unordered_map<long long, std::vector<std::pair<long long, double>>> adjacencyList;

public:
    Graph() = default;
    
    // Adiciona um nó ao grafo
    void addNode(long long id, double x, double y);
    
    // Adiciona uma aresta direcionada de u para v com peso weight
    void addEdge(long long u, long long v, double weight);
    
    // Retorna os vizinhos de um nó (para Dijkstra)
    const std::vector<std::pair<long long, double>>& getNeighbors(long long nodeId) const;
    
    // Verifica se um nó existe
    bool hasNode(long long nodeId) const;
    
    // Retorna informações de um nó
    const Node& getNode(long long nodeId) const;
    
    // Retorna o número de nós
    size_t getNodeCount() const;
    
    // Retorna o número de arestas
    size_t getEdgeCount() const;
};

#endif // GRAPH_H
