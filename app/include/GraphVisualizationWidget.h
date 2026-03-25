#pragma once

#include <QWidget>
#include <vector>
#include "graphs/Graph.h"

class GraphVisualizationWidget : public QWidget {
    Q_OBJECT

public:
    explicit GraphVisualizationWidget(QWidget *parent = nullptr);
    ~GraphVisualizationWidget() override;

    void setGraph(const core::graphs::Graph& graph);
    void setPath(const std::vector<int>& path);
    void resetPath();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    core::graphs::Graph m_graph{0};
    std::vector<int> m_path;
    std::vector<QPointF> m_nodePositions;

    void calculateNodePositions();
};
