// yocheved@davidowitz.net | 324460682

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

#include <vector>
#include <iostream>

using namespace std;


TEST_CASE("Test for first graph in demo")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "-1");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,2}, b={1}");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0 -> 1 -> 2");

}

TEST_CASE("Test for second graph in demo")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "No path found");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0 -> 1 -> 2 -> 0");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite");
}

TEST_CASE("Test weighted graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0 -> 2 -> 3 -> 4");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0 -> 1 -> 2 -> 0");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite");
}


TEST_CASE("Test graph with negative weights")
{
    ariel::Graph g;

        vector<vector<int>> graph = {
        {0, -1, 2},
        {0, 0, -3},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0 -> 1 -> 2");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "-1");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");

    vector<vector<int>> graph2 = {
        {0, -1, 0},
        {1, 0, -5},
        {0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0 -> 1 -> 2");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0 -> 1 -> 0");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,2}, b={1}");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");

}



TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph4 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph5 = {
        {0, 1, 1},
        {1, 0, 1}};
    CHECK_THROWS(g.loadGraph(graph));
}


TEST_CASE("Test small graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1},
        {1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0 -> 1");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "-1");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, b={1}");

    vector<vector<int>> graph2 = {
        {0, 5},
        {0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 1, 0) == "No path found");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "-1");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, b={1}");

}
TEST_CASE("Test empty graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "Invalid vertex input");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "-1");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={}, b={}");
}

TEST_CASE("Test if a directed graph is connected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph3 = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 3, 0, 0, 2},
        {0, 0, 4, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == false);

}

TEST_CASE("Test if an undirected graph is connected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 1},
        {0, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 0, -1},
        {0, 0, 0},
        {-1, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph3 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == false);
        
}

TEST_CASE("Test shortest path error")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1},
        {1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "Invalid vertex input");

    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 1, 3) == "Invalid vertex input");
    CHECK(ariel::Algorithms::shortestPath(g, 5, 2) == "Invalid vertex input");

}

TEST_CASE("Test shortest path in undirected unweighted graph")
{
    ariel::Graph g;

    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0 -> 2");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0 -> 1");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0 -> 2 -> 3 -> 4");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 4) == "1 -> 2 -> 3 -> 4");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {0, 0, 0, 1, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0 -> 2");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 4) == "1 -> 3 -> 4");
    string path = ariel::Algorithms::shortestPath(g, 0, 4);
    CHECK((path == "0 -> 1 -> 3 -> 4" || path == "0 -> 2 -> 3 -> 4"));


    vector<vector<int>> graph3 = {
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0 -> 2");
    CHECK(ariel::Algorithms::shortestPath(g, 2, 1) == "2 -> 0 -> 1");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 2) == "1 -> 0 -> 2");

    vector<vector<int>> graph4 = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "No path found");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0 -> 1");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 0) == "1 -> 0");

}

TEST_CASE("Test shortest path in undirected graph with non negative weights")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 3, 0},
        {3, 0, 2},
        {0, 2, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0 -> 1 -> 2");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0 -> 1");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 2) == "1 -> 2");

    vector<vector<int>> graph2 = {
        {0, 10, 3, 0, 0},
        {10, 0, 17, 1, 0},
        {3, 17, 0, 100, 0},
        {0, 1, 100, 0, 40},
        {0, 0, 0, 40, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0 -> 1 -> 3 -> 4");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 3) == "1 -> 3");
    CHECK(ariel::Algorithms::shortestPath(g, 2, 4) == "2 -> 0 -> 1 -> 3 -> 4");
    CHECK(ariel::Algorithms::shortestPath(g, 2, 1) == "2 -> 0 -> 1");

}

TEST_CASE("Test shortest path in undirected graph with negative weights")
{
    // all undirected graphs with negative weights will contain negative cycle

    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, -3},
        {-3, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "Graph contains negative cycle");


    vector<vector<int>> graph4 = {
        {0, -1, 1},
        {-1, 0, -1},
        {1, -1, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "Graph contains negative cycle");
}

TEST_CASE("Test shortest path in directed unweighted graph ")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0 -> 1 -> 2");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0 -> 1");
    CHECK(ariel::Algorithms::shortestPath(g, 2, 0) == "No path found");

    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}}; 
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0 -> 1 -> 2");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0 -> 1");
    CHECK(ariel::Algorithms::shortestPath(g, 2, 1) == "2 -> 0 -> 1");

    vector<vector<int>> graph3 = {
        {0, 1, 1, 0, 1},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0 -> 4");
    CHECK(ariel::Algorithms::shortestPath(g, 4, 0) == "4 -> 3 -> 2 -> 0");

}

TEST_CASE("Test shortest path in directed graph with non negative weights")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 5, 0},
        {3, 0, 2},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0 -> 1 -> 2");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0 -> 1");
    CHECK(ariel::Algorithms::shortestPath(g, 2, 1) == "No path found");

    vector<vector<int>> graph2 = {
        {0, 10, 3, 0, 0},
        {10, 0, 17, 1, 0},
        {3, 0, 0, 100, 0},
        {0, 1, 0, 0, 40},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0 -> 1 -> 3 -> 4");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 3) == "1 -> 3");
    CHECK(ariel::Algorithms::shortestPath(g, 2, 4) == "2 -> 0 -> 1 -> 3 -> 4");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 2) == "1 -> 0 -> 2");

}

TEST_CASE("Test shortest path in directed graph with negative weights")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, -5, 0},
        {1, 0, -2},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "Graph contains negative cycle");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 0) == "0");

    vector<vector<int>> graph2 = {
        {0, 0, 0, 2, -2},
        {0, 0, -1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, -8},
        {0, 0, 2, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0 -> 3 -> 4");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0 -> 3 -> 4 -> 2");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 3) == "No path found");
}

TEST_CASE("Test if directed graph contains a cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "-1");

    vector<vector<int>> graph2 = {
        {0, 0, 7, 0, 0},
        {6, 0, 0, 0, 0},
        {0, 8, 0, 0, 5},
        {0, 0, 0, 0, 7},
        {0, 0, 5, 7, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0 -> 2 -> 1 -> 0");

    vector<vector<int>> graph3 = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0 -> 1 -> 2 -> 0");

    vector<vector<int>> graph4 = {
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {1, 0, 0, 0},
        {0, 1, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0 -> 3 -> 1 -> 2 -> 0");

}

TEST_CASE("Test if undirected graph contains a cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "-1");

    vector<vector<int>> graph2 = {
        {0, 6, 7, 0, 0},
        {6, 0, 8, 0, 0},
        {7, 8, 0, 0, 5},
        {0, 0, 0, 0, 7},
        {0, 0, 5, 7, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0 -> 1 -> 2 -> 0");

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0},
        {1, 0, 1, 1},
        {0, 1, 0, 1},
        {0, 1, 1, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "1 -> 2 -> 3 -> 1");

}

TEST_CASE("Test if undirected graph is bipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite");

    vector<vector<int>> graph2 = {
        {0, 1, 0, 0},
        {1, 0, 0, 1},
        {0, 0, 0, 1},
        {0, 1, 1, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,3}, b={1,2}");
}

TEST_CASE("Test if a directed graph is bipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1},
        {0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, b={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,2}, b={1,3}");

    vector<vector<int>> graph3 = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite");
}


TEST_CASE("Test negative cycles in a directed graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, -1, 0},
        {0, 0, -1},
        {1, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle: 0 -> 1 -> 2 -> 0");

    vector<vector<int>> graph2 = {
        {0, 3, 2},
        {0, 0, -2},
        {0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");

}

TEST_CASE("Test negative cycles in an undirected graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 6, 7, 0, 0},
        {6, 0, 8, -4, 0},
        {7, 8, 0, 0, 5},
        {0, -4, 0, 0, 7},
        {0, 0, 5, 7, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle: 3 -> 1 -> 3");


}


