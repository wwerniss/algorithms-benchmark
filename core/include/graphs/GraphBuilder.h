#pragma once

#include "graphs/Graph.h"
#include <memory>
#include <random>

namespace core {
namespace graphs {

/**
 * @class GraphBuilder
 * @brief Implements the Builder design pattern to construct complex Graph instances.
 * 
 * Provides a fluent interface to build graphs step-by-step,
 * encapsulating random connection and distribution logic.
 */
class GraphBuilder {
private:
    std::unique_ptr<Graph> graph; ///< Internal pointer to the graph being built.

public:
    /**
     * @brief Default constructor.
     */
    GraphBuilder() : graph(nullptr) {}

    /**
     * @brief Initializes the graph with a specific number of vertices.
     * @param count Number of vertices to allocate.
     * @return Reference to the builder instance.
     */
    GraphBuilder& addNodes(int count) {
        graph = std::make_unique<Graph>(count);
        return *this;
    }

    /**
     * @brief Connects all nodes sequentially (0 -> 1 -> 2 -> ... -> n-1) to guarantee a single path.
     * @param weight The weight assigned to each edge (default: 1.0).
     * @return Reference to the builder instance.
     */
    GraphBuilder& connectLinear(double weight = 1.0) {
        if (!graph) return *this;
        for (int i = 0; i < graph->getNumVertices() - 1; ++i) {
            graph->addEdge(i, i + 1, weight);
        }
        return *this;
    }

    /**
     * @brief Randomly connects nodes based on a specified probability.
     * @param probability Chance to connect any two distinct nodes (0.0 to 1.0).
     * @param minWeight Minimum weight for the generated edges.
     * @param maxWeight Maximum weight for the generated edges.
     * @return Reference to the builder instance.
     */
    GraphBuilder& connectRandomly(double probability, double minWeight = 1.0, double maxWeight = 10.0) {
        if (!graph || probability <= 0.0) return *this;
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> probDist(0.0, 1.0);
        std::uniform_real_distribution<> weightDist(minWeight, maxWeight);

        int n = graph->getNumVertices();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && probDist(gen) < probability) {
                    graph->addEdge(i, j, weightDist(gen));
                }
            }
        }
        return *this;
    }

    /**
     * @brief Fully connects the graph (every node connects to every other node).
     * @param weight The weight assigned to all edges.
     * @return Reference to the builder instance.
     */
    GraphBuilder& connectFully(double weight = 1.0) {
        if (!graph) return *this;
        int n = graph->getNumVertices();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    graph->addEdge(i, j, weight);
                }
            }
        }
        return *this;
    }

    /**
     * @brief Finalizes construction and returns ownership of the built graph.
     * @return Unique pointer to the constructed Graph object.
     */
    std::unique_ptr<Graph> build() {
        return std::move(graph);
    }
};

} // namespace graphs
} // namespace core
