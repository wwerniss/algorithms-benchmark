#include "VisualizationWidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <algorithm>

VisualizationWidget::VisualizationWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(400, 300);
}

VisualizationWidget::~VisualizationWidget() = default;

void VisualizationWidget::setData(const std::vector<int>& data) {
    m_data = data;
    update();
}

void VisualizationWidget::setHighlighted(int index1, int index2) {
    m_highlight1 = index1;
    m_highlight2 = index2;
    update();
}

void VisualizationWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    if (m_data.empty()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int width = this->width();
    int height = this->height();

    int maxVal = *std::max_element(m_data.begin(), m_data.end());
    if (maxVal == 0) maxVal = 1;

    double barWidth = static_cast<double>(width) / m_data.size();

    for (size_t i = 0; i < m_data.size(); ++i) {
        double barHeight = (static_cast<double>(m_data[i]) / maxVal) * height;
        
        QRectF rect(i * barWidth, height - barHeight, barWidth - 1, barHeight);
        
        if (i == m_highlight1 || i == m_highlight2) {
            painter.setBrush(Qt::red);
        } else {
            painter.setBrush(Qt::blue);
        }
        
        painter.setPen(Qt::black);
        painter.drawRect(rect);
    }
}
