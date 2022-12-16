#include <vector>
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

    
    while(getline(reader, line)) {
//        cout << line << endl;

        stringstream ss(line);
        vector<int> gridline;
        string str;
        for (int i = 0; i < line.size(); i++) {
            gridline.push_back(line[i] - '0');
        }
        grid.push_back(gridline);
    }

    
    vector<int> v {1, 2, 3};
    cout << "vec: " << v << endl;

    

    
}

