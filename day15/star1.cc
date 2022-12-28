#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <cstdio>
#include <deque>
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
    int keyrow = 2000000;
    //int keyrow = 10;
    string line;
    vector<vector<int>>grid;
    vector<string> lines;
    set<int> idxs; 
    set<int> keybeacs;
    while(getline(reader, line)) { lines.push_back(line);} 
    cout << lines << endl;
    for(int i = 0; i < lines.size(); i++) {
        int sensx, sensy, beacx, beacy;
        sscanf(lines[i].c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &sensx, &sensy, &beacx, &beacy);
        int dist = abs(sensx-beacx) + abs(sensy-beacy);
        int span = dist - abs(sensy-keyrow);
        cout << "sensor " << i << ", \t span: " << span << ", \t dist: " << dist << endl;
        if (span <= 0) {continue;}
        for(int i = sensx-span; i <= sensx+span; i++){
            idxs.insert(i);
        }
        if (sensy == keyrow) {idxs.insert(sensx);}
        if (beacy== keyrow) {keybeacs.insert(beacx);}
    }
    for (auto b : keybeacs) {
        cout << "b: " << b << endl;
        idxs.erase(b);
    }
    cout << "res: " << idxs.size() << endl;
}

