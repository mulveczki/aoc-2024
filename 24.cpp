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

int calcOutputValue(
                    map<string, int>& inputs,
                    map<string, tuple<string, string, string>>& rules,
                    string output,
                    bool p = false,
                    int subCalc = 0) {
    
    if (auto search = inputs.find(output); search != inputs.end())
        return search->second;
    auto [input1, input2, op] = rules[output];
    if (p) {
        for (int i = 0; i < subCalc; i++) {cout<<"-";}
        cout << "("<< output <<") " <<  input1 << op << input2 << endl;
    }
    
    // ha AND
    if (op == "AND") return calcOutputValue(inputs, rules, input1, p, subCalc+1) & calcOutputValue(inputs, rules, input2, p, subCalc+1);
    // ha OR
    if (op == "OR") return calcOutputValue(inputs, rules, input1, p, subCalc+1) | calcOutputValue(inputs, rules, input2, p, subCalc+1);
    // ha XOR
    return calcOutputValue(inputs, rules, input1, p, subCalc+1) ^ calcOutputValue(inputs, rules, input2, p, subCalc+1);
}

void swapRules(map<string, tuple<string, string, string>>& rules, string egyik, string masik) {
    auto cs = rules[egyik];
    rules[egyik] = rules[masik];
    rules[masik] = cs;
}

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    map<string, int> inputs;
    map<string, tuple<string, string, string>> rules;
    set<string> outputs;
    
    string s;
    while (getline(be, s) && s.length()>0) {
        inputs[s.substr(0,s.find(":"))] = stoi(s.substr(s.find(":")+2,1));
    }
    
    while (getline(be,s)) {
        vector<string> data = split(s, " ");
        string input1 = data[0];
        string op = data[1];
        string input2 = data[2];
        string output = data[4];
        rules[output] = {input1, input2, op};
        if (output[0] == 'z')
            outputs.insert(output);
    }
    
    cout<<"  x: ";
    for (int i = 0; i<45; i++) {
        if (i<10)
            cout<<inputs["x0"+to_string(i)];
        else
            cout<<inputs["x"+to_string(i)];
        if ((i+1)%5 == 0) cout<<" ";
    }
    cout<<endl;
    
    cout<<"  y: ";
    for (int i = 0; i<45; i++) {
        if (i<10)
            cout<<inputs["y0"+to_string(i)];
        else
            cout<<inputs["y"+to_string(i)];
        if ((i+1)%5 == 0) cout<<" ";
    }
    cout<<endl;
    
    swapRules(rules, "z10", "kmb");
    swapRules(rules, "z15", "tvp");
    swapRules(rules, "z25", "dpg");
    swapRules(rules, "vdk", "mmf");
    
    cout<<"out: ";
    
    int i = 0;
    for (auto el: outputs) {
        int outputValue = calcOutputValue(inputs, rules, el, false);
        count += pow(2, i) * outputValue;
        i++;
        cout<<outputValue;
        if (i%5 == 0) cout<<" ";
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