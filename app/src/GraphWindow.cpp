#include "GraphWindow.h"
#include "graphs/BFS.h"
#include "graphs/DFS.h"
#include "graphs/Dijkstra.h"
#include "graphs/GraphBuilder.h"
#include "benchmarks/BenchmarkHistoryManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QElapsedTimer>
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

    m_timeLabel = new QLabel("Time: 0 ms");

    controlsLayout->addWidget(new QLabel("Algorithm:"));
    controlsLayout->addWidget(m_algoCombo);
    controlsLayout->addWidget(m_startNode);
    controlsLayout->addWidget(m_endNode);
    controlsLayout->addWidget(findBtn);
    controlsLayout->addWidget(genBtn);
    controlsLayout->addWidget(m_timeLabel);
    controlsLayout->addStretch();

    m_visualizer = new GraphVisualizationWidget(this);

    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(m_visualizer, 1);
}

void GraphWindow::generateGraph() {
    int numNodes = 12; // Example fixed size
    
    core::graphs::GraphBuilder builder;
    m_graph = *builder.addNodes(numNodes)
                      .connectLinear(1.0)
                      .connectRandomly(0.25, 1.0, 10.0)
                      .build();
                      
    m_startNode->setRange(0, numNodes - 1);
    m_endNode->setRange(0, numNodes - 1);
    m_startNode->setValue(0);
    m_endNode->setValue(numNodes - 1);
    
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
        QElapsedTimer timer;
        timer.start();
        auto path = strategy->findPath(m_graph, start, end);
        qint64 elapsed = timer.nsecsElapsed();
        
        m_visualizer->setPath(path);
        
        double elapedMs = elapsed / 1000000.0;
        m_timeLabel->setText(QString("Time: %1 ms").arg(elapedMs, 0, 'f', 3));
        
        std::string contextStr = "Graph: " + std::to_string(m_graph.getNumVertices()) + 
                                 " nodes, Path: " + std::to_string(start) + " -> " + std::to_string(end);
                                 
        core::benchmarks::BenchmarkHistoryManager::getInstance().addRecord(
            {algo.toStdString(), contextStr, elapedMs}
        );
    }
}
