#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

bool isGoingOut(vector<string> &v) {
    int rows = v.size();
    if (rows == 0) return false;
    int cols = v[0].size();

    for (int i = 0; i < cols; ++i) {
        if (v[0][i] == '^' || v[rows - 1][i] == 'v') return true;
    }
    for (int i = 0; i < rows; ++i) {
        if (v[i][0] == '<' || v[i][cols - 1] == '>') return true;
    }
    return false;
}

void handleMove(vector<string> &v) {
    int rows = v.size();
    if (rows == 0) return;
    int cols = v[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char &current = v[i][j];
            if (current == 'v') {
                if (i + 1 >= rows || v[i + 1][j] == '#') {
                    current = '<';
                } else {
                    current = 'X';
                    v[i + 1][j] = 'v';
                }
                return;
            } else if (current == '^') {
                if (i - 1 < 0 || v[i - 1][j] == '#') {
                    current = '>';
                } else {
                    current = 'X';
                    v[i - 1][j] = '^';
                }
                return;
            } else if (current == '<') {
                if (j - 1 < 0 || v[i][j - 1] == '#') {
                    current = '^';
                } else {
                    current = 'X';
                    v[i][j - 1] = '<';
                }
                return;
            } else if (current == '>') {
                if (j + 1 >= cols || v[i][j + 1] == '#') {
                    current = 'v';
                } else {
                    current = 'X';
                    v[i][j + 1] = '>';
                }
                return;
            }
        }
    }
}

void copyWithNewObstacle(vector<string> &v, vector<string> &w, int posX, int posY) {
    w = v; // Copy directly
    w[posX][posY] = '#'; // Add the obstacle
}

int main() {

    long long count = 0;
    ifstream be("be.txt");
     
    vector<string> v, vv;
    string s;

    while (getline(be, s)) {
        v.push_back(s);
    }

    vector<string> alap = v;
    while (!isGoingOut(alap)) {
        handleMove(alap);
    }

    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[0].size(); ++j) {
            if (alap[i][j] == 'X') {
                copyWithNewObstacle(v, vv, i, j);

                int qq = 0, max_iter = 99999;
                while (!isGoingOut(vv) && qq < max_iter) {
                    handleMove(vv);
                    ++qq;
                }

                if (qq == max_iter) {
                    ++count;
                }
            }
        }
    }

    cout << endl << "==========================" << endl
         << "sum: " << count << endl
         << "==========================" << endl;

    be.close();
    return 0;
}
