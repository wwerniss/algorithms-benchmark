#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "patterns/Observer.h"
#include "benchmarks/BenchmarkRecord.h"

/**
 * @class HistoryWindow
 * @brief GUI tab widget that observes and displays the global benchmark history.
 * 
 * Implements the Observer pattern to automatically receive notifications
 * whenever a new algorithmic test finishes. It asynchronously updates its
 * internal QTableWidget with the latest algorithm name, test context, and duration.
 */
class HistoryWindow : public QWidget, public core::patterns::IObserver<core::benchmarks::BenchmarkRecord> {
    Q_OBJECT

public:
    /**
     * @brief Constructs the HistoryWindow and binds it as an observer to the global history manager.
     * @param parent The parent QWidget, typically the main tab widget.
     */
    explicit HistoryWindow(QWidget *parent = nullptr);
    
    /**
     * @brief Destroys the window and unregisters it from the history manager's observer list.
     */
    ~HistoryWindow() override;

    /**
     * @brief Callback invoked by the Observable when new records are added to the general history.
     * @param history The fully updated list of benchmark records.
     */
    void onUpdate(const std::vector<core::benchmarks::BenchmarkRecord>& history) override;

private:
    /** @brief Initializes layout, UI components, and table formatting. */
    void setupUi();
    
    /** 
     * @brief Formats and pushes raw history data into the visual QTableWidget. 
     * @param history The data source vector containing past benchmark sessions.
     */
    void populateTable(const std::vector<core::benchmarks::BenchmarkRecord>& history);

    QTableWidget *m_table;   ///< View widget displaying the historical benchmarks.
    QPushButton *m_clearBtn; ///< Button used strictly to clear the visual representation (does not clear singleton data).
};
