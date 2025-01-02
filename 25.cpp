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
#include <list>
#include <map>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <random>
#include <deque>
using namespace std;

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    vector<int> input(5);
    vector<vector<int>> keys, locks;
    
    string s;
    while(!be.eof()) {
        bool isKey = false, isLock = false;
        fill(input.begin(), input.end(), -1);
        for (int i = 0; i<7; i++) {
            getline(be,s);
            for (int j = 0; j<s.length(); j++) {
                if (s[j] == '#')
                    input[j]++;
            }
            if (i == 0 && s[0] == '#' && s[1] == '#' && s[2] == '#' && s[3] == '#' && s[4] == '#')
                isLock = true;
            if (i == 6 && s[0] == '#' && s[1] == '#' && s[2] == '#' && s[3] == '#' && s[4] == '#')
                isKey = true;
        }
        if (isLock)
            locks.push_back(input);
        if (isKey)
            keys.push_back(input);
        
        getline(be,s);
    }
    
    for (auto key: keys) {
        for (auto lock: locks) {
            bool joe = true;
            for (int i = 0;i<5;i++) {
                if (key[i]+lock[i] > 5)
                    joe = false;
            }
            if (joe)
                count++;
        }
    }
    
    cout                            << endl
    << "==========================" << endl
    << "sum: " << count             << endl
    << "==========================" << endl;
    
    if (count2 != 0)
        cout
        << "sum2: " << count2           << endl
        << "==========================" << endl;
    
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stopTime - startTime);
    cout << "Execution time: " << duration.count()/1000.0/1000.0 << "s" << endl;
    
    be.close();
    return 0;
}