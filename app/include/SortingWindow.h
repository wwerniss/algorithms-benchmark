#pragma once

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <vector>
#include <memory>
#include "VisualizationWidget.h"
#include "sorting/ISortStrategy.h"
#include "patterns/Observer.h"
#include "patterns/Command.h"

class SortingWindow : public QWidget, public core::patterns::IObserver<int> {
    Q_OBJECT

public:
    explicit SortingWindow(QWidget *parent = nullptr);
    ~SortingWindow() override;

    void onUpdate(const std::vector<int>& data) override;

private slots:
    void startSorting();
    void stepForward();
    void stepBackward(); // Undo
    void updateVisualization();

private:
    void setupUi();
    void generateData();
    void setUIState(const std::vector<int>& data);

    VisualizationWidget *m_visualizer;
    QLabel *m_timeLabel;
    std::vector<int> m_data;
    
    std::vector<std::unique_ptr<core::patterns::ICommand>> m_commands;
    int m_commandIndex = -1; // Current state in history
    std::vector<int> m_lastState;
    
    QTimer *m_timer;
};
