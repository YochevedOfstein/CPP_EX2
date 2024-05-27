// yocheved@davidowitz.net | 324460682

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>
#include <iostream>

enum Color{
    White,
    Grey,
    Black,
    Red,
    Blue
};

using namespace std;

namespace ariel {
    
    class Algorithms{

        private:

        /**
        * @brief This function is the main function for the DFS algorithm, it will call the dfsVisit function for each vertex in the graph.
        * @param g The graph to be checked.
        * @return A vector of vectors of integers, each vector represents a connected component in the graph.
        **/
        static vector<vector<int>> dfsMain(const Graph& g);

        /**
         * @brief This function performs a DFS traversal starting from a given vertex.
         * @param g The graph to be checked.
         * @param vertex The vertex to start the traversal from.
         * @param colors A vector of colors to keep track of the visited vertices.
         * @return A vector of integers representing the vertices in the connected component.
         **/
        static vector<int> dfsVisit(const Graph& g, size_t vertex, vector<Color>& colors);

        /**
         * @brief This function performs a DFS traversal starting from a given vertex to find a cycle.
         * @param g The graph to be checked.
         * @param vertex The vertex to start the traversal from.
         * @param colors A vector of colors to keep track of the visited vertices.
         * @param parents A vector of integers to keep track of the parent of each vertex.
         * @param path A vector of integers to keep track of the path.
         * @return A vector of integers representing the vertices in a cycle.
         **/
        static string dfsFindCycle(const Graph& g, size_t v, vector<Color>& colors, vector<int>& parents, vector<int>& path);

        /**
         * @brief This function creates a cycle from a given path.
         * @param path A vector of integers representing the vertices in the cycle.
         * @param src The source vertex of the cycle.
         * @return A string representing the cycle.
         **/
        static string createCycle(vector<int>& path, size_t src);

        /**
         * @brief This function performs a BFS traversal starting from a given vertex.
         * @param g The graph to be checked.
         * @param start The vertex to start the traversal from.
         * @param end The vertex to end the traversal.
         * @return A string representing the path from the start vertex to the end vertex.
         **/
        static string bfs(const Graph& g, size_t start, size_t end);

        /**
         * @brief This function performs a Dijkstra's algorithm starting from a given vertex.
         * @param g The graph to be checked.
         * @param start The vertex to start the traversal from.
         * @param end The vertex to end the traversal.
         * @return A string representing the path from the start vertex to the end vertex.
         **/
        static string dijkstra(const Graph& g, size_t start, size_t end);

        /**
         * @brief This function performs a Bellman-Ford algorithm starting from a given vertex.
         * @param g The graph to be checked.
         * @param start The vertex to start the traversal from.
         * @param end The vertex to end the traversal.
         * @return A string representing the path from the start vertex to the end vertex.
         **/
        static string bellmanFord(const Graph& g, size_t start, size_t end);
        
        
        public:

        /**
         * @brief This function checks if a graph is connected.
         * @param graph The graph to be checked.
         * @return true if the graph is connected, false otherwise.
         **/
        static bool isConnected(const Graph& graph);

        /**
         * @brief This function finds the shortest path between two vertices in a graph.
         * @param graph The graph to be checked.
         * @param start The start vertex.
         * @param end The end vertex.
         * @return A string representing the shortest path between the two vertices.
         **/
        static string shortestPath(const Graph& graph, size_t start, size_t end);

        /**
         * @brief This function checks if a graph contains a cycle.
         * @param graph The graph to be checked.
         * @return A string representing the cycle if it exists, "-1" otherwise.
         **/
        static string isContainsCycle(const Graph& graph);

        /**
         * @brief This function checks if a graph is bipartite.
         * @param graph The graph to be checked.
         * @return A string representing the bipartite sets if the graph is bipartite, "The graph is not bipartite" otherwise.
         **/
        static string isBipartite(const Graph& graph);

        /**
         * @brief This function finds a negative cycle in the graph.
         * @param graph The graph to be checked.
         * @param start The start vertex.
         * @param end The end vertex.
         * @return A string representing the negative cycle, "No negative cycle found" otherwise.
         **/    
        static string negativeCycle(const Graph& graph);

    };
}

#endif 