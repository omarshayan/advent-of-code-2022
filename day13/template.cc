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
    vector<string> buffers;
    while(getline(reader, line)) { buffers.push_back(line);} 
    cout << buffers << endl;
    for(int i = 0; i < buffers.size(); i++) {

        vector<string> buffer;
        if (i < buffers.size()){
            string line = buffers[i];
            stringstream ss(line);
            string str;
            while (getline(ss, str, ' ')) {buffers.push_back(str);}

        }
    }
}

