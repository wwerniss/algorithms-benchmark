#pragma once

#include "BenchmarkRecord.h"
#include "patterns/Observer.h"
#include <vector>

namespace core {
namespace benchmarks {

/**
 * @class BenchmarkHistoryManager
 * @brief Singleton manager that stores all benchmark runs and notifies UI observers.
 */
class BenchmarkHistoryManager : public patterns::IObservable<BenchmarkRecord> {
private:
    std::vector<BenchmarkRecord> history;

    // Private constructor for Meyer's Singleton
    BenchmarkHistoryManager() = default;

public:
    // Delete copy operations
    BenchmarkHistoryManager(const BenchmarkHistoryManager&) = delete;
    BenchmarkHistoryManager& operator=(const BenchmarkHistoryManager&) = delete;

    /**
     * @brief Access point for the Singleton instance.
     * @return Reference to the global history manager.
     */
    static BenchmarkHistoryManager& getInstance() {
        static BenchmarkHistoryManager instance;
        return instance;
    }

    /**
     * @brief Adds a new benchmark result to history and notifies all UI observers.
     * @param record The result containing algorithm name, context, and time.
     */
    void addRecord(const BenchmarkRecord& record) {
        history.push_back(record);
        notifyObservers(history);
    }

    /**
     * @brief Retrieves the full history of benchmarks.
     * @return Constant reference to the history vector.
     */
    const std::vector<BenchmarkRecord>& getHistory() const {
        return history;
    }
};

} // namespace benchmarks
} // namespace core
