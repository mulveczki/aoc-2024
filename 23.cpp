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
#include <set>
#include <map>
#include <algorithm>
using namespace std;

void bron_kerbosch(map<string, set<string>> &graph, set<string> r, set<string> p, set<string> x, vector<set<string>> &cliques) {
    if (p.empty() && x.empty()) {
        cliques.push_back(r);
    } else {
        set<string> union_px;
        set_union(p.begin(), p.end(), x.begin(), x.end(), inserter(union_px, union_px.begin()));
        
        string u = *union_px.begin(); // Pivot vertex
        set<string> p_minus_neighbors;
        set_difference(p.begin(), p.end(), graph[u].begin(), graph[u].end(), inserter(p_minus_neighbors, p_minus_neighbors.begin()));

        for (string v : p_minus_neighbors) {
            set<string> new_r = r;
            new_r.insert(v);
            set<string> new_p;
            set<string> new_x;
            
            set_intersection(p.begin(), p.end(), graph[v].begin(), graph[v].end(), inserter(new_p, new_p.begin()));
            set_intersection(x.begin(), x.end(), graph[v].begin(), graph[v].end(), inserter(new_x, new_x.begin()));
            
            bron_kerbosch(graph, new_r, new_p, new_x, cliques);
            p.erase(v);
            x.insert(v);
        }
    }
}

set<string> find_largest_complete_subgraph(map<string, set<string>> &graph) {
    vector<set<string>> cliques;
    set<string> r, x;
    set<string> p;
    for (auto &kv : graph) {
        p.insert(kv.first);
    }
    
    bron_kerbosch(graph, r, p, x, cliques);
    
    return *max_element(cliques.begin(), cliques.end(), [](const set<string> &a, const set<string> &b) {
        return a.size() < b.size();
    });
}

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    
    string s;
    vector<string> vs;
    vector<string> conn;
    
    map<string, set<string>> graph;
    
    while(getline(be,s)) {
        vs.push_back(s);
        graph[s.substr(0,2)].insert(s.substr(3,2));
        graph[s.substr(3,2)].insert(s.substr(0,2));
    }
    
    // a) feladat
    for (int i = 0; i<vs.size(); i++) {
        
        for (int j = 0; j<vs.size(); j++) {
            if (i != j) {
                string i_elso = vs[i].substr(0,2);
                string i_maso = vs[i].substr(3,2);
                string j_elso = vs[j].substr(0,2);
                string j_maso = vs[j].substr(3,2);
                
                if (i_elso == j_elso) {
                    if ((find(vs.begin(), vs.end(), i_maso + "-" + j_maso) != vs.end()
                        || find(vs.begin(), vs.end(), j_maso + "-" + i_maso) != vs.end())
                        && (i_elso[0] == 't' || i_maso[0] == 't' || j_maso[0] == 't')) {
                        conn.push_back(i_elso + "-" + i_maso + "-" + j_maso);
                        count++;
                    }
                }
                if (i_maso == j_maso) {
                    if ((find(vs.begin(), vs.end(), i_elso + "-" + j_elso) != vs.end()
                        || find(vs.begin(), vs.end(), j_elso + "-" + i_elso) != vs.end())
                        && (i_maso[0] == 't' || i_elso[0] == 't' || j_elso[0] == 't')) {
                        conn.push_back(i_maso + "-" + i_elso + "-" + j_elso);
                        count++;
                    }
                }
                if (i_elso == j_maso) {
                    if ((find(vs.begin(), vs.end(), i_maso + "-" + j_elso) != vs.end()
                        || find(vs.begin(), vs.end(), j_elso + "-" + i_maso) != vs.end())
                        && (i_elso[0] == 't' || i_maso[0] == 't' || j_elso[0] == 't')) {
                        conn.push_back(i_elso + "-" + i_maso + "-" + j_elso);
                        count++;
                    }
                }
                if (i_maso == j_elso) {
                    if ((find(vs.begin(), vs.end(), i_elso + "-" + j_maso) != vs.end()
                        || find(vs.begin(), vs.end(), j_maso + "-" + i_elso) != vs.end())
                        && (i_maso[0] == 't' || i_elso[0] == 't' || j_maso[0] == 't')) {
                        conn.push_back(i_maso + "-" + i_elso + "-" + j_maso);
                        count++;
                    }
                }
            }
        }
    }
    
    count /= 6;
    
    // b) feladat
    set<string> largest_clique = find_largest_complete_subgraph(graph);
        
    cout << "Largest complete subgraph: ";
    for (string v : largest_clique) {
        cout << v << ",";
    }

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