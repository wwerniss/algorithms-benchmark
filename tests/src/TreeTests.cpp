#include <gtest/gtest.h>
#include "trees/BST.h"
#include "trees/AVLTree.h"

using namespace core::trees;

TEST(TreeTests, BSTInsertAndTraversal) {
    BST<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    auto result = bst.inorderTraversal();
    std::vector<int> expected = {20, 30, 40, 50, 60, 70, 80};
    
    EXPECT_EQ(result, expected);
}

TEST(TreeTests, AVLTreeInsertAndTraversal) {
    AVLTree<int> avl;
    // Inserting in a way that causes rotations
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);

    auto result = avl.inorderTraversal();
    std::vector<int> expected = {10, 20, 25, 30, 40, 50};
    
    EXPECT_EQ(result, expected);
}

TEST(TreeTests, EmptyTree) {
    BST<int> bst;
    EXPECT_TRUE(bst.inorderTraversal().empty());
    
    AVLTree<int> avl;
    EXPECT_TRUE(avl.inorderTraversal().empty());
}
