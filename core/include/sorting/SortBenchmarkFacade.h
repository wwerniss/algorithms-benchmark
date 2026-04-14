#pragma once

#include "sorting/SortFactory.h"
#include "benchmarks/BenchmarkHistoryManager.h"
#include <vector>
#include <string>
#include <utility>

namespace core {
namespace sorting {

/**
 * @class SortBenchmarkFacade
 * @brief Implements the Facade design pattern to manage sorting benchmarks.
 * 
 * Provides a unified, simplified interface for the GUI to test the performance
 * of multiple sorting algorithms simultaneously without knowing system internals.
 */
class SortBenchmarkFacade {
private:
    std::vector<std::string> algorithms; ///< List of registered algorithms.
    std::vector<int> dataSet;            ///< The array to be sorted by algorithms.

public:
    /**
     * @brief Default constructor. Registers standard algorithms by default.
     */
    SortBenchmarkFacade() : algorithms({"QuickSort", "MergeSort", "BubbleSort", "SelectionSort", "InsertionSort"}) {}

    /**
     * @brief Configures the dataset to run benchmarks against.
     * @param data The collection of integers.
     */
    void setDataSet(const std::vector<int>& data) {
        dataSet = data;
    }

    /**
     * @brief Registers an additional algorithm for the benchmark suite.
     * @param algo The string ID/name of the algorithm to benchmark.
     */
    void addAlgorithm(const std::string& algo) {
        algorithms.push_back(algo);
    }
    
    /**
     * @brief Clears the list of registered algorithms.
     */
    void clearAlgorithms() {
        algorithms.clear();
    }

    /**
     * @brief Executes the benchmark suite.
     * @return A list of (algorithm_name, processing_time_in_ms) pairs.
     */
    std::vector<std::pair<std::string, double>> runBenchmarks() const {
        std::vector<std::pair<std::string, double>> results;
        if (dataSet.empty()) return results;
        
        std::string contextStr = "Array Size: " + std::to_string(dataSet.size());
        
        for (const auto& algo : algorithms) {
            auto strategy = SortFactory::create<int>(algo);
            if (strategy) {
                std::vector<int> dataCopy = dataSet;
                strategy->sort(dataCopy);
                double duration = strategy->getLastDurationMs();
                results.push_back({algo, duration});
                
                // Add to global benchmark history
                benchmarks::BenchmarkHistoryManager::getInstance().addRecord(
                    {algo, contextStr, duration}
                );
            }
        }
        
        return results;
    }
};

} // namespace sorting
} // namespace core
