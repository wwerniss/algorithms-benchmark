#pragma once

#include <QWidget>
#include <vector>

class VisualizationWidget : public QWidget {
    Q_OBJECT

public:
    explicit VisualizationWidget(QWidget *parent = nullptr);
    ~VisualizationWidget() override;

    void setData(const std::vector<int>& data);
    void setHighlighted(int index1, int index2);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<int> m_data;
    int m_highlight1 = -1;
    int m_highlight2 = -1;
};
