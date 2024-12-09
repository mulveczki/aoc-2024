#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int main() {

    long long count = 0;
    ifstream be("be.txt");
    
    char c;
    vector<string> vs;
    
    bool isFile = true;
    int id = 0;
    
    while(be.get(c)) {
        for (int i=0; i<(int)(c-'0'); i++) {
            if (isFile)
                vs.push_back(to_string(id));
            else
                vs.push_back(".");
        }
        if (isFile) id++;
        isFile = !isFile;
    }
    
    // a) feladat
    for (int i=0,j=vs.size()-1; i<j; i++) {
        if (vs[i] == ".") {
            vs[i] = vs[j];
            vs[j] = ".";
            j--;
        }
        while(vs[j] == ".")
            j--;
    }
    // b) feladat
    int hossz_to_copy = 0;
    for (int j=vs.size()-1; j>0; j -= hossz_to_copy) {
        
        while(vs[j] == ".")
            j--;
        
        hossz_to_copy = 0;
        while (j-hossz_to_copy-1>=0 && vs[j-hossz_to_copy] == vs[j]) {
            hossz_to_copy++;
        }
        
        bool copied = false;
        int i = 0;
        int hossz_place = 0;
        while (!copied && i<j) {
            if(vs[i] == ".") {
                hossz_place++;
            }
            else {
                if(hossz_place >= hossz_to_copy) {
                    for (int k = 0; k<hossz_to_copy; k++) {
                        vs[i-hossz_place+k] = vs[j-hossz_to_copy+1+k];
                        vs[j-hossz_to_copy+k+1] = ".";
                    }
                    
                    copied = true;
                }
                hossz_place = 0;
            }
            i++;
        }
        
    }
    
    for (int i=0; i<vs.size(); i++){
        if (vs[i] != ".") {
            count += stoll(vs[i])*i;
        }
    }
   
    cout << endl << "==========================" << endl
         << "sum: " << count << endl
         << "==========================" << endl;

    be.close();
    return 0;
}
