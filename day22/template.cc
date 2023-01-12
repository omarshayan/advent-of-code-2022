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
    string line;
    vector<string> lines;
    while(getline(reader, line)) { lines.push_back(line);} 
    cout << lines << endl;
    for(int i = 0; i < lines.size(); i++) {
    }
}

