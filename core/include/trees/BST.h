#pragma once

#include <memory>
#include <vector>

namespace core {
namespace trees {

template<typename T>
struct TreeNode {
    T data;
    std::unique_ptr<TreeNode<T>> left;
    std::unique_ptr<TreeNode<T>> right;
    
    explicit TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
protected:
    std::unique_ptr<TreeNode<T>> root;

    virtual std::unique_ptr<TreeNode<T>> insertRec(std::unique_ptr<TreeNode<T>> node, T val) {
        if (!node) {
            return std::make_unique<TreeNode<T>>(val);
        }
        if (val < node->data) {
            node->left = insertRec(std::move(node->left), val);
        } else if (val > node->data) {
            node->right = insertRec(std::move(node->right), val);
        }
        return node;
    }

    void inorderRec(const TreeNode<T>* node, std::vector<T>& result) const {
        if (node) {
            inorderRec(node->left.get(), result);
            result.push_back(node->data);
            inorderRec(node->right.get(), result);
        }
    }

public:
    BST() : root(nullptr) {}
    virtual ~BST() = default;

    const TreeNode<T>* getRoot() const { return root.get(); }

    virtual void insert(T val) {
        root = insertRec(std::move(root), val);
    }

    std::vector<T> inorderTraversal() const {
        std::vector<T> result;
        inorderRec(root.get(), result);
        return result;
    }
};

} // namespace trees
} // namespace core
