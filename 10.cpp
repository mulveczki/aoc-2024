#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

typedef vector<vector<int>> Heads;

Heads makeEmpty(int n, int m) {
    vector<vector<int>> heads;
    for (int i=0;i<n;i++) {
        vector<int> vi;
        for (int j = 0; j<m; j++) {
            vi.push_back(0);
        }
        heads.push_back(vi);
    }
    return heads;
}

int sumHeads(Heads heads) {
    int sum = 0;
    for(auto line: heads)
        for(auto element: line)
            sum += element;
    return sum;
}

struct Pont {
    int x;
    int y;
};

int findTailsFromHead(vector<string>& vs, Heads& heads, int n, int m, int nextValue = 1) {
    if (vs[n][m] == '9') {
        heads[n][m] = 1;
        return 1;
    }
    int a=0, b=0, c=0, d=0;
    if (n-1>=0 && vs[n-1][m]==to_string(nextValue)[0]) {
        a = findTailsFromHead(vs, heads, n-1, m, nextValue+1);
    }
    if (m-1>=0 && vs[n][m-1]==to_string(nextValue)[0]) {
        b = findTailsFromHead(vs, heads, n, m-1, nextValue+1);
    }
    if (n+1<vs.size() && vs[n+1][m]==to_string(nextValue)[0]) {
        c = findTailsFromHead(vs, heads, n+1, m, nextValue+1);
    }
    if (m+1<vs[0].length() && vs[n][m+1]==to_string(nextValue)[0]) {
        d = findTailsFromHead(vs, heads, n, m+1, nextValue+1);
    }
    return a+b+c+d;
}

int main() {

    long long count = 0;
    ifstream be("be.txt");
    
    vector<string> vs;
    string s;
    
    while (getline(be,s)) {
        vs.push_back(s);
    }
    
    vector<Pont> zeros;
    int n = vs.size();
    int m = vs[0].length();
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (vs[i][j] == '0') {
                zeros.push_back({x: i, y: j});
            }
        }
    }
    
    for(auto el: zeros) {
        Heads heads = makeEmpty(n, m);
        // b) feladat - ami a visszatérési érték
        int distinctroutes = findTailsFromHead(vs, heads, el.x, el.y);
        count += distinctroutes;
        // -------------------------------
        // a) feladat - amit a heads vátozóba ír
        // count += sumHeads(heads);
        // -------------------------------
    }
    
    cout << endl 
         << "==========================" << endl
         << "sum: " << count << endl
         << "==========================" << endl;

    be.close();
    return 0;
}
