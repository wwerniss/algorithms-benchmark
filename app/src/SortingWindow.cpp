#include "SortingWindow.h"
#include "sorting/SortFactory.h"
#include "sorting/StepCommand.h"
#include "states/SortingWindowStates.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QSlider>
#include <QMessageBox>
#include <QLabel>
#include <random>
#include <QDateTime>
#include "sorting/SortBenchmarkFacade.h"

SortingWindow::SortingWindow(QWidget *parent) : QWidget(parent) {
    setupUi();
    generateData();
    
    m_currentState = std::make_unique<IdleState>();
    m_currentState->updateUI(this);
    
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SortingWindow::onTimerTick);
    
    m_uiTimer = new QTimer(this);
    connect(m_uiTimer, &QTimer::timeout, this, &SortingWindow::updateTimeLabel);
}

SortingWindow::~SortingWindow() = default;

void SortingWindow::setupUi() {
    setWindowTitle("Sorting Algorithm Visualization");
    resize(1200, 600);

    auto *mainLayout = new QVBoxLayout(this);
    auto *topControlsLayout = new QHBoxLayout();
    auto *bottomControlsLayout = new QHBoxLayout();
    
    m_algoCombo = new QComboBox(this);
    m_algoCombo->addItem("QuickSort");
    m_algoCombo->addItem("MergeSort");
    m_algoCombo->addItem("BubbleSort");
    m_algoCombo->addItem("SelectionSort");
    m_algoCombo->addItem("InsertionSort");
    m_algoCombo->setObjectName("algoCombo");
    
    m_sizeCombo = new QComboBox(this);
    m_sizeCombo->addItems({"32", "64", "128", "256"});
    m_sizeCombo->setCurrentText("64");
    m_sizeCombo->setToolTip("Array Size");
    
    m_startBtn = new QPushButton("Generate & Sort", this);
    connect(m_startBtn, &QPushButton::clicked, this, &SortingWindow::startSorting);
    
    m_stepBackBtn = new QPushButton("<< Undo", this);
    connect(m_stepBackBtn, &QPushButton::clicked, this, &SortingWindow::stepBackward);

    m_stepFwdBtn = new QPushButton("Step >>", this);
    connect(m_stepFwdBtn, &QPushButton::clicked, this, &SortingWindow::stepForward);

    m_playBtn = new QPushButton("Play/Pause", this);
    connect(m_playBtn, &QPushButton::clicked, this, [this](){
        if (m_currentState) m_currentState->handlePlayPause(this);
    });

    m_timeLabel = new QLabel("Time: 0 ms");

    auto *sliderLayoutContainer = new QWidget(this);
    auto *sliderVLayout = new QVBoxLayout(sliderLayoutContainer);
    sliderVLayout->setContentsMargins(0, 0, 0, 0);
    sliderVLayout->setSpacing(2);

    m_delaySlider = new QSlider(Qt::Horizontal, this);
    m_delaySlider->setRange(1, 11);
    m_delaySlider->setValue(11);
    m_delaySlider->setTickPosition(QSlider::TicksBelow);
    m_delaySlider->setTickInterval(1);
    m_delaySlider->setSingleStep(1);
    m_delaySlider->setPageStep(1);
    m_delaySlider->setMinimumWidth(200);
    m_delaySlider->setToolTip("Animation Speed (RT)");
    connect(m_delaySlider, &QSlider::valueChanged, this, &SortingWindow::changeDelay);

    auto *sliderLabelsHLayout = new QHBoxLayout();
    sliderLabelsHLayout->setContentsMargins(0, 0, 0, 0);
    auto *lblMin = new QLabel("0.1x", this);
    auto *lblMid = new QLabel("0.5x", this);
    auto *lblMax = new QLabel("1.0x", this);
    auto *lblRT = new QLabel("RT", this);
    
    QFont smallFont = lblMin->font();
    smallFont.setPointSize(10);
    lblMin->setFont(smallFont);
    lblMid->setFont(smallFont);
    lblMax->setFont(smallFont);
    lblRT->setFont(smallFont);
    
    lblMin->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    lblMid->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblMax->setAlignment(Qt::AlignRight | Qt::AlignTop);
    lblRT->setAlignment(Qt::AlignRight | Qt::AlignTop);

    sliderLabelsHLayout->addWidget(lblMin);
    sliderLabelsHLayout->addStretch(4);
    sliderLabelsHLayout->addWidget(lblMid);
    sliderLabelsHLayout->addStretch(5);
    sliderLabelsHLayout->addWidget(lblMax);
    sliderLabelsHLayout->addStretch(1);
    sliderLabelsHLayout->addWidget(lblRT);

    sliderVLayout->addWidget(m_delaySlider);
    sliderVLayout->addLayout(sliderLabelsHLayout);

    m_soundBtn = new QPushButton("Sound: ON", this);
    connect(m_soundBtn, &QPushButton::clicked, this, &SortingWindow::toggleSound);

    m_synthesizer = new AudioSynthesizer(this);
    m_synthesizer->startSynth();
    m_soundEnabled = true;

    topControlsLayout->addWidget(m_algoCombo);
    topControlsLayout->addWidget(m_sizeCombo);
    topControlsLayout->addWidget(m_startBtn);
    topControlsLayout->addWidget(sliderLayoutContainer);
    topControlsLayout->addWidget(m_timeLabel);
    topControlsLayout->addWidget(m_soundBtn);
    topControlsLayout->addStretch();
    
    bottomControlsLayout->addStretch();
    bottomControlsLayout->addWidget(m_stepBackBtn);
    bottomControlsLayout->addWidget(m_playBtn);
    bottomControlsLayout->addWidget(m_stepFwdBtn);
    bottomControlsLayout->addStretch();

    m_visualizer = new VisualizationWidget(this);

    mainLayout->addLayout(topControlsLayout);
    mainLayout->addWidget(m_visualizer, 1);
    mainLayout->addLayout(bottomControlsLayout);
}

void SortingWindow::generateData() {
    m_data.clear();
    m_commands.clear();
    m_commandIndex = -1;
    m_data.resize(m_sizeCombo->currentText().toInt());
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10, 100);

    for (int &val : m_data) {
        val = dis(gen);
    }
    m_lastState = m_data;
    setUIState(m_data);
}

void SortingWindow::setUIState(const std::vector<int>& data) {
    m_visualizer->setData(data);
}


void SortingWindow::setState(std::unique_ptr<IWindowActivityState> state) {
    m_currentState = std::move(state);
    if (m_currentState) {
        m_currentState->updateUI(this);
    }
}

void SortingWindow::playAnimation() {
    if (m_commandIndex + 1 < (int)m_commands.size()) {
        if (m_delaySlider->value() == 11) {
            m_timer->start(0);
        } else {
            float speed = m_delaySlider->value() / 10.0f;
            m_timer->start(static_cast<int>(30 / speed));
        }
        m_stopwatch.start();
        m_uiTimer->start(50);
    }
}

void SortingWindow::pauseAnimation() {
    m_timer->stop();
    m_uiTimer->stop();
    m_accumulatedTime += m_stopwatch.isValid() ? m_stopwatch.elapsed() : 0;
    updateTimeLabel();
}


void SortingWindow::onUpdate(const std::vector<int>& data) {
    if (m_lastState != data) {
        int activeValue = -1;
        for (size_t i = 0; i < data.size(); ++i) {
            if (i < m_lastState.size() && m_lastState[i] != data[i]) {
                activeValue = data[i];
                break;
            }
        }
        auto cmd = std::make_unique<core::sorting::StepCommand<int>>(
            m_lastState, data, [this, activeValue](const std::vector<int>& state){
                setUIState(state);
                if (m_soundEnabled && activeValue >= 0 && activeValue <= 100) {
                    double freq = 200.0 + (800.0 - 200.0) * (activeValue / 100.0);
                    m_synthesizer->playTone(freq);
                }
            });
        m_commands.push_back(std::move(cmd));
        m_lastState = data;
    }
}

void SortingWindow::startSorting() {
    if (m_currentState) m_currentState->handleSortStart(this);
}

void SortingWindow::stepForward() {
    if (m_currentState) m_currentState->handleStepForward(this);
}

void SortingWindow::stepBackward() {
    if (m_currentState) m_currentState->handleStepBackward(this);
}

void SortingWindow::onTimerTick() {
    if (m_commandIndex + 1 < (int)m_commands.size()) {
        m_commandIndex++;
        m_commands[m_commandIndex]->execute();

        if (m_commandIndex + 1 >= (int)m_commands.size()) {
            if (m_currentState) m_currentState->handleSortEnd(this);
        }
    } else {
        if (m_currentState) m_currentState->handleSortEnd(this);
    }
}

void SortingWindow::updateVisualization() {
    // Deprecated for stepForward
}

void SortingWindow::changeDelay(int value) {
    if (value == 11) {
        m_delaySlider->setToolTip("Animation Speed (RT)");
        if (m_timer->isActive()) {
            m_timer->setInterval(0);
        }
    } else {
        float speed = value / 10.0f;
        m_delaySlider->setToolTip(QString("Animation Speed (%1x)").arg(speed, 0, 'f', 1));
        if (m_timer->isActive()) {
            m_timer->setInterval(static_cast<int>(30 / speed));
        }
    }
}

void SortingWindow::updateTimeLabel() {
    qint64 currentElapsed = m_accumulatedTime;
    if (m_timer->isActive() && m_stopwatch.isValid()) {
        currentElapsed += m_stopwatch.elapsed();
    }
    m_timeLabel->setText(QString("Time: %1 ms").arg(currentElapsed));
}

void SortingWindow::toggleSound() {
    m_soundEnabled = !m_soundEnabled;
    m_soundBtn->setText(m_soundEnabled ? "Sound: ON" : "Sound: OFF");
}

// --- State Pattern Implementations ---

void IdleState::handleSortStart(SortingWindow* window) {
    window->generateData();
    window->m_commands.clear();
    window->m_commandIndex = -1;

    QString algo = window->m_algoCombo->currentText();
    auto strategy = core::sorting::SortFactory::create<int>(algo.toStdString());
    if (!strategy) return;
    
    strategy->addObserver(window);
    std::vector<int> dataCopy = window->m_data;
    strategy->sort(dataCopy);
    
    window->m_accumulatedTime = 0;
    window->m_timeLabel->setText("Time: 0 ms");
    
    if (!window->m_commands.empty()) {
        window->setState(std::make_unique<RunningState>());
        window->playAnimation();
    }
}

void IdleState::updateUI(SortingWindow* window) {
    window->m_startBtn->setEnabled(true);
    window->m_stepBackBtn->setEnabled(false);
    window->m_stepFwdBtn->setEnabled(false);
    window->m_playBtn->setEnabled(false);
    window->m_algoCombo->setEnabled(true);
    window->m_sizeCombo->setEnabled(true);
}

void RunningState::handlePlayPause(SortingWindow* window) {
    window->pauseAnimation();
    window->setState(std::make_unique<PausedState>());
}

void RunningState::handleSortEnd(SortingWindow* window) {
    window->pauseAnimation();
    
    std::string algo = window->m_algoCombo->currentText().toStdString();
    std::string contextStr = "Array Size: " + std::to_string(window->m_data.size()) + " (Animated)";
    core::benchmarks::BenchmarkHistoryManager::getInstance().addRecord(
        {algo, contextStr, static_cast<double>(window->m_accumulatedTime)}
    );
    
    window->setState(std::make_unique<IdleState>());
}

void RunningState::updateUI(SortingWindow* window) {
    window->m_startBtn->setEnabled(false);
    window->m_stepBackBtn->setEnabled(false);
    window->m_stepFwdBtn->setEnabled(false);
    window->m_playBtn->setEnabled(true);
    window->m_algoCombo->setEnabled(false);
    window->m_sizeCombo->setEnabled(false);
}

void PausedState::handlePlayPause(SortingWindow* window) {
    window->playAnimation();
    window->setState(std::make_unique<RunningState>());
}

void PausedState::handleStepForward(SortingWindow* window) {
    if (window->m_commandIndex + 1 < (int)window->m_commands.size()) {
        window->m_commandIndex++;
        window->m_commands[window->m_commandIndex]->execute();

        if (window->m_commandIndex + 1 >= (int)window->m_commands.size()) {
            std::string algo = window->m_algoCombo->currentText().toStdString();
            std::string contextStr = "Array Size: " + std::to_string(window->m_data.size()) + " (Animated)";
            core::benchmarks::BenchmarkHistoryManager::getInstance().addRecord(
                {algo, contextStr, static_cast<double>(window->m_accumulatedTime)}
            );
            window->setState(std::make_unique<IdleState>());
        } else {
            updateUI(window);
        }
    }
}

void PausedState::handleStepBackward(SortingWindow* window) {
    if (window->m_commandIndex >= 0 && window->m_commandIndex < (int)window->m_commands.size()) {
        window->m_commands[window->m_commandIndex]->undo();
        window->m_commandIndex--;
        updateUI(window);
    }
}

void PausedState::handleSortStart(SortingWindow* window) {
    window->setState(std::make_unique<IdleState>());
    window->m_currentState->handleSortStart(window);
}

void PausedState::handleSortEnd(SortingWindow* window) {
    window->setState(std::make_unique<IdleState>());
}

void PausedState::updateUI(SortingWindow* window) {
    window->m_startBtn->setEnabled(true);
    window->m_stepBackBtn->setEnabled(window->m_commandIndex >= 0);
    window->m_stepFwdBtn->setEnabled(window->m_commandIndex + 1 < (int)window->m_commands.size());
    window->m_playBtn->setEnabled(true);
    window->m_algoCombo->setEnabled(true);
    window->m_sizeCombo->setEnabled(true);
}
