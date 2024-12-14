#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

void getAreaAndPerimeter(vector<string>& vs, int i, int j, int& area, int& perimeter, char c) {
    area++;
    perimeter += 4;
    vs[i][j] = tolower(c);
    if (i-1>=0 && toupper(vs[i-1][j]) == c) {
        perimeter--;
        if (vs[i-1][j] == c)
            getAreaAndPerimeter(vs, i-1, j, area, perimeter, c);
    }
    if (i+1<vs.size() && toupper(vs[i+1][j]) == c) {
        perimeter--;
        if (vs[i+1][j] == c)
            getAreaAndPerimeter(vs, i+1, j, area, perimeter, c);
    }
    if (j-1>=0 && toupper(vs[i][j-1]) == c) {
        perimeter--;
        if (vs[i][j-1] == c)
            getAreaAndPerimeter(vs, i, j-1, area, perimeter, c);
    }
    if (j+1<vs[0].size() && toupper(vs[i][j+1]) == c) {
        perimeter--;
        if (vs[i][j+1] == c)
            getAreaAndPerimeter(vs, i, j+1, area, perimeter, c);
    }
    
}

void getAreaAndSides(vector<string>& vs, int i, int j, int& area, int& sides, char c) {
    area++;
    vs[i][j] = tolower(c);
    // jobb felső sarok
    if ((i==0 && j+1 == vs[0].size())
        || (i==0 && j+1<vs[0].size() && c!=toupper(vs[i][j+1]))
        || (j == vs[0].size()-1 && i>0 && c!=toupper(vs[i-1][j]))
        || (i>0 && j+1<vs[0].size() && c!=toupper(vs[i][j+1]) && c!=toupper(vs[i-1][j])))
        sides++;
    
    // bal felső sarok
    if ((i==0 && j == 0)
        || (i==0 && j>0 && c!=toupper(vs[i][j-1]))
        || (j == 0 && i>0 && c!=toupper(vs[i-1][j]))
        || (i>0 && j>0 && c!=toupper(vs[i][j-1]) && c!=toupper(vs[i-1][j])))
        sides++;
    
    // jobb alsó sarok
    if ((i+1 == vs.size() && j+1 == vs[0].size())
        || (i+1 == vs.size() && j+1<vs[0].size() && c!=toupper(vs[i][j+1]))
        || (j == vs[0].size()-1 && i+1 < vs.size() && c!=toupper(vs[i+1][j]))
        || (i+1 < vs.size() && j+1<vs[0].size() && c!=toupper(vs[i][j+1]) && c!=toupper(vs[i+1][j])))
        sides++;
    
    // bal alsó sarok
    if ((i+1 == vs.size() && j == 0)
        || (i+1 == vs.size() && j>0 && c!=toupper(vs[i][j-1]))
        || (j == 0 && i+1 < vs.size() && c!=toupper(vs[i+1][j]))
        || (i+1 < vs.size() && j>0 && c!=toupper(vs[i][j-1]) && c!=toupper(vs[i+1][j])))
        sides++;
    
    
    // jobb felül
    if (i-1 >= 0 && toupper(vs[i-1][j]) == c
        && j+1 < vs[0].length() && toupper(vs[i][j+1]) == c
        && toupper(vs[i-1][j+1]) != c) sides++;
    // jobb alul
    if (i+1 < vs.size() && toupper(vs[i+1][j]) == c
        && j+1 < vs[0].length() && toupper(vs[i][j+1]) == c
        && toupper(vs[i+1][j+1]) != c) sides++;
    // bal felül
    if (i-1 >= 0 && toupper(vs[i-1][j]) == c
        && j-1 >=0 && toupper(vs[i][j-1]) == c
        && toupper(vs[i-1][j-1]) != c) sides++;
    // bal alul
    if (i+1 < vs.size() && toupper(vs[i+1][j]) == c
        && j-1 >=0 && toupper(vs[i][j-1]) == c
        && toupper(vs[i+1][j-1]) != c) sides++;
    
    
    if (i-1>=0 && vs[i-1][j] == c) {
        getAreaAndSides(vs, i-1, j, area, sides, c);
    }
    if (i+1<vs.size() && vs[i+1][j] == c) {
        getAreaAndSides(vs, i+1, j, area, sides, c);
    }
    if (j-1>=0 && vs[i][j-1] == c) {
        getAreaAndSides(vs, i, j-1, area, sides, c);
    }
    if (j+1<vs[0].size() && vs[i][j+1] == c) {
        getAreaAndSides(vs, i, j+1, area, sides, c);
    }
    
}

void clearArea(vector<string>& vs, int i, int j, char c) {
    vs[i][j] = '.';
    if (i-1>=0 && vs[i-1][j] == c) {
        clearArea(vs, i-1, j, c);
    }
    if (i+1<vs.size() && vs[i+1][j] == c) {
        clearArea(vs, i+1, j, c);
    }
    if (j-1>=0 && vs[i][j-1] == c) {
        clearArea(vs, i, j-1, c);
    }
    if (j+1<vs[0].size() && vs[i][j+1] == c) {
        clearArea(vs, i, j+1, c);
    }
}

int main() {

    long long count = 0;
    ifstream be("be.txt");
    
    string s;
    vector<string> vs;
    while (getline(be,s)) {
        vs.push_back(s);
    }
    
    for (int i=0; i<vs.size(); i++) {
        for (int j=0; j<vs[0].size(); j++) {
            if (vs[i][j] != '.') {
                int area = 0, perimeter = 0, sides = 0;
                cout<<"("<<vs[i][j]<<") ";
                // a) feladat
                //getAreaAndPerimeter(vs, i, j, area, perimeter, vs[i][j]);
                //cout<<"Area: "<<area<<" Perimeter: "<<perimeter<<" Value: "<<area*perimeter<<endl;
                //count += area * perimeter;
                // b) feladat
                getAreaAndSides(vs, i, j, area, sides, vs[i][j]);
                cout<<"Area: "<<area<<" Sides: "<<sides<<" Value: "<<area*sides<<endl;
                count += area * sides;
                clearArea(vs, i, j, vs[i][j]);
            }
        }
    }
   
    cout                                 << endl
         << "==========================" << endl
         << "sum: " << count             << endl
         << "==========================" << endl;

    be.close();
    return 0;
}
