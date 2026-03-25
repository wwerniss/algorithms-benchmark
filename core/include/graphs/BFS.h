#pragma once

#include "graphs/IPathfindingStrategy.h"
#include <queue>

namespace core {
namespace graphs {

class BFS : public IPathfindingStrategy {
public:
    std::vector<int> findPath(const Graph& graph, int start, int goal) override {
        int v = graph.getNumVertices();
        std::vector<bool> visited(v, false);
        std::vector<int> parent(v, -1);
        std::queue<int> q;

        visited[start] = true;
        q.push(start);

        bool found = false;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == goal) {
                found = true;
                break;
            }

            for (const auto& edge : graph.getNeighbors(current)) {
                if (!visited[edge.destination]) {
                    visited[edge.destination] = true;
                    parent[edge.destination] = current;
                    q.push(edge.destination);
                }
            }
        }

        std::vector<int> path;
        if (found) {
            for (int at = goal; at != -1; at = parent[at]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
        }
        return path;
    }

    std::string getName() const override {
        return "Breadth-First Search (BFS)";
    }
};

} // namespace graphs
} // namespace core
