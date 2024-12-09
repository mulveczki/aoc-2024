#include <iostream>
#include <vector>
#include <fstream>
#include <string>
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

string decToTrinary(int n)
{
    string s = "";
    int binaryNum[32];

    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 3;
        n = n / 3;
        i++;
    }

    for (int j = i - 1; j >= 0; j--)
        s += to_string(binaryNum[j]);
    
    return s;
}

string itomuv(int hossz, int muv_int) {
    string tri = decToTrinary(muv_int);
    string muv_str = "";
    for (int i = 0; i < hossz-tri.length(); i++) {
        muv_str += "+";
    }
    for (int i=0; i<tri.length(); i++) {
        if (tri[i] == '0')
            muv_str += "+";
        else if (tri[i] == '1'){
            muv_str += "*";
        }
        else {
            muv_str += "|";
        }
    }
    return muv_str;
}

int main() {

    long long count = 0;
    ifstream be("be.txt");
    
    string s;
    while(getline(be, s)) {
        bool lehet = false;
        vector<string> tenyezok;
        long long eredmeny = stoll(s.substr(0, s.find(":")));
        string szamok = s.substr(s.find(":")+2);
        tenyezok = split(szamok, " ");
        
        int lehetosegek = pow(3, tenyezok.size()-1);
        for (int i = 0; i<lehetosegek; i++) {
            string muveletek = itomuv(tenyezok.size()-1, i);
            long long er = stoll(tenyezok[0]);
            for (int j = 0; j<muveletek.size(); j++) {
                if(muveletek[j] == '*') er *= stoll(tenyezok[j+1]);
                else if(muveletek[j] == '+') er += stoll(tenyezok[j+1]);
                else er = stoll(to_string(er) + tenyezok[j+1]);
            }
            if (er == eredmeny) {
                lehet = true;
            }
        }
        
        if (lehet) {
            count+=eredmeny;
        }
        
    }

    cout << endl << "==========================" << endl
         << "sum: " << count << endl
         << "==========================" << endl;

    be.close();
    return 0;
}
