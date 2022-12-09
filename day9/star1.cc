#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]\n";
    return os;
}

int main() {

    ifstream reader("inputr.txt");
    string line;
    vector<vector<int>>grid;

    stringstream ss(line);
    vector<string> dirs;
    vector<int> amts;
    string str;
    
    while(getline(reader, line)) {
//        cout << line << endl;
        stringstream ss(line);
        getline(ss, str, ' '); 
        dirs.push_back(str);
        getline(ss, str, ' '); 
        amts.push_back(stoi(str));
    }

    map<tuple<int, int>, int> positions;
    int headx = 0;
    int heady = 0;
    int tailx = 0;
    int taily = 0;
    for (int i = 0; i < amts.size(); i++) {
        
        for (int j = 0; j < amts[i]; j++ ) {
            if (dirs[i] == "L") { headx -= 1; }
            if (dirs[i] == "R") { headx += 1; }
            if (dirs[i] == "U") { heady += 1; }
            if (dirs[i] == "D") { heady -= 1; }
            if (headx - tailx > 1) {
                if (heady == taily) {
                    tailx = headx - 1;
                } else {
                    tailx = headx - 1;
                    taily = heady;
                }
            }
            if (headx - tailx < -1) {
                if (heady == taily) {
                    tailx = headx + 1;
                } else {
                    tailx = headx + 1;
                    taily = heady;
                }
            }

            if (heady - taily > 1) {
                if (heady == taily) {
                    taily = heady - 1;
                } else {
                    taily = heady - 1;
                    tailx = headx;
                }
            }
            if (heady - taily < -1) {
                if (heady == taily) {
                    taily = heady + 1;
                } else {
                    taily = heady + 1;
                    tailx = headx;
                }
            }
            cout << "head: " << headx << ", " << heady << endl;
            cout << "tail: " << tailx << ", " << taily << endl;
            positions[make_tuple(tailx, taily)]++;
        }
    }
    for (auto&& item : positions)
        cout << get<0>(item.first) << ", " << get<0>(item.first)  << ": " << item.second << '\n';

    
    cout << "res: " << positions.size() << endl;

    

    
}

