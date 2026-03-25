/**
 * @file Graph.h
 * @brief Core graph data structures.
 */

#pragma once

#include <vector>
#include <list>

namespace core {
namespace graphs {

/**
 * @struct Edge
 * @brief Represents a directed, weighted edge in a graph.
 */
struct Edge {
    int destination;  ///< The index of the target vertex.
    double weight;    ///< The numerical weight/cost of the edge.
};

/**
 * @class Graph
 * @brief Represents a directed graph using an adjacency list.
 */
class Graph {
private:
    int numVertices;                           ///< Total number of vertices in the graph.
    std::vector<std::list<Edge>> adjList;      ///< Adjacency list storing outgoing edges for each vertex.

public:
    /**
     * @brief Constructs a new Graph with the specified number of vertices.
     * @param vertices The number of vertices to allocate space for.
     */
    explicit Graph(int vertices) : numVertices(vertices), adjList(vertices) {}

    /**
     * @brief Adds a directed edge from a source vertex to a destination vertex.
     * @param source The starting vertex index.
     * @param destination The target vertex index.
     * @param weight The weight of the edge (default: 1.0).
     */
    void addEdge(int source, int destination, double weight = 1.0) {
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            adjList[source].push_back({destination, weight});
        }
    }

    /**
     * @brief Retrieves the total number of vertices in the graph.
     * @return The number of vertices.
     */
    int getNumVertices() const { return numVertices; }

    /**
     * @brief Retrieves the outgoing edges for a given vertex.
     * @param vertex The index of the vertex.
     * @return A constant reference to a list of edges originating from the given vertex.
     */
    const std::list<Edge>& getNeighbors(int vertex) const {
        return adjList[vertex];
    }
};

} // namespace graphs
} // namespace core
