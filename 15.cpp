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

struct Pont {
    int x;
    int y;
};

int hasEmptyPlace(vector<string>& map, Pont r, char irany) {
    int tav = 1;
    switch (irany) {
        case '>':
            while (r.x+tav < map[0].length() && map[r.y][r.x+tav] != '#') {
                if (map[r.y][r.x+tav] == '.')
                    return tav;
                tav++;
            }
            break;
        case '<':
            while (r.x-tav >= 0 && map[r.y][r.x-tav] != '#') {
                if (map[r.y][r.x-tav] == '.')
                    return tav;
                tav++;
            }
            break;
        case '^':
            while (r.y-tav >= 0 && map[r.y-tav][r.x] != '#') {
                if (map[r.y-tav][r.x] == '.')
                    return tav;
                tav++;
            }
            break;
        case 'v':
            while (r.y+tav < map.size() && map[r.y+tav][r.x] != '#') {
                if (map[r.y+tav][r.x] == '.')
                    return tav;
                tav++;
            }
            break;
    }
    return -1;
}

void moveRobot(vector<string>& map, Pont& r, char irany, int mennyit) {
    switch (irany) {
        case '>':
            map[r.y][r.x] = '.';
            map[r.y][r.x+1] = '@';
            if (mennyit > 1) { // doboz(oka)t tol
                map[r.y][r.x + mennyit] = 'O';
            }
            r.x++;
            break;
        case '<':
            map[r.y][r.x] = '.';
            map[r.y][r.x-1] = '@';
            if (mennyit > 1) { // doboz(oka)t tol
                map[r.y][r.x - mennyit] = 'O';
            }
            r.x--;
            break;
        case '^':
            map[r.y][r.x] = '.';
            map[r.y-1][r.x] = '@';
            if (mennyit > 1) { // doboz(oka)t tol
                map[r.y - mennyit][r.x] = 'O';
            }
            r.y--;
            break;
        case 'v':
            map[r.y][r.x] = '.';
            map[r.y+1][r.x] = '@';
            if (mennyit > 1) { // doboz(oka)t tol
                map[r.y + mennyit][r.x] = 'O';
            }
            r.y++;
            break;
    }
}

bool canMove(vector<string>& map, Pont p, char irany, bool par = false) {
    if (p.x<0 || p.y<0 || p.x>=map[0].length() || p.y>=map.size() || map[p.y][p.x] == '#') return false;
    if (map[p.y][p.x] == '.') return true;
    bool masikresz;
    switch (irany) {
        case '>':
            return canMove(map, (Pont){.x=p.x+1, .y=p.y}, irany);
            break;
        case '<':
            return canMove(map, (Pont){.x=p.x-1, .y=p.y}, irany);
            break;
        case '^':
            masikresz = true;
            if (map[p.y][p.x]==']' && !par)
                masikresz = canMove(map, (Pont){.x=p.x-1, .y=p.y}, irany, true);
            else if (map[p.y][p.x]=='[' && !par)
                masikresz = canMove(map, (Pont){.x=p.x+1, .y=p.y}, irany, true);
            return canMove(map, (Pont){.x=p.x, .y=p.y-1}, irany) && masikresz;
            break;
        case 'v':
            masikresz = true;
            if (map[p.y][p.x]==']' && !par)
                masikresz = canMove(map, (Pont){.x=p.x-1, .y=p.y}, irany, true);
            else if (map[p.y][p.x]=='[' && !par)
                masikresz = canMove(map, (Pont){.x=p.x+1, .y=p.y}, irany, true);
            return canMove(map, (Pont){.x=p.x, .y=p.y+1}, irany) && masikresz;
            break;
        default:
            return true;
            break;
    }
}

void moveIt(vector<string>& map, Pont p, char irany, bool par = false) {
    if (map[p.y][p.x] == '.') {
        switch (irany) {
            case '>':
                map[p.y][p.x] = map[p.y][p.x-1];
                break;
            case '<':
                map[p.y][p.x] = map[p.y][p.x+1];
                break;
            case '^':
                map[p.y][p.x] = map[p.y+1][p.x];
                break;
            case 'v':
                map[p.y][p.x] = map[p.y-1][p.x];
                break;
        }
        return;
    }
    switch (irany) {
        case '>':
            moveIt(map, (Pont){.x=p.x+1, .y=p.y}, irany);
            map[p.y][p.x] = map[p.y][p.x-1];
            break;
        case '<':
            moveIt(map, (Pont){.x=p.x-1, .y=p.y}, irany);
            map[p.y][p.x] = map[p.y][p.x+1];
            break;
        case '^':
            if (map[p.y][p.x]==']' && !par)
                moveIt(map, (Pont){.x=p.x-1, .y=p.y}, irany, true);
            else if (map[p.y][p.x]=='[' && !par)
                moveIt(map, (Pont){.x=p.x+1, .y=p.y}, irany, true);
            moveIt(map, (Pont){.x=p.x, .y=p.y-1}, irany);
            if (!par)
                map[p.y][p.x] = map[p.y+1][p.x];
            else
                map[p.y][p.x] = '.';
            break;
        case 'v':
            if (map[p.y][p.x]==']' && !par)
                moveIt(map, (Pont){.x=p.x-1, .y=p.y}, irany, true);
            else if (map[p.y][p.x]=='[' && !par)
                moveIt(map, (Pont){.x=p.x+1, .y=p.y}, irany, true);
            moveIt(map, (Pont){.x=p.x, .y=p.y+1}, irany);
            if (!par)
                map[p.y][p.x] = map[p.y-1][p.x];
            else
                map[p.y][p.x] = '.';
            break;
    }
}

int main() {

    long long count = 0;
    ifstream be("be.txt");
    
    string s, sB;
    vector<string> map, mapB;
    bool found = false;
    Pont robot;
    
    /* a) feladat
    while (getline(be,s) && s.length()>2) {
        map.push_back(s);
        if (!found)
            for (int i = 0; i<s.length(); i++) {
                if (s[i] == '@') {
                    robot.x = i;
                    robot.y = map.size()-1;
                }
            }
    }
    */
    
    while (getline(be,s) && s.length()>2) {
        sB = "";
        for (int i=0; i<s.length();i++) {
            switch (s[i]) {
                case '#':
                    sB += "##";
                    break;
                case 'O':
                    sB += "[]";
                    break;
                case '.':
                    sB += "..";
                    break;
                case '@':
                    sB += "@.";
                    break;
                default:
                    break;
            }
        }
        mapB.push_back(sB);
        if (!found)
            for (int i = 0; i<sB.length(); i++) {
                if (sB[i] == '@') {
                    robot.x = i;
                    robot.y = mapB.size()-1;
                }
            }
    }
    
    char c;
    int mennyit;
    while (be.get(c)) {
        if (c == '\n') continue;
        /* a) feladat
        mennyit = hasEmptyPlace(map, robot, c);
        if(mennyit != -1) {
            moveRobot(map, robot, c, mennyit);
        }
        */
        if (canMove(mapB, robot, c)) {
            moveIt(mapB, robot, c);
            mapB[robot.y][robot.x] = '.';
            switch (c) {
                case '>':
                    robot.x++;
                    break;
                case '<':
                    robot.x--;
                    break;
                case '^':
                    robot.y--;
                    break;
                case 'v':
                    robot.y++;
                    break;
            }
        }
    }
    
    /* a) feladat
    for (int i = 0; i<map.size(); i++) {
        for (int j = 0; j<map[0].length(); j++) {
            if (map[i][j] == 'O') {
                count += 100*i + j;
            }
        }
    }
    */
    
    for (int i = 0; i<mapB.size(); i++) {
        for (int j = 0; j<mapB[0].length(); j++) {
            if (mapB[i][j] == '[') {
                count += 100*i + j;
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

