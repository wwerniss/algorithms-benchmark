#pragma once

#include "graphs/Graph.h"
#include <vector>
#include <string>

namespace core {
namespace graphs {

class IPathfindingStrategy {
public:
    virtual ~IPathfindingStrategy() = default;
    
    // Returns a vector representing the path from start to goal.
    // If no path is found, returns an empty vector.
    virtual std::vector<int> findPath(const Graph& graph, int start, int goal) = 0;
    
    virtual std::string getName() const = 0;
};

} // namespace graphs
} // namespace core
