/**
 * @file Dijkstra.h
 * @brief Implementation of Dijkstra's algorithm for finding the shortest path.
 */

#pragma once

#include "graphs/IPathfindingStrategy.h"
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

namespace core {
namespace graphs {

/**
 * @class Dijkstra
 * @brief Concrete strategy implementing Dijkstra's pathfinding algorithm.
 *
 * This algorithm finds the shortest path between a starting node and a goal node
 * in a weighted graph with non-negative edge weights. It uses a priority queue.
 */
class Dijkstra : public IPathfindingStrategy {
public:
    /**
     * @brief Finds the shortest path from a start vertex to a goal vertex.
     * @param graph The directed graph to search in.
     * @param start The index of the starting vertex.
     * @param goal The index of the target vertex.
     * @return A vector of vertex indices representing the path from start to goal. Returns an empty vector if no path exists.
     */
    std::vector<int> findPath(const Graph& graph, int start, int goal) override {
        int v = graph.getNumVertices();
        std::vector<double> dist(v, std::numeric_limits<double>::infinity());
        std::vector<int> parent(v, -1);
        
        using pdi = std::pair<double, int>;
        std::priority_queue<pdi, std::vector<pdi>, std::greater<pdi>> pq;

        dist[start] = 0.0;
        pq.push({0.0, start});

        while (!pq.empty()) {
            double d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;
            
            if (u == goal) break;

            for (const auto& edge : graph.getNeighbors(u)) {
                int dest = edge.destination; // Renamed to avoid shadowing 'v'
                double weight = edge.weight;

                if (dist[u] + weight < dist[dest]) {
                    dist[dest] = dist[u] + weight;
                    parent[dest] = u;
                    pq.push({dist[dest], dest});
                }
            }
        }

        std::vector<int> path;
        if (dist[goal] != std::numeric_limits<double>::infinity()) {
            for (int at = goal; at != -1; at = parent[at]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
        }
        return path;
    }

    /**
     * @brief Returns the human-readable name of the algorithm.
     * @return The string "Dijkstra's Algorithm".
     */
    std::string getName() const override {
        return "Dijkstra's Algorithm";
    }
};

} // namespace graphs
} // namespace core
