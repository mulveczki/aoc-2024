#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <string>
#include <numeric>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <limits>
#include <limits.h>
#include <set>
#include <map>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <random>

using namespace std;

int minDistance(int dist[], int n, bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 
void printSolution(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    //for (int i = 0; i < n; i++)
    //    printf("\t%d \t\t\t\t %d\n", i, dist[i]);
    printf("%d \t\t %d\n", n-1, dist[n-1]);
}
 
void dijkstra(vector<vector<int>>& graph, int src)
{
    int V = graph.size();
    int dist[V];
 
    bool sptSet[V];
    
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    dist[src] = 0;
 
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, graph.size(), sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
 
    printSolution(dist, V);
}
 


int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    int size = 71;
    int limit = 2936;
    vector<vector<int>> graph;
    
    for (int i = 0; i<size*size; i++) {
        vector<int> v(size*size,0);
        graph.push_back(v);
    }

    vector<vector<int>> map(size,vector<int>(size, 0));
    
    string s;
    int q = 0;
    while (q<limit && getline(be,s)) {
        int a = stoi(s.substr(0, s.find(",")));
        int b = stoi(s.substr(s.find(",")+1));
        map[b][a] = WALL;
        q++;
        if (q == limit)
            cout<<"--> "<<a<<","<<b<<" <--"<<endl;
    }
    
    for (int i = 0; i<size; i++) {
        for (int j = 0; j<size; j++) {
            if (j<size-1 && map[i][j] == 0 && map[i][j+1] == 0) {
                graph[i*size+j][i*size+j+1] = 1;
                graph[i*size+j+1][i*size+j] = 1;
            }
            if (i<size-1 && map[i][j] == 0 && map[i+1][j] == 0) {
                graph[i*size+j][(i+1)*size+j] = 1;
                graph[(i+1)*size+j][i*size+j] = 1;
            }
        }
    }
    
    if (map[(size-1)][(size-1)] == 0 && map[(size-1)][(size-2)] == 0) {
        graph[(size-1)*size+(size-1)][(size-1)*size+(size-2)] = 1;
        graph[(size-1)*size+(size-2)][(size-1)*size+(size-1)] = 1;
    }
    if (map[(size-1)][(size-1)] == 0 && map[(size-2)][(size-1)] == 0) {
        graph[(size-1)*size+(size-1)][(size-2)*size+(size-1)] = 1;
        graph[(size-2)*size+(size-1)][(size-1)*size+(size-1)] = 1;
    }

    dijkstra(graph, 0);
    
    cout                                 << endl
         << "==========================" << endl
         << "sum: " << count             << endl
         << "==========================" << endl;

    if (count2 != 0)
    cout << "sum2: " << count2           << endl
         << "==========================" << endl;
    
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stopTime - startTime);
    cout << "Execution time: " << duration.count()/1000.0/1000.0 << "s" << endl;
    
    be.close();
    return 0;
}