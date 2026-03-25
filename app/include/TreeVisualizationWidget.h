#pragma once

#include <QWidget>
#include <vector>

struct DrawNode {
    int data;
    int x, y;
    int leftChildIdx = -1;
    int rightChildIdx = -1;
};

class TreeVisualizationWidget : public QWidget {
    Q_OBJECT

public:
    explicit TreeVisualizationWidget(QWidget *parent = nullptr);
    ~TreeVisualizationWidget() override;

    template<typename NodeType>
    void setTree(const NodeType* root) {
        m_nodes.clear();
        if (root) {
            buildDrawTree(root, 0, width() / 2, width() / 4);
        }
        update();
    }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<DrawNode> m_nodes;

    template<typename NodeType>
    int buildDrawTree(const NodeType* node, int depth, int x, int xOffset) {
        if (!node) return -1;
        
        int idx = m_nodes.size();
        m_nodes.push_back({node->data, x, 50 + depth * 60, -1, -1});
        
        int left = buildDrawTree(node->left.get(), depth + 1, x - xOffset, xOffset / 2);
        int right = buildDrawTree(node->right.get(), depth + 1, x + xOffset, xOffset / 2);
        
        m_nodes[idx].leftChildIdx = left;
        m_nodes[idx].rightChildIdx = right;
        
        return idx;
    }
};
