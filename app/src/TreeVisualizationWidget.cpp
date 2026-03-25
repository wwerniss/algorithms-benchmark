#include "TreeVisualizationWidget.h"
#include <QPainter>
#include <QPaintEvent>

TreeVisualizationWidget::TreeVisualizationWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(400, 400);
}

TreeVisualizationWidget::~TreeVisualizationWidget() = default;

void TreeVisualizationWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    if (m_nodes.empty()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw all edges first so they are under the nodes
    painter.setPen(QPen(Qt::gray, 2));
    for (const auto& node : m_nodes) {
        if (node.leftChildIdx != -1) {
            const auto& left = m_nodes[node.leftChildIdx];
            painter.drawLine(node.x, node.y, left.x, left.y);
        }
        if (node.rightChildIdx != -1) {
            const auto& right = m_nodes[node.rightChildIdx];
            painter.drawLine(node.x, node.y, right.x, right.y);
        }
    }

    // Draw nodes
    int radius = 18;
    for (const auto& node : m_nodes) {
        painter.setBrush(Qt::green);
        painter.setPen(Qt::black);
        
        painter.drawEllipse(QPoint(node.x, node.y), radius, radius);

        painter.setPen(Qt::black);
        painter.drawText(QRect(node.x - radius, node.y - radius, radius * 2, radius * 2), 
                         Qt::AlignCenter, QString::number(node.data));
    }
}
