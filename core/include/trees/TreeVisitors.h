#pragma once

#include "ITreeVisitor.h"
#include <string>
#include <sstream>

namespace core {
namespace trees {

/**
 * @class TreeSerializationVisitor
 * @brief A concrete visitor that serializes traversed tree nodes into a formatted string array format.
 */
template<typename T>
class TreeSerializationVisitor : public ITreeVisitor<T> {
private:
    std::ostringstream buffer; ///< Internal buffer handling string construction.
    bool isFirst = true;       ///< Flag to manage commas appropriately without a trailing comma.

public:
    /**
     * @brief Visits a node and appends its data to the buffer.
     * @param node The tree node to serialize.
     */
    void visit(const TreeNode<T>* node) override {
        if (!node) return;
        
        if (!isFirst) {
            buffer << ", ";
        }
        buffer << node->data;
        isFirst = false;
    }
    
    /**
     * @brief Returns the built serialized string.
     * @return Formatted string resembling a JSON array.
     */
    std::string getResult() const {
        return "[" + buffer.str() + "]";
    }
    
    /**
     * @brief Resets the builder state for reusing the visitor on a fresh traversal.
     */
    void reset() {
        buffer.str("");
        buffer.clear();
        isFirst = true;
    }
};

/**
 * @class TreeCounterVisitor
 * @brief A concrete visitor that counts the total number of nodes encountered in a traversal.
 */
template<typename T>
class TreeCounterVisitor : public ITreeVisitor<T> {
private:
    int count = 0;
    
public:
    /**
     * @brief Visits a node and increments the internal counter.
     * @param node The tree node visited.
     */
    void visit(const TreeNode<T>* node) override {
        if (node) {
            count++;
        }
    }
    
    /**
     * @brief Retrieves the final node count.
     * @return The integer volume of nodes counted.
     */
    int getCount() const {
        return count;
    }
    
    /**
     * @brief Clears the counter to zero.
     */
    void reset() {
        count = 0;
    }
};

} // namespace trees
} // namespace core
