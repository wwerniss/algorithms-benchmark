#pragma once

#include <vector>

namespace core {
namespace patterns {

template<typename T>
class IStrategy {
public:
    virtual ~IStrategy() = default;
    
    // Executes the algorithm. For sorting, this modifies the vector in-place.
    // For graphs/trees, this might behave differently. 
    // We can define specific strategies like ISortStrategy, IGraphStrategy later.
    virtual void execute(std::vector<T>& data) = 0;
};

} // namespace patterns
} // namespace core
