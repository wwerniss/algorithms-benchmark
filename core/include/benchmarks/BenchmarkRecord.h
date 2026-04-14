#pragma once

#include <string>

namespace core {
namespace benchmarks {

/**
 * @struct BenchmarkRecord
 * @brief Represents a single benchmark test result.
 */
struct BenchmarkRecord {
    std::string algorithmName; ///< Name of the executed algorithm.
    std::string context;       ///< Context of the test (e.g., array size, graph complexity).
    double durationMs;         ///< Execution time in milliseconds.
};

} // namespace benchmarks
} // namespace core
