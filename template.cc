#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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

    ifstream reader("input.txt");
    string line;
    vector<vector<int>>grid;
    vector<string> lines;
    while(getline(reader, line)) { lines.push_back(line);} 
    cout << lines << endl;
    vector<vector<int>> lava;
    for(int i = 0; i < lines.size(); i++) {

        vector<int> coords;
        stringstream ss(lines[i]);
        string str;
        while (getline(ss, str, ',')) {coords.push_back(stoi(str));}
        lava.push_back(coords);
    }
    for (auto v: lava) {cout << v<< endl;}
}

