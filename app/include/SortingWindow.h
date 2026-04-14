#pragma once

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QLabel>
#include <vector>
#include <memory>
#include <QSlider>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include "AudioSynthesizer.h"
#include "VisualizationWidget.h"
#include "sorting/ISortStrategy.h"
#include "patterns/Observer.h"
#include "patterns/Command.h"

class IWindowActivityState;

class SortingWindow : public QWidget, public core::patterns::IObserver<int> {
    Q_OBJECT
    friend class IdleState;
    friend class RunningState;
    friend class PausedState;

public:
    explicit SortingWindow(QWidget *parent = nullptr);
    ~SortingWindow() override;

    void onUpdate(const std::vector<int>& data) override;

private slots:
    void startSorting();
    void stepForward();
    void stepBackward(); // Undo
    void updateVisualization();
    void changeDelay(int value);
    void updateTimeLabel();
    void onTimerTick();
    void toggleSound();

private:
    void setupUi();
    void generateData();
    void setUIState(const std::vector<int>& data);

    void setState(std::unique_ptr<IWindowActivityState> state);
    void playAnimation();
    void pauseAnimation();

    VisualizationWidget *m_visualizer;
    QLabel *m_timeLabel;
    QSlider *m_delaySlider;
    QPushButton *m_startBtn;
    QPushButton *m_stepBackBtn;
    QPushButton *m_stepFwdBtn;
    QPushButton *m_playBtn;
    QPushButton *m_soundBtn;
    AudioSynthesizer *m_synthesizer;
    bool m_soundEnabled = true;

    QComboBox *m_algoCombo;
    QComboBox *m_sizeCombo;
    
    std::unique_ptr<IWindowActivityState> m_currentState;
    std::vector<int> m_data;
    
    std::vector<std::unique_ptr<core::patterns::ICommand>> m_commands;
    int m_commandIndex = -1; // Current state in history
    std::vector<int> m_lastState;
    
    QTimer *m_timer;
    QTimer *m_uiTimer;
    QElapsedTimer m_stopwatch;
    qint64 m_accumulatedTime = 0;
};
