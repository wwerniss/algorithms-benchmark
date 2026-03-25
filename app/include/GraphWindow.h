#pragma once

#include <QWidget>
#include "GraphVisualizationWidget.h"
#include "graphs/Graph.h"
#include <QComboBox>
#include <QSpinBox>

class GraphWindow : public QWidget {
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = nullptr);
    ~GraphWindow() override;

private slots:
    void findPath();
    void generateGraph();

private:
    void setupUi();

    GraphVisualizationWidget *m_visualizer;
    core::graphs::Graph m_graph{0};
    
    QComboBox *m_algoCombo;
    QSpinBox *m_startNode;
    QSpinBox *m_endNode;
};
