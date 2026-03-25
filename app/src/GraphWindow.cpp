#include "GraphWindow.h"
#include "graphs/BFS.h"
#include "graphs/DFS.h"
#include "graphs/Dijkstra.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <random>

GraphWindow::GraphWindow(QWidget *parent) : QWidget(parent) {
    setupUi();
    generateGraph();
}

GraphWindow::~GraphWindow() = default;

void GraphWindow::setupUi() {
    setWindowTitle("Graph Algorithm Visualization");
    resize(700, 500);

    auto *mainLayout = new QVBoxLayout(this);
    auto *controlsLayout = new QHBoxLayout();
    
    m_algoCombo = new QComboBox(this);
    m_algoCombo->addItem("BFS");
    m_algoCombo->addItem("DFS");
    m_algoCombo->addItem("Dijkstra");
    
    m_startNode = new QSpinBox(this);
    m_startNode->setPrefix("Start: ");
    
    m_endNode = new QSpinBox(this);
    m_endNode->setPrefix("End: ");
    
    auto *findBtn = new QPushButton("Find Path", this);
    connect(findBtn, &QPushButton::clicked, this, &GraphWindow::findPath);
    
    auto *genBtn = new QPushButton("Generate Random Graph", this);
    connect(genBtn, &QPushButton::clicked, this, &GraphWindow::generateGraph);

    controlsLayout->addWidget(new QLabel("Algorithm:"));
    controlsLayout->addWidget(m_algoCombo);
    controlsLayout->addWidget(m_startNode);
    controlsLayout->addWidget(m_endNode);
    controlsLayout->addWidget(findBtn);
    controlsLayout->addWidget(genBtn);
    controlsLayout->addStretch();

    m_visualizer = new GraphVisualizationWidget(this);

    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(m_visualizer, 1);
}

void GraphWindow::generateGraph() {
    int numNodes = 12; // Example fixed size
    m_graph = core::graphs::Graph(numNodes);
    
    m_startNode->setRange(0, numNodes - 1);
    m_endNode->setRange(0, numNodes - 1);
    m_startNode->setValue(0);
    m_endNode->setValue(numNodes - 1);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    // Random edges
    for (int i = 0; i < numNodes; ++i) {
        int edges = (dis(gen) % 3) + 1; // 1 to 3 edges per node
        for (int e = 0; e < edges; ++e) {
            int target = dis(gen) % numNodes;
            if (target != i) {
                m_graph.addEdge(i, target, dis(gen) % 10 + 1);
            }
        }
    }
    
    m_visualizer->setGraph(m_graph);
    m_visualizer->resetPath();
}

void GraphWindow::findPath() {
    QString algo = m_algoCombo->currentText();
    int start = m_startNode->value();
    int end = m_endNode->value();
    
    std::unique_ptr<core::graphs::IPathfindingStrategy> strategy;
    
    if (algo == "BFS") {
        strategy = std::make_unique<core::graphs::BFS>();
    } else if (algo == "DFS") {
        strategy = std::make_unique<core::graphs::DFS>();
    } else if (algo == "Dijkstra") {
        strategy = std::make_unique<core::graphs::Dijkstra>();
    }
    
    if (strategy) {
        auto path = strategy->findPath(m_graph, start, end);
        m_visualizer->setPath(path);
    }
}
