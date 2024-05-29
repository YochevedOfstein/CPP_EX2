// yocheved@davidowitz.net | 324460682

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>

#define INF numeric_limits<int>::max()

using namespace std;

namespace ariel{
    class Graph{
        
        private:

        vector<vector<int>> adjMatrix;

        size_t numOfVertices;

        bool isDirected;
        bool isWeighted;
        bool hasNegativeWeights;

        public:

        /**
         * @brief Construct a new Graph object
        */
        Graph();

        /**
         * @brief Initialize graph from givan adjacency matrix.
         * @param matrix The graph to be loaded.
        */
        void loadGraph(vector<vector<int>> &matrix);

        /**
         * @brief Print the graph.
        */
        void printGraph()const;

        /**
         * @brief Check if the graph has negative weighted edges.
         * @return true if the graph has negative weighted edges, false otherwise.
        */
        bool hasNegativeWeightedEdges()const;

        /**
         * @brief Check if the graph is weighted.
         * @return true if the graph is weighted, false otherwise.
        */
        bool isWeightedGraph()const;

        /**
         * @brief Check if the graph is directed.
         * @return true if the graph is directed, false otherwise.
        */
        bool isDirectedGraph()const;

        /**
         * @brief Getter function for number of vertices.
         * @return Number of vertices.
        */
        size_t getNumOfVertices()const;

        /**
         * @brief Getter function for neighbors of a given vertex.
         * @param v The vertex to get its neighbors.
         * @return A vector of neighbors of the given vertex.
        */
        vector<size_t> getNeighbors(size_t v)const;

        /**
         * @brief Getter function for the graph itself.
         * @return The graph.
        */
        vector<vector<int>> getGraph()const;

        /**
         * @brief Getter function for the weight of an edge.
         * @param start The start vertex of the edge.
         * @param end The end vertex of the edge.
         * @return The weight of the edge.
        */
        int getWeight(size_t start, size_t end)const;


        Graph operator+(const Graph& graph);
        Graph operator-(const Graph& graph);
        Graph operator*(const Graph& graph);
        Graph operator*(int scalar);

        Graph& operator+=(const Graph& graph);
        Graph& operator-=(const Graph& graph);
        Graph& operator*=(const Graph& graph);
        Graph& operator*=(int scalar);
        Graph& operator/=(int scalar);

        bool operator==(const Graph& graph);
        bool operator!=(const Graph& graph);
        bool operator>(const Graph& graph);
        bool operator<(const Graph& graph);
        bool operator>=(const Graph& graph);
        bool operator<=(const Graph& graph);

        Graph& operator++();  
        Graph operator++(int); 
        Graph& operator--();    
        Graph operator--(int);  
        Graph operator+() const;
        Graph operator-() const;

        friend ostream& operator<<(ostream& os, const Graph& graph);


    };
}

#endif 