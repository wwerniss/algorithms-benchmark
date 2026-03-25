#include "GraphVisualizationWidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <cmath>

GraphVisualizationWidget::GraphVisualizationWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(400, 400);
}

GraphVisualizationWidget::~GraphVisualizationWidget() = default;

void GraphVisualizationWidget::setGraph(const core::graphs::Graph& graph) {
    m_graph = graph;
    calculateNodePositions();
    update();
}

void GraphVisualizationWidget::setPath(const std::vector<int>& path) {
    m_path = path;
    update();
}

void GraphVisualizationWidget::resetPath() {
    m_path.clear();
    update();
}

void GraphVisualizationWidget::calculateNodePositions() {
    m_nodePositions.clear();
    int n = m_graph.getNumVertices();
    if (n == 0) return;

    int w = width();
    int h = height();
    int cx = w / 2;
    int cy = h / 2;
    double radius = std::min(w, h) / 2.0 * 0.8;

    for (int i = 0; i < n; ++i) {
        double angle = i * 2.0 * M_PI / n;
        double x = cx + radius * std::cos(angle);
        double y = cy + radius * std::sin(angle);
        m_nodePositions.push_back(QPointF(x, y));
    }
}

void GraphVisualizationWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    if (m_graph.getNumVertices() == 0 || m_nodePositions.empty()) return;

    // Recalculate on resize
    calculateNodePositions();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw all edges
    painter.setPen(QPen(Qt::gray, 1));
    for (int i = 0; i < m_graph.getNumVertices(); ++i) {
        for (const auto& edge : m_graph.getNeighbors(i)) {
            painter.drawLine(m_nodePositions[i], m_nodePositions[edge.destination]);
        }
    }

    // Draw path edges
    if (m_path.size() > 1) {
        painter.setPen(QPen(Qt::red, 3));
        for (size_t i = 0; i < m_path.size() - 1; ++i) {
            painter.drawLine(m_nodePositions[m_path[i]], m_nodePositions[m_path[i+1]]);
        }
    }

    // Draw nodes
    int nodeRadius = 15;
    for (int i = 0; i < m_graph.getNumVertices(); ++i) {
        bool inPath = std::find(m_path.begin(), m_path.end(), i) != m_path.end();
        painter.setBrush(inPath ? Qt::red : Qt::blue);
        painter.setPen(Qt::black);
        
        QPointF pos = m_nodePositions[i];
        painter.drawEllipse(pos, nodeRadius, nodeRadius);

        // Draw node ID
        painter.setPen(Qt::white);
        painter.drawText(QRectF(pos.x() - nodeRadius, pos.y() - nodeRadius, nodeRadius*2, nodeRadius*2), 
                         Qt::AlignCenter, QString::number(i));
    }
}
