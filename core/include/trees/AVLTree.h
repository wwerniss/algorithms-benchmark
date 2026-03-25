#pragma once

#include "trees/BST.h"
#include <algorithm>

namespace core {
namespace trees {

template<typename T>
struct AVLNode {
    T data;
    std::unique_ptr<AVLNode<T>> left;
    std::unique_ptr<AVLNode<T>> right;
    int height;
    
    explicit AVLNode(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

template<typename T>
class AVLTree {
private:
    std::unique_ptr<AVLNode<T>> root;

    int height(const std::unique_ptr<AVLNode<T>>& node) {
        if (!node) return 0;
        return node->height;
    }

    int getBalance(const std::unique_ptr<AVLNode<T>>& node) {
        if (!node) return 0;
        return height(node->left) - height(node->right);
    }

    std::unique_ptr<AVLNode<T>> rightRotate(std::unique_ptr<AVLNode<T>> y) {
        std::unique_ptr<AVLNode<T>> x = std::move(y->left);
        std::unique_ptr<AVLNode<T>> T2 = std::move(x->right);

        x->right = std::move(y);
        x->right->left = std::move(T2);

        x->right->height = std::max(height(x->right->left), height(x->right->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    std::unique_ptr<AVLNode<T>> leftRotate(std::unique_ptr<AVLNode<T>> x) {
        std::unique_ptr<AVLNode<T>> y = std::move(x->right);
        std::unique_ptr<AVLNode<T>> T2 = std::move(y->left);

        y->left = std::move(x);
        y->left->right = std::move(T2);

        y->left->height = std::max(height(y->left->left), height(y->left->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    std::unique_ptr<AVLNode<T>> insertRec(std::unique_ptr<AVLNode<T>> node, T val) {
        if (!node) {
            return std::make_unique<AVLNode<T>>(val);
        }

        if (val < node->data) {
            node->left = insertRec(std::move(node->left), val);
        } else if (val > node->data) {
            node->right = insertRec(std::move(node->right), val);
        } else {
            return node; // Duplicate keys not allowed
        }

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && val < node->left->data) {
            return rightRotate(std::move(node));
        }

        // Right Right Case
        if (balance < -1 && val > node->right->data) {
            return leftRotate(std::move(node));
        }

        // Left Right Case
        if (balance > 1 && val > node->left->data) {
            node->left = leftRotate(std::move(node->left));
            return rightRotate(std::move(node));
        }

        // Right Left Case
        if (balance < -1 && val < node->right->data) {
            node->right = rightRotate(std::move(node->right));
            return leftRotate(std::move(node));
        }

        return node;
    }

    void inorderRec(const AVLNode<T>* node, std::vector<T>& result) const {
        if (node) {
            inorderRec(node->left.get(), result);
            result.push_back(node->data);
            inorderRec(node->right.get(), result);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    const AVLNode<T>* getRoot() const { return root.get(); }

    void insert(T val) {
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
