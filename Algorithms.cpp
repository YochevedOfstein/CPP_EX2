

#include "Algorithms.hpp"

#include <queue>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
using namespace ariel;


bool Algorithms::isConnected(const Graph& g){

    if(g.getGraph().empty()){

        return true;
    }

    size_t vertices = g.getNumOfVertices();

    if(g.isDirectedGraph()){

        vector<vector<int>> firstDfsCheck = dfsMain(g);

        if(firstDfsCheck.size() == 1){
        return true;
        }

        size_t last = static_cast<size_t>(firstDfsCheck.back().front());
        vector<Color> colors(vertices, White);

        vector<int> secondDfsCheck = dfsVisit(g, last, colors);

        size_t secondDfsSize = secondDfsCheck.size();

        return secondDfsSize == vertices;
    }
    else{

        vector<Color> colors(vertices, White);
        dfsVisit(g, 0, colors);

        for(Color c: colors){
            if(c == White){
                return false;
            }
        }
        return true;
    }
}

string Algorithms::shortestPath(const Graph& g, size_t start, size_t end){

    size_t Vertices = g.getNumOfVertices();

    if(start >= Vertices || end >= Vertices){
        return "Invalid vertex input";
    }
    if(start == end){
        return to_string(start);
    }

    string shortestPath;

    if(!g.isWeightedGraph()){
        shortestPath = bfs(g, start, end);
    }
    else{
        if(!g.hasNegativeWeightedEdges()){
            shortestPath = dijkstra(g, start, end);
        }
        else{
            shortestPath = bellmanFord(g, start, end);
        }
    }

    return shortestPath;
}


string Algorithms::isContainsCycle(const Graph& g){

    size_t vertices = g.getNumOfVertices();
    vector<Color> colors(vertices, White);
    vector<int> parents(vertices, -1);
    vector<int> path;

    for (size_t i = 0; i < vertices; ++i) {

        if (colors[i] == White) {
            string cycle = dfsFindCycle(g, i, colors, parents, path);
            if(!cycle.empty()){
                return cycle; 
            }
        }
    }

    return "-1";
}

string Algorithms::isBipartite(const Graph& g){

    size_t vertices = g.getNumOfVertices();

    vector<vector<int>> adjmatrix = g.getGraph();

    if(g.isDirectedGraph()){
        for(size_t i = 0; i < vertices; i++){
            for(size_t j = 0; j < vertices; j++){
                if(adjmatrix[i][j] != 0 &&  adjmatrix[j][i] == 0){
                    adjmatrix[j][i] = adjmatrix[i][j];
                }
                if(adjmatrix[i][j] == 0 &&  adjmatrix[j][i] != 0){
                    adjmatrix[i][j] = adjmatrix[j][i];
                }
            }
        }
    }

    vector<Color> colors(vertices, White);

    vector<int> setRed;
    vector<int> setBlue;
    queue<size_t> q;

    for(size_t start_vertex = 0; start_vertex < vertices; start_vertex++) {
        if(colors[start_vertex] == White) {
            q.push(start_vertex);
            colors[start_vertex] = Blue;
            setBlue.push_back(start_vertex);

            while (!q.empty()){
                size_t n = q.front();
                q.pop();
                
                for(size_t neighbor: g.getNeighbors(n)){
                    if(colors[n] == colors[neighbor]){
                        return "The graph is not bipartite";
                    }
                    if(colors[neighbor] == White){
                        colors[neighbor] = (colors[n] == Blue) ? Red : Blue;
                        if(colors[neighbor] == Blue) {
                            setBlue.push_back(neighbor);
                        } else {
                            setRed.push_back(neighbor);
                        }
                        q.push(neighbor);
                    }
                }
            } 
        }
    }

    string ans = "The graph is bipartite: A={";
    for(size_t i = 0; i < setBlue.size(); i++){
        ans = ans + to_string(setBlue[i]);
        if(i != setBlue.size() - 1){
            ans = ans + ",";
        }
    }
    ans = ans + "}, b={";
    for(size_t i = 0; i < setRed.size(); i++){
        ans = ans + to_string(setRed[i]);
        if(i != setRed.size() - 1){
            ans = ans + ",";
        }
    }
    ans = ans + "}";
    return ans;
}

string Algorithms::negativeCycle(const Graph& g){

    size_t vertices = g.getNumOfVertices();
    vector<int> distance(vertices, INF);
    vector<int> parent(vertices, -1);
    int startcycle = -1;

    distance[0] = 0;

    for (size_t i = 0; i < vertices; ++i) {
        startcycle = -1;
        for (size_t u = 0; u < vertices; ++u) {
            for (size_t v : g.getNeighbors(u)) {
                int weight = g.getWeight(u, v);
                if (weight != 0) {
                    int dis = distance[u] + weight;
                    if (dis < distance[v]) {
                        distance[v] = dis;
                        parent[v] = static_cast<int>(u);  
                        startcycle = static_cast<int>(v);  
                    }
                }
            }
        }
    }

    if (startcycle != -1) {
        for (size_t i = 0; i < vertices; ++i) {
            startcycle = parent[static_cast<size_t>(startcycle)];
        }
        vector<int> cycle;
        for (int cur = startcycle;; cur = parent[static_cast<size_t>(cur)]) {
            cycle.push_back(cur);
            if (cur == startcycle && cycle.size() > 1) {
                break;
            }
        }
        reverse(cycle.begin(), cycle.end());
        string cycle_str = "Negative cycle: ";
        for (size_t i = 0; i < cycle.size(); ++i) {
            cycle_str += to_string(cycle[i]);
            if (i != cycle.size() - 1) {
                cycle_str += " -> ";
            }
        }
        return cycle_str;
    }

    return "No negative cycle found";
}


string Algorithms::dfsFindCycle(const Graph& g, size_t v, vector<Color>& colors, vector<int>& parents, vector<int>& path){

    colors[v] = Grey;
    path.push_back(v);
    for (size_t neighbor : g.getNeighbors(v)) {
        if (colors[neighbor] == White) {
            parents[neighbor] = v; 
            string cycle = dfsFindCycle(g, neighbor, colors, parents, path);
            if(!cycle.empty()){
                return cycle;
            }
        }
        else if(colors[neighbor] == Grey){
            if(!g.isDirectedGraph() && parents[v] == neighbor){
                continue;
            }

            return createCycle(path, neighbor);
        }
    }
    colors[v] = Black;
    path.pop_back();
    return "";
}

string Algorithms::createCycle(vector<int>& path, size_t src){

    string cycle;
    size_t cycle_start = 0;

    for (size_t i = 0; i < path.size(); i++) {
        if (path[i] == src) {
            cycle_start = i;
            break;
        }
    }
    for (size_t i = cycle_start; i < path.size(); i++) {
        cycle = cycle + to_string(path[i]) + " -> ";
    }
    cycle = cycle + to_string(src);

    return cycle;

}

vector<vector<int>> Algorithms::dfsMain(const Graph& g){

    size_t vertices = g.getNumOfVertices();

    vector<Color> colors(vertices, White);


    vector<vector<int>> dfsmatrix;

    for(size_t i = 0; i < vertices; i++){
        if(colors[i] == White){
            dfsmatrix.push_back(dfsVisit(g, i, colors));
        }
    }

    return dfsmatrix;
}

vector<int> Algorithms::dfsVisit(const Graph& g, size_t v, vector<Color>& colors){

    size_t vertices = g.getNumOfVertices();

    vector<int> dfsOrder;

    colors[v] = Grey;

    dfsOrder.push_back(v);

    for(size_t neighbor: g.getNeighbors(v)){
        if(colors[neighbor] == White){
            dfsOrder.push_back(neighbor);
            dfsVisit(g, neighbor, colors);
        }
    }

    colors[v] = Black;

    return dfsOrder;
  
}

string Algorithms::bfs(const Graph& g, size_t start, size_t end){

    size_t vertices = g.getNumOfVertices();

    vector<Color> colors(vertices, White);

    vector<int> distance(vertices, INF);

    vector<int> parent(vertices, -1);

    colors[start] = Grey;
    distance[start] = 0;

    queue<size_t> q;

    q.push(start);

    while(!q.empty()){
        size_t u = q.front();
        q.pop();

        if(u == end){

            string path = to_string(end);
            while(parent[end] != -1){
                path = to_string(parent[end]) + " -> " + path;
                end = (size_t)parent[end];
            }
            return path;

        }

        for (size_t v : g.getNeighbors(u)) {
            if (colors[v] == White) {
                colors[v] = Grey;
                distance[v] = distance[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }

        colors[u] = Black;
    }

  return "No path found";  
}



string Algorithms::dijkstra(const Graph& g, size_t start, size_t end){

    size_t vertices = g.getNumOfVertices();

    vector<int> distance(vertices, INF);

    vector<int> parent(vertices, -1);

    distance[start] = 0;

    priority_queue<pair<int, size_t>, vector<pair<int, size_t>>, greater<pair<int, size_t>>> pq;

     pq.push({0, start});

    while(!pq.empty()){
        size_t u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        if(u == end){
            string path = to_string(end);
            while(parent[end] != -1){
                path = to_string(parent[end]) + " -> " + path;
                end = (size_t)parent[end];
            }
            return path;
        }

        for (size_t v : g.getNeighbors(u)) {
            if(distance[v] > distance[u] + g.getWeight(u,v)){
                distance[v] = distance[u] + g.getWeight(u,v);
                parent[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return "No path found";  
}

string Algorithms::bellmanFord(const Graph& g, size_t start, size_t end){

    size_t vertices = g.getNumOfVertices();

    if (start >= vertices || end >= vertices) {
        return "Invalid vertex input";
    }

    vector<int> distance(vertices, INF);
    vector<int> parent(vertices, -1);


    vector<vector<int>> adjacencyMatrix = g.getGraph();

    distance[start] = 0;

    for(size_t i = 0; i < vertices - 1; i++){
        for(size_t u = 0; u < vertices; u++){
            for (size_t v : g.getNeighbors(u)) {
                int weight = g.getWeight(u, v);
                if(distance[v] > distance[u] + weight){
                distance[v] = distance[u] + weight;
                parent[v] = u;
                }
            }
        }
    }
    for(size_t u = 0; u < vertices; u++){
        for (size_t neighbor : g.getNeighbors(u)) {
            int weight = g.getWeight(u, neighbor);
            if(distance[u] != INF && distance[neighbor] > distance[u] + weight){
                return "Graph contains negative cycle";
            }
        }
    }

    if(distance[end] == INF){
        return "No path found";
    }

    string path = to_string(end);
    for(size_t i = end; i != start; i = (size_t)parent[i]){
        if(parent[i] == -1){
           return "No path found";         
        }
        path = to_string(parent[i]) + " -> " + path;
    }
    return path;
}

