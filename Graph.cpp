

#include "Graph.hpp"

using namespace std;
using namespace ariel;

Graph::Graph(){
    this->numOfVertices = 0;
    this->isDirected = false;
    this->isWeighted = false;
    this->hasNegativeWeights = false;
}

void Graph::loadGraph(vector<vector<int>> &matrix){

    this->numOfVertices = matrix.size();
    this->adjMatrix = matrix;

    for(size_t i = 0; i < adjMatrix.size(); i++){
        if(adjMatrix.size() != adjMatrix[i].size()){
            throw invalid_argument("Invalid graph - this graph is not a square matrix");
        }
        for(size_t j = 0; j < adjMatrix[i].size(); j++){

            if(i == j && adjMatrix[i][j] != 0){
                throw invalid_argument("Invalid graph - the diagonal must be all 0 "); 
            }
            if(adjMatrix[i][j] != adjMatrix[j][i]){
                this->isDirected = true;
            }
            if(adjMatrix[i][j] > 1){
                this->isWeighted = true; 
            }
            if(adjMatrix[i][j] < 0){
                this->isWeighted = true; 
                this->hasNegativeWeights = true;
            }
        }
    }
}

void Graph::printGraph()const{

    size_t edges = 0;
    size_t vertices = this->numOfVertices;

    for(size_t i = 0; i < vertices ; i++){
        for(size_t j = 0; j < vertices; j++){
            if(adjMatrix[i][j] != 0){
                edges++;
            }
        }
    }
    if(!(this->isDirected)){
        edges = edges/2;
    }
    cout << "Graph with " << numOfVertices << " and " << edges << " edges" << endl;

}

bool Graph::hasNegativeWeightedEdges() const{
    return this->hasNegativeWeights;
}

bool Graph::isDirectedGraph()const{
    return this->isDirected;
}

bool Graph::isWeightedGraph()const{
    return this->isWeighted;
}

size_t Graph::getNumOfVertices()const{
    return this->numOfVertices;
}

int Graph::getWeight(size_t u, size_t v)const{

    if (u >= adjMatrix.size() || v >= adjMatrix.size()) {
        throw out_of_range("Invalid vertex index");
    }
    if(!isWeightedGraph()){
        throw runtime_error("Graph has no weights");
    }

    return adjMatrix[u][v];
}

vector<size_t> Graph::getNeighbors(size_t v) const{
    vector<size_t> neighbors;

    for(size_t i = 0; i < getNumOfVertices(); i++){
        if(adjMatrix[v][i] != 0){
            neighbors.push_back(i);
        }
    }

    return neighbors;
}

vector<vector<int>> Graph::getGraph()const{
    return this->adjMatrix;
}

////////////////////////// Operators //////////////////////////

Graph Graph::operator+(const Graph& graph){
    vector<vector<int>> newMatrix;
    if(this->getNumOfVertices() != graph.getNumOfVertices()){
        throw invalid_argument("Invalid graph - the graphs must have the same number of vertices");
    }
    for(size_t i = 0; i < this->getNumOfVertices(); i++){
        vector<int> row;
        for(size_t j = 0; j < this->getNumOfVertices(); j++){
            row.push_back(this->adjMatrix[i][j] + graph.adjMatrix[i][j]);
        }
        newMatrix.push_back(row);
    }
    Graph newGraph;
    newGraph.loadGraph(newMatrix);
    return newGraph;
}

Graph Graph::operator-(const Graph& graph){
    vector<vector<int>> newMatrix;
    if(this->getNumOfVertices() != graph.getNumOfVertices()){
        throw invalid_argument("Invalid graph - the graphs must have the same number of vertices");
    }
    for(size_t i = 0; i < this->getNumOfVertices(); i++){
        vector<int> row;
        for(size_t j = 0; j < this->getNumOfVertices(); j++){
            row.push_back(this->adjMatrix[i][j] - graph.adjMatrix[i][j]);
        }
        newMatrix.push_back(row);
    }
    Graph newGraph;
    newGraph.loadGraph(newMatrix);
    return newGraph;
}

Graph Graph::operator*(const Graph& graph){

    if(this->getNumOfVertices() != graph.getNumOfVertices()){
        throw invalid_argument("Invalid graph - the number of columns of the first matrix must be equal to the number of rows of the second matrix");
    }
    size_t vertices = this->getNumOfVertices();

    vector<vector<int>> newMatrix(vertices, vector<int>(vertices, 0));

    for(size_t i = 0; i < this->getNumOfVertices(); i++){
        for(size_t j = 0; j < this->getNumOfVertices(); j++){
            if(i == j){
                newMatrix[i][j] = 0;
                continue;
            }
            for(size_t k = 0; k < this->getNumOfVertices(); k++){
                newMatrix[i][j] += this->adjMatrix[i][k] * graph.adjMatrix[k][j];
            }
        }
    }
    Graph newGraph;
    newGraph.loadGraph(newMatrix);
    return newGraph;
}

Graph Graph::operator*(int scalar){
    vector<vector<int>> newMatrix;
    for(size_t i = 0; i < this->getNumOfVertices(); i++){
        vector<int> row;
        for(size_t j = 0; j < this->getNumOfVertices(); j++){
            row.push_back(this->adjMatrix[i][j] * scalar);
        }
        newMatrix.push_back(row);
    }
    Graph newGraph;
    newGraph.loadGraph(newMatrix);
    return newGraph;
}


Graph& Graph::operator+=(const Graph& graph){
    if(this->getNumOfVertices() != graph.getNumOfVertices()){
        throw invalid_argument("Invalid graph - the graphs must have the same number of vertices");
    }
    for(size_t i = 0; i < this->getNumOfVertices(); i++){
        for(size_t j = 0; j < this->getNumOfVertices(); j++){
            this->adjMatrix[i][j] += graph.adjMatrix[i][j];
        }
    }
    return *this;
}

Graph& Graph::operator-=(const Graph& graph){
    if(this->getNumOfVertices() != graph.getNumOfVertices()){
        throw invalid_argument("Invalid graph - the graphs must have the same number of vertices");
    }
    for(size_t i = 0; i < this->getNumOfVertices(); i++){
        for(size_t j = 0; j < this->getNumOfVertices(); j++){
            this->adjMatrix[i][j] -= graph.adjMatrix[i][j];
        }
    }
    return *this;
}

Graph& Graph::operator*=(const Graph& graph){
    *this = *this * graph;
    return *this;
}

Graph& Graph::operator*=(int scalar){
    *this = *this * scalar;
    return *this;
}

Graph& Graph::operator/=(int scalar){
    if(scalar == 0){
        throw invalid_argument("Invalid scalar - cannot divide by 0");
    }
    for(size_t i = 0; i < this->getNumOfVertices(); i++){
        for(size_t j = 0; j < this->getNumOfVertices(); j++){
            this->adjMatrix[i][j] /= scalar;
        }
    }
    return *this;
}



bool contains(const Graph& g1, const Graph& g2) {
    if (g1.getNumOfVertices() < g2.getNumOfVertices()) {
        return false; 
    }

    for (size_t i = 0; i < g2.getNumOfVertices(); ++i) {
        for (size_t j = 0; j < g2.getNumOfVertices(); ++j) {
            if (g2.getGraph()[i][j] != 0 && g1.getGraph()[i][j] == 0) {
                return false; 
            }
        }
    }

    return true;
}

size_t countEdges(const Graph& g) {
    size_t edges = 0;
    for (size_t i = 0; i < g.getNumOfVertices(); ++i) {
        for (size_t j = 0; j < g.getNumOfVertices(); ++j) {
            if (g.getGraph()[i][j] != 0) {
                ++edges;
            }
        }
    }
    return edges;
}

bool Graph::operator>(const Graph& graph){
    if(this->getNumOfVertices() < graph.getNumOfVertices()){
        return false;
    }
    bool ans = false;
    if(this->getNumOfVertices() > graph.getNumOfVertices()){
        ans = contains(*this, graph);
    }
    if(ans == false){
        return countEdges(*this) > countEdges(graph);
    }
    return ans;
}

bool Graph::operator<(const Graph& graph){
    if(this->getNumOfVertices() > graph.getNumOfVertices()){
        return false;
    }
    bool ans = false;
    if(this->getNumOfVertices() < graph.getNumOfVertices()){
        ans = contains(graph, *this);
    }
    if(ans == false){
        return countEdges(*this) < countEdges(graph);
    }
    return ans;
}


bool Graph::operator==(const Graph& graph){
    if(this->getNumOfVertices() != graph.getNumOfVertices()){
        return false;
    }
    for(size_t i = 0; i < this->getNumOfVertices(); i++){
        for(size_t j = 0; j < this->getNumOfVertices(); j++){
            if(this->adjMatrix[i][j] != graph.adjMatrix[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool Graph::operator!=(const Graph& graph){
    return !(*this == graph);
}

bool Graph::operator>=(const Graph& graph){
    return (*this > graph) || (*this == graph);
}

bool Graph::operator<=(const Graph& graph){
    return (*this < graph) || (*this == graph);
}

Graph& Graph::operator++(){
    for(size_t i = 0; i < this->getNumOfVertices(); i++){
        for(size_t j = 0; j < this->getNumOfVertices(); j++){
            this->adjMatrix[i][j]++;
        }
    }
    return *this;
}

Graph Graph::operator++(int){
    Graph temp = *this;
    for(size_t i = 0; i < this->getNumOfVertices(); i++){
        for(size_t j = 0; j < this->getNumOfVertices(); j++){
            this->adjMatrix[i][j]++;
        }
    }
    return temp;
}

Graph& Graph::operator--() {
    for(size_t i = 0; i < this->getNumOfVertices(); i++) {
        for(size_t j = 0; j < this->getNumOfVertices(); j++) {
            this->adjMatrix[i][j]--;
        }
    }
    return *this;
}

Graph Graph::operator--(int){
    Graph temp = *this;
    for(size_t i = 0; i < this->getNumOfVertices(); i++){
        for(size_t j = 0; j < this->getNumOfVertices(); j++){
            this->adjMatrix[i][j]--;
        }
    }
    return temp;
}

Graph Graph::operator+() const {
    return *this;  
}

Graph Graph::operator-() const {
    Graph temp = *this; 
    for(size_t i = 0; i < this->getNumOfVertices(); i++) {
        for(size_t j = 0; j < this->getNumOfVertices(); j++) {
            temp.adjMatrix[i][j] = -temp.adjMatrix[i][j]; 
        }
    }
    return temp; 
}

ostream& ariel::operator<<(ostream& os, const Graph& graph){

    size_t vertices = graph.getNumOfVertices();

    for (size_t i = 0; i < vertices; i++) {
        os << "[";
        for (size_t j = 0; j < vertices; j++) {
            os << graph.getGraph()[i][j];
            if (j != vertices - 1){
                os << ", ";
            } 
        }
        os << "]" << endl;
    }
    return os;
}
