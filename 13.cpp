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

long long minLinKomb(long long ax, long long ay, long long bx, long long by, long long px, long long py) {
    long long start = px/bx, anum;
    for (long long bnum = start; bnum >=0; bnum--) {
        anum = (px - bnum * bx) / ax;
        if ((ax*anum + bx*bnum) == px && (ay*anum + by*bnum) == py) {
            return anum*3 + bnum;
        }
    }
    return 0;
}

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    string s;
    vector<string> vs;
    long long ax = 0, ay = 0, bx = 0, by = 0, px = 0, py = 0;
    
    while(getline(be,s)) {
        if (s.find("A:") != string::npos) {
            long long fX = s.find("X+");
            long long fY = s.find("Y+");
            ax = stoll(s.substr(fX+2, fY-fX-2));
            ay = stoll(s.substr(fY+2, s.length()-fY-2));
        }
        else if (s.find("B:") != string::npos) {
            long long fX = s.find("X+");
            long long fY = s.find("Y+");
            bx = stoll(s.substr(fX+2, fY-fX-2));
            by = stoll(s.substr(fY+2, s.length()-fY-2));
        }
        else if (s.find("Prize:") != string::npos) {
            long long fX = s.find("X=");
            long long fY = s.find("Y=");
            px = stoll(s.substr(fX+2, fY-fX-2));
            py = stoll(s.substr(fY+2, s.length()-fY-2));
            // a) feladat
            count += minLinKomb(ax, ay, bx, by, px, py);
            // b) feladat
            
            px += 10000000000000;
            py += 10000000000000;
            
            long long a = (py*bx - by*px) / (ay*bx - by*ax);
            long long b = (py*ax - ay*px) / (by*ax - ay*bx);
            
            if (a*ax + b*bx == px && a*ay + b*by == py)
                count2 += (a*3 + b);
                                
        }
        vs.push_back(s);
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