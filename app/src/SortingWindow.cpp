#include "SortingWindow.h"
#include "sorting/SortFactory.h"
#include "sorting/StepCommand.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <random>

SortingWindow::SortingWindow(QWidget *parent) : QWidget(parent) {
    setupUi();
    generateData();
    
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SortingWindow::stepForward);
}

SortingWindow::~SortingWindow() = default;

void SortingWindow::setupUi() {
    setWindowTitle("Sorting Algorithm Visualization");
    resize(700, 500);

    auto *mainLayout = new QVBoxLayout(this);
    auto *controlsLayout = new QHBoxLayout();
    
    auto *algoCombo = new QComboBox(this);
    algoCombo->addItem("QuickSort");
    algoCombo->addItem("MergeSort");
    algoCombo->addItem("BubbleSort");
    algoCombo->addItem("SelectionSort");
    algoCombo->addItem("InsertionSort");
    algoCombo->setObjectName("algoCombo");
    
    auto *startBtn = new QPushButton("Generate & Sort", this);
    connect(startBtn, &QPushButton::clicked, this, &SortingWindow::startSorting);
    
    auto *stepBackBtn = new QPushButton("<< Undo", this);
    connect(stepBackBtn, &QPushButton::clicked, this, &SortingWindow::stepBackward);

    auto *stepFwdBtn = new QPushButton("Step >>", this);
    connect(stepFwdBtn, &QPushButton::clicked, this, &SortingWindow::stepForward);

    auto *playBtn = new QPushButton("Play/Pause", this);
    connect(playBtn, &QPushButton::clicked, this, [this](){
        if (m_timer->isActive()) m_timer->stop();
        else m_timer->start(30); // 30ms per frame
    });

    m_timeLabel = new QLabel("Time: 0 ms");

    controlsLayout->addWidget(algoCombo);
    controlsLayout->addWidget(startBtn);
    controlsLayout->addWidget(stepBackBtn);
    controlsLayout->addWidget(playBtn);
    controlsLayout->addWidget(stepFwdBtn);
    controlsLayout->addWidget(m_timeLabel);
    controlsLayout->addStretch();

    m_visualizer = new VisualizationWidget(this);

    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(m_visualizer, 1);
}

void SortingWindow::generateData() {
    m_data.clear();
    m_commands.clear();
    m_commandIndex = -1;
    m_data.resize(60);
    
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

void SortingWindow::onUpdate(const std::vector<int>& data) {
    if (m_lastState != data) {
        auto cmd = std::make_unique<core::sorting::StepCommand<int>>(
            m_lastState, data, [this](const std::vector<int>& state){
                setUIState(state);
            });
        m_commands.push_back(std::move(cmd));
        m_lastState = data;
    }
}

void SortingWindow::startSorting() {
    generateData();
    m_commands.clear();
    m_commandIndex = -1;

    auto *combo = findChild<QComboBox*>("algoCombo");
    if (!combo) return;
    
    QString algo = combo->currentText();
    auto strategy = core::sorting::SortFactory::create<int>(algo.toStdString());
    
    if (!strategy) return;
    
    strategy->addObserver(this);
    
    // Sort a copy
    std::vector<int> dataCopy = m_data;
    strategy->sort(dataCopy);
    m_timeLabel->setText(QString("Time: %1 ms").arg(strategy->getLastDurationMs()));
    
    // Auto-start playback
    if (!m_commands.empty()) {
        m_timer->start(30);
    }
}

void SortingWindow::stepForward() {
    if (m_commandIndex + 1 < (int)m_commands.size()) {
        m_commandIndex++;
        m_commands[m_commandIndex]->execute();
    } else {
        m_timer->stop();
    }
}

void SortingWindow::stepBackward() {
    if (m_commandIndex >= 0 && m_commandIndex < (int)m_commands.size()) {
        m_timer->stop();
        m_commands[m_commandIndex]->undo();
        m_commandIndex--;
    }
}

void SortingWindow::updateVisualization() {
    // Deprecated for stepForward
}
