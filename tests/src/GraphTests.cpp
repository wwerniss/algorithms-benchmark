#include <gtest/gtest.h>
#include "graphs/Graph.h"
#include "graphs/BFS.h"
#include "graphs/DFS.h"
#include "graphs/Dijkstra.h"

using namespace core::graphs;

TEST(GraphTests, BFSPath) {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    BFS bfs;
    auto path = bfs.findPath(g, 0, 4);
    
    // Shortest path is 0 -> 2 -> 4
    std::vector<int> expected = {0, 2, 4};
    EXPECT_EQ(path, expected);
}

TEST(GraphTests, DFSPath) {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    DFS dfs;
    auto path = dfs.findPath(g, 0, 4);
    
    // Path depends on order of edges, but usually 0 -> 1 -> 3 -> 4
    // We just check if it's a valid path
    ASSERT_TRUE(path.front() == 0);
    ASSERT_TRUE(path.back() == 4);
}

TEST(GraphTests, DijkstraPath) {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 1, 1);
    
    // Shortest path to 4 is 0 -> 2 -> 3 -> 1 -> 4 (weight: 1+1+1+1 = 4)
    Dijkstra dijkstra;
    auto path = dijkstra.findPath(g, 0, 4);
    
    std::vector<int> expected = {0, 2, 3, 1, 4};
    EXPECT_EQ(path, expected);
}

TEST(GraphTests, NoPath) {
    Graph g(3);
    g.addEdge(0, 1);
    
    BFS bfs;
    auto path = bfs.findPath(g, 0, 2);
    EXPECT_TRUE(path.empty());
}
