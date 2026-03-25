#pragma once

#include "graphs/IPathfindingStrategy.h"
#include <vector>

namespace core {
namespace graphs {

class DFS : public IPathfindingStrategy {
public:
    std::vector<int> findPath(const Graph& graph, int start, int goal) override {
        int v = graph.getNumVertices();
        std::vector<bool> visited(v, false);
        std::vector<int> path;
        
        if (dfsHelper(graph, start, goal, visited, path)) {
            return path;
        }
        return {};
    }

    std::string getName() const override {
        return "Depth-First Search (DFS)";
    }

private:
    bool dfsHelper(const Graph& graph, int current, int goal, std::vector<bool>& visited, std::vector<int>& path) {
        visited[current] = true;
        path.push_back(current);

        if (current == goal) {
            return true;
        }

        for (const auto& edge : graph.getNeighbors(current)) {
            if (!visited[edge.destination]) {
                if (dfsHelper(graph, edge.destination, goal, visited, path)) {
                    return true;
                }
            }
        }

        path.pop_back();
        return false;
    }
};

} // namespace graphs
} // namespace core
