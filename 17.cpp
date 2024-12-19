#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <string>
#include <numeric>
#include <unistd.h>
#include <chrono>
#include <thread>

using namespace std;

template <class T>
void printAll(vector<T> &v, char c = '\n') {
    for (const auto &row : v) {
        cout << row << c;
    }
    cout << endl;
}

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

long long combo(int& val, long long& a, long long& b, long long& c) {
    switch (val) {
        case 0:
        case 1:
        case 2:
        case 3:
            return val;
        case 4:
            return a;
        case 5:
            return b;
        case 6:
            return c;
        case 7:
            cout<<endl<<"COMBO HIBA - INPUT: 7"<<endl;
            return val;
    }
    return val;
}

string runProgram(vector<int>& program, long long a, long long b, long long c) {
    string s = "";
    
    for (int i = 0; i<program.size(); i+=2) {
        switch (program[i]) {
            case 0:
                a = a / pow(2,combo(program[i+1], a, b, c));
                break;
            case 1:
                b = b^program[i+1];
                break;
            case 2:
                b = combo(program[i+1], a, b, c) % 8;
                break;
            case 3:
                if (a>0)
                    i = program[i+1] - 2;
                break;
            case 4:
                b = b^c;
                break;
            case 5:
                s += to_string(combo(program[i+1], a, b, c) % 8);
                s += ",";
                break;
            case 6:
                b = a / pow(2,combo(program[i+1], a, b, c));
                break;
            case 7:
                c = a / pow(2,combo(program[i+1], a, b, c));
                break;
        }
    }
    return s;
}

int calcOneStep(long long A) {
    return ((int)(A%8)^5^6^(A/(int)pow(2,(A%8)^5)))%8;
}

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    ifstream be("be.txt");
    
    long long a, b, c;
    string s;
    vector<string> vs;
    vector<int> vi;
    
    getline(be,s);
    a = stoll(s.substr(s.find("A:")+3));
    
    getline(be,s);
    b = stoll(s.substr(s.find("B:")+3));
    
    getline(be,s);
    c = stoll(s.substr(s.find("C:")+3));
    
    getline(be,s);
    getline(be,s);
    s = s.substr(s.find(":")+2);
    vs = split(s, ",");
    
    for (auto el: vs)
        vi.push_back(stoi(el));
    
    // a) feladat
    cout << runProgram(vi, a, b, c) << endl;
    
    // b) feladat
    vector<long long> v1, v2, vGood;
    v1.push_back(0);
    for (int i = vi.size()-1; i>=0; i--) {
        for(auto el: v1) {
            for (int j = 0; j < 8; j++) {
                if (calcOneStep(el*8+j) == vi[i])
                    v2.push_back(el*8+j);
            }
        }
        v1.empty();
        v1 = v2;
        v2.empty();
    }
    
    s += ",";
    for (int i = 0; i<v1.size(); i++) {
        string programOutput = runProgram(vi, v1[i], b, c);
        if (s.compare(programOutput) == 0)
            vGood.push_back(v1[i]);
    }
    
    cout << *min_element(vGood.begin(), vGood.end()) << endl;

    cout                                 << endl
         << "==========================" << endl
         << "sum: " << count             << endl
         << "==========================" << endl;
    
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stopTime - startTime);
    cout << "Execution time: " << duration.count()/1000.0/1000.0 << "s" << endl;
    
    be.close();
    return 0;
}
