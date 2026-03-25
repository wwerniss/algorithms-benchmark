#include "MainWindow.h"
#include "SortingWindow.h"
#include "GraphWindow.h"
#include "TreeWindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUi() {
    setWindowTitle("Algorithms Benchmark & Visualization");
    resize(400, 300);

    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);

    auto *titleLabel = new QLabel("Select an Algorithm Category:", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 20px;");
    layout->addWidget(titleLabel);

    auto *btnSorting = new QPushButton("Sorting Algorithms", this);
    auto *btnGraphs = new QPushButton("Graph Algorithms", this);
    auto *btnTrees = new QPushButton("Tree Structures", this);

    connect(btnSorting, &QPushButton::clicked, this, [this]() {
        auto *sw = new SortingWindow();
        sw->setAttribute(Qt::WA_DeleteOnClose);
        sw->show();
    });

    connect(btnGraphs, &QPushButton::clicked, this, [this]() {
        auto *gw = new GraphWindow();
        gw->setAttribute(Qt::WA_DeleteOnClose);
        gw->show();
    });

    connect(btnTrees, &QPushButton::clicked, this, [this]() {
        auto *tw = new TreeWindow();
        tw->setAttribute(Qt::WA_DeleteOnClose);
        tw->show();
    });

    layout->addWidget(btnSorting);
    layout->addWidget(btnGraphs);
    layout->addWidget(btnTrees);

    layout->addStretch();

    setCentralWidget(centralWidget);
}
