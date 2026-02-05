#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include <vector>
#include <limits>

struct PathResult {
    std::vector<long long> path;  // Sequência de nós do caminho
    double totalDistance;          // Distância total em metros
    bool found;                    // Se encontrou um caminho
    
    PathResult() : totalDistance(0), found(false) {}
};

class Dijkstra {
public:
    // Calcula o caminho mais curto entre origin e destination
    static PathResult shortestPath(const Graph& graph, long long origin, long long destination);
};

#endif // DIJKSTRA_H
