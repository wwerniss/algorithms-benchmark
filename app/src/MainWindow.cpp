#include "MainWindow.h"
#include "SortingWindow.h"
#include "GraphWindow.h"
#include "TreeWindow.h"
#include "HistoryWindow.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUi() {
    setWindowTitle("Algorithms Benchmark & Visualization");
    resize(1200, 800); 

    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(5, 5, 5, 5); 

    auto *tabWidget = new QTabWidget(this);

    auto *sw = new SortingWindow(tabWidget);
    auto *gw = new GraphWindow(tabWidget);
    auto *tw = new TreeWindow(tabWidget);
    auto *hw = new HistoryWindow(tabWidget);

    tabWidget->addTab(sw, "Sorting Algorithms");
    tabWidget->addTab(gw, "Graph Algorithms");
    tabWidget->addTab(tw, "Tree Structures");
    tabWidget->addTab(hw, "Benchmark History");

    layout->addWidget(tabWidget);

    setCentralWidget(centralWidget);
}
