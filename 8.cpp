#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int main() {

    long long count = 0;
    ifstream be("be.txt");
 
    string s;
    vector<string> map;
    vector<char> ant_type;
    while(getline(be,s)) {
        map.push_back(s);
        for (int i=0; i<s.length(); i++) {
            if (s[i] != '.' && find(ant_type.begin(),ant_type.end(),s[i]) == ant_type.end())
                ant_type.push_back(s[i]);
        }
    }
    vector<string> map_copy = map;
    for (int i=0;i<ant_type.size();i++) {
        vector<int> x,y;
        
        for (int j=0; j<map.size(); j++) {
            for (int k=0; k<map[0].length(); k++) {
                if (map[j][k] == ant_type[i]) {
                    x.push_back(k);
                    y.push_back(j);
                }
            }
        }
        
        for (int j=0; j<x.size(); j++) {
            for (int k=0; k<x.size(); k++) {
                for (int l=0; l<50; l++) {
                    int xx = x[k] + l*(x[k] - x[j]);
                    int yy = y[k] + l*(y[k] - y[j]);
                    if (j!=k && xx >= 0 && yy >=0 && xx < map[0].length() && yy < map.size()) {
                        map_copy[yy][xx] = '#';
                    }
                }
            }
        }
    }
        
    for (int j=0; j<map_copy.size(); j++) {
        for (int k=0; k<map_copy[0].length(); k++) {
            cout << map_copy[j][k];
            if(map_copy[j][k] == '#')
                count++;
        }
        cout<<endl;
    }
    
    cout << endl << "==========================" << endl
         << "sum: " << count << endl
         << "==========================" << endl;

    be.close();
    return 0;
}
