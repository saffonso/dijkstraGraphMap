#include "dijkstra.h"
#include <queue>
#include <unordered_map>
#include <algorithm>

PathResult Dijkstra::shortestPath(const Graph& graph, long long origin, long long destination) {
    PathResult result;
    
    // Verifica se os nós existem
    if (!graph.hasNode(origin) || !graph.hasNode(destination)) {
        return result;
    }
    
    // Tabela de distâncias (inicialmente infinito)
    std::unordered_map<long long, double> dist;
    
    // Tabela de predecessores para reconstruir o caminho
    std::unordered_map<long long, long long> predecessor;
    
    // Min-heap: (distância, nó)
    using PQElement = std::pair<double, long long>;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> pq;
    
    // Inicialização
    dist[origin] = 0;
    pq.push({0, origin});
    
    while (!pq.empty()) {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();
        
        // Chegou ao destino
        if (currentNode == destination) {
            result.found = true;
            result.totalDistance = currentDist;
            
            // Reconstrói o caminho
            long long node = destination;
            while (node != origin) {
                result.path.push_back(node);
                node = predecessor[node];
            }
            result.path.push_back(origin);
            std::reverse(result.path.begin(), result.path.end());
            
            return result;
        }
        
        // Ignora se já encontramos um caminho melhor
        if (dist.count(currentNode) && currentDist > dist[currentNode]) {
            continue;
        }
        
        // Explora vizinhos
        for (const auto& [neighbor, weight] : graph.getNeighbors(currentNode)) {
            double newDist = currentDist + weight;
            
            // Se encontramos um caminho melhor
            if (!dist.count(neighbor) || newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                predecessor[neighbor] = currentNode;
                pq.push({newDist, neighbor});
            }
        }
    }
    
    // Não encontrou caminho
    return result;
}
