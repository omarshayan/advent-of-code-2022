#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstdio>
#include <string.h>
#include <sstream>
#include <deque>
#include <stdlib.h>
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
    vector<string> lines;
    while(getline(reader, line)) { lines.push_back(line);} 
    cout << lines << endl;
    for(int i = 0; i < lines.size(); i++) {
        char valve[2];
        int flowrate;
        char* tunnels;
        sscanf("Valve %s has flow rate=%d; tunnels lead to valves %s", valve, flowrate, tunnels);
        cout << "Valve " << valve << " has flow rate " << flowrate << " " << tunnels << endl;
    }
}

