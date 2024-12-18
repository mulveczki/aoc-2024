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

int modulo( long long value, int m) {
    int mod = value % m;
    if (mod < 0) {
        mod += m;
    }
    return mod;
}

struct Robot {
    int px;
    int py;
    int vx;
    int vy;
};

bool isEmptyBottom (vector<string>& palya, int also_sorok, int szele) {
    for (int i = palya.size()-also_sorok; i<palya.size(); i++) {
        for (int j = 0; j<szele; j++)
            if (palya[i][j] == '#')
                return false;
        for (int j = palya[0].length()-szele; j<palya[0].length(); j++)
            if (palya[i][j] == '#')
                return false;
    }
    return true;
}

bool drawMap(vector<Robot> robotok, int n, int m, int also_sorok, int szele) {
    cout<<"============"<<endl;
    cout<<"============"<<endl;
    vector<string> vs;
    bool b = false;
    for (int i = 0; i<m; i++) {
        string s = "";
        for (int j = 0; j<n; j++) {
            s += ' ';
        }
        vs.push_back(s);
    }
    for (auto r: robotok) {
         vs[r.py][r.px] = '#';
    }
    if (isEmptyBottom(vs, also_sorok, szele)) {
        b = true;
        for (auto s: vs) {
            cout<<s<<endl;
        }
    }
    return b;
}

void moveRobotsOneStep(vector<Robot>& robotok, int n, int m) {
    for (int i = 0; i<robotok.size(); i++) {
        robotok[i].px = modulo(robotok[i].px+robotok[i].vx, n);
        robotok[i].py = modulo(robotok[i].py+robotok[i].vy, m);
    }
}

int main() {

    long long count = 0;
    ifstream be("be.txt");

    long long n=101, m=103, steps = 100;
    //long long n=11, m=7, steps = 100;
    long long countBF = 0, countJF = 0, countJL = 0, countBL = 0;
    string s;
    vector<Robot> robotok;
    int px, py, vx, vy;
    while (getline(be,s)) {
        int fev = s.find(",");
        int fv = s.find("v=");
        int fmv = fv + s.substr(fv).find(",");

        px = stoi(s.substr(2, fev-2));
        py = stoi(s.substr(fev+1, fv-fev-2));
        vx = stoi(s.substr(fv+2, fmv-fv-2));
        vy = stoi(s.substr(fmv+1, s.length()-fmv-1));
        robotok.push_back({.px = px, .py = py, .vx = vx, .vy = vy});

        int finalX = modulo(px+steps*vx,n);
        int finalY = modulo(py+steps*vy,m);

        if (finalX <= (n/2-1) && finalY <= (m/2-1)) countBF++;
        else if (finalX >= ((n+3)/2-1) && finalY <= (m/2-1)) countJF++;
        else if (finalX >= ((n+3)/2-1) && finalY >= ((m+3)/2-1)) countJL++;
        else if (finalX <= (n/2-1) && finalY >= ((m+3)/2-1)) countBL++;
    }
     
    count = countBF * countJF * countBL * countJL;
    
    long long qqq = 1, from = 5000, to = 8000; // 5000-8000, 7138. lépés
    while(qqq <= to) {
        moveRobotsOneStep(robotok, n, m);
        if (qqq >= from) {
            if (drawMap(robotok, n, m, 0, 0)) {
                cout << qqq << ". lépés" << endl;
                this_thread::sleep_for(chrono::milliseconds(300));
            }
        }
        qqq++;
    }
    
    cout                                 << endl
         << "==========================" << endl
         << "sum: " << count             << endl
         << "==========================" << endl;

    be.close();
    return 0;
}
