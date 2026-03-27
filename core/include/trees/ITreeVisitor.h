#pragma once

namespace core {
namespace trees {

// Forward declaration
template<typename T>
struct TreeNode;

/**
 * @class ITreeVisitor
 * @brief Interface for the Visitor design pattern applied to binary trees.
 * 
 * Allows defining new operations on tree nodes (like serialization, counting, evaluation)
 * without modifying the internal structure of the tree nodes themselves.
 */
template<typename T>
class ITreeVisitor {
public:
    virtual ~ITreeVisitor() = default;
    
    /**
     * @brief Visits a specific tree node to perform an operation.
     * @param node The node currently being visited.
     */
    virtual void visit(const TreeNode<T>* node) = 0;
};

} // namespace trees
} // namespace core
