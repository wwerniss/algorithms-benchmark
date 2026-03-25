#pragma once

#include <QWidget>
#include "TreeVisualizationWidget.h"
#include "trees/BST.h"
#include "trees/AVLTree.h"
#include <QComboBox>
#include <QSpinBox>

class TreeWindow : public QWidget {
    Q_OBJECT

public:
    explicit TreeWindow(QWidget *parent = nullptr);
    ~TreeWindow() override;

private slots:
    void insertNode();
    void resetTree();

private:
    void setupUi();
    void updateVisualization();

    TreeVisualizationWidget *m_visualizer;
    
    QComboBox *m_treeCombo;
    QSpinBox *m_valSpinBox;
    
    std::unique_ptr<core::trees::BST<int>> m_bst;
    std::unique_ptr<core::trees::AVLTree<int>> m_avl;
};
