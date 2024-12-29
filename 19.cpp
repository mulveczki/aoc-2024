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

using namespace std;

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

map<string, long long> found;

long long patternDoable(string pattern, vector<string>& towels) {

    if (pattern == "") return 1;
    
    if (found.find(pattern) != found.end()) {
        return found[pattern];
    }

    long long count = 0;

    for(int i = 1; i<=pattern.length(); i++) {
        if (find(towels.begin(), towels.end(), pattern.substr(0,i)) != towels.end()) {
            count += patternDoable(pattern.substr(i), towels);
        }
    }

    found[pattern] = count;
    return count;
}

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    vector<string> towels;
    string s;
    
    getline(be, s);
    towels = split(s, ", ");
    getline(be, s);
    
    while(getline(be, s)) {
        if (count2 += patternDoable(s, towels)) {
            count++;
        }
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