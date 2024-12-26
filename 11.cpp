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
#include <queue>
#include <unordered_map>
#include <cmath>
#include <random>
using namespace std;

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    map<long long, long long> stones;
    string s;
    while (!be.eof()) {
        be >> s;
        stones[stoll(s)]++;
    }
    
    for (int i = 0; i<75; i++) {
        map<long long, long long> stones2;
        for(auto stone: stones) {
            if (stone.first == 0) {
                stones2[1]+=stone.second;
            }
            else if (to_string(stone.first).length() % 2 == 0) {
                string vls = to_string(stone.first);
                long long vls1 = stoll(vls.substr(0, vls.length()/2));
                long long vls2 = stoll(vls.substr(vls.length()/2, vls.length()/2));
                stones2[vls1]+=stone.second;
                stones2[vls2]+=stone.second;
            }
            else {
                stones2[stone.first*2024]+=stone.second;
            }
        }
        stones = stones2;
    }
    
    for (auto stone: stones)
        count += stone.second;
    
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