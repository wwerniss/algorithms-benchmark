#include "HistoryWindow.h"
#include "benchmarks/BenchmarkHistoryManager.h"
#include <QHeaderView>

HistoryWindow::HistoryWindow(QWidget *parent) : QWidget(parent) {
    setupUi();
    
    // Initial populate
    populateTable(core::benchmarks::BenchmarkHistoryManager::getInstance().getHistory());
    
    // Subscribe to future updates
    core::benchmarks::BenchmarkHistoryManager::getInstance().addObserver(this);
}

HistoryWindow::~HistoryWindow() {
    core::benchmarks::BenchmarkHistoryManager::getInstance().removeObserver(this);
}

void HistoryWindow::setupUi() {
    auto *layout = new QVBoxLayout(this);
    
    m_table = new QTableWidget(0, 3, this);
    m_table->setHorizontalHeaderLabels({"Algorithm", "Context", "Duration (ms)"});
    m_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    m_clearBtn = new QPushButton("Clear History (View Only)", this);
    connect(m_clearBtn, &QPushButton::clicked, this, [this]() {
        m_table->setRowCount(0);
    });
    
    layout->addWidget(m_table);
    layout->addWidget(m_clearBtn);
}

void HistoryWindow::onUpdate(const std::vector<core::benchmarks::BenchmarkRecord>& history) {
    populateTable(history);
}

void HistoryWindow::populateTable(const std::vector<core::benchmarks::BenchmarkRecord>& history) {
    m_table->setRowCount(0);
    for (const auto& record : history) {
        int row = m_table->rowCount();
        m_table->insertRow(row);
        m_table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(record.algorithmName)));
        m_table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(record.context)));
        m_table->setItem(row, 2, new QTableWidgetItem(QString::number(record.durationMs, 'f', 3)));
    }
}
