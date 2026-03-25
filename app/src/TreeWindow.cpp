#include "TreeWindow.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QRandomGenerator>

TreeWindow::TreeWindow(QWidget *parent) : QWidget(parent) {
    setupUi();
    resetTree();
}

TreeWindow::~TreeWindow() = default;

void TreeWindow::setupUi() {
    setWindowTitle("Tree Structure Visualization");
    resize(700, 500);

    auto *mainLayout = new QVBoxLayout(this);
    auto *controlsLayout = new QHBoxLayout();
    
    m_treeCombo = new QComboBox(this);
    m_treeCombo->addItem("Binary Search Tree (BST)");
    m_treeCombo->addItem("AVL Tree");
    connect(m_treeCombo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &TreeWindow::resetTree);
    
    m_valSpinBox = new QSpinBox(this);
    m_valSpinBox->setRange(1, 999);
    m_valSpinBox->setValue(50);
    
    auto *insertBtn = new QPushButton("Insert Node", this);
    connect(insertBtn, &QPushButton::clicked, this, &TreeWindow::insertNode);
    
    auto *resetBtn = new QPushButton("Clear Tree", this);
    connect(resetBtn, &QPushButton::clicked, this, &TreeWindow::resetTree);

    controlsLayout->addWidget(new QLabel("Tree Type:"));
    controlsLayout->addWidget(m_treeCombo);
    controlsLayout->addWidget(new QLabel("Value:"));
    controlsLayout->addWidget(m_valSpinBox);
    controlsLayout->addWidget(insertBtn);
    controlsLayout->addWidget(resetBtn);
    controlsLayout->addStretch();

    m_visualizer = new TreeVisualizationWidget(this);

    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(m_visualizer, 1);
}

void TreeWindow::resetTree() {
    QString type = m_treeCombo->currentText();
    
    if (type == "AVL Tree") {
        m_avl = std::make_unique<core::trees::AVLTree<int>>();
        m_bst.reset();
    } else {
        m_bst = std::make_unique<core::trees::BST<int>>();
        m_avl.reset();
    }
    
    updateVisualization();
}

void TreeWindow::insertNode() {
    int val = m_valSpinBox->value();
    
    if (m_bst) m_bst->insert(val);
    if (m_avl) m_avl->insert(val);
    
    m_valSpinBox->setValue(QRandomGenerator::global()->bounded(1, 100)); // Randomize next value for convenience
    
    updateVisualization();
}

void TreeWindow::updateVisualization() {
    if (m_bst) {
        m_visualizer->setTree(m_bst->getRoot());
    } else if (m_avl) {
        m_visualizer->setTree(m_avl->getRoot());
    }
}
