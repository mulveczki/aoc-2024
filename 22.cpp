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

using namespace std;

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    long long a;
    int priceActual, priceLast;
    vector<int> diffs;
    vector<vector<int>> maps;
    int num;
    
    while (!be.eof()) {
        vector<int> map(130321,0);
        be>>a;
        //cout<<a;
        priceLast = a % 10;
        diffs.clear();
        for (int i = 0; i<2000; i++) {
            a = ((a*64)^a)%16777216;
            a = ((a/32)^a)%16777216;
            a = ((a*2048)^a)%16777216;
            priceActual = a % 10;
            diffs.push_back(priceActual-priceLast);
            if (i>3)
                diffs.erase(diffs.begin());
            if (i>2) {
                num = (diffs[0]+9) + (diffs[1]+9)*19 + (diffs[2]+9)*19*19 + (diffs[3]+9)*19*19*19;
                if (map[num] == 0)
                    map[num] = priceActual+1;
            }
            priceLast = priceActual;
        }
        //cout << ": " << a << endl;
        count += a;
        maps.push_back(map);
    }
    
    for (int i = 0; i<maps[0].size(); i++) {
        int sum = 0;
        for (int j = 0; j<maps.size(); j++) {
            if (maps[j][i] > 0)
                sum += (maps[j][i]-1);
        }
        if (sum > count2)
            count2 = sum;
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