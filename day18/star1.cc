#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
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
template <typename T, size_t N>
ostream& operator<<(ostream& os, const array<T, N>& v)
{
    os << "[";
    for (int i = 0; i < N; ++i) {
        os << v[i];
        if (i != N - 1)
            os << ", ";
    }
    os << "]";
    return os;
}
struct ArrayHasher {
    std::size_t operator()(const std::array<int, 3>& a) const {
        std::size_t h = 0;

        for (auto e : a) {
            h ^= std::hash<int>{}(e)  + 0x9e3779b9 + (h << 6) + (h >> 2); 
        }
        return h;
    }   
};

int main() {

    ifstream reader("inputt.txt");
    string line;
    vector<vector<int>>grid;
    vector<string> lines;
    while(getline(reader, line)) { lines.push_back(line);} 
    cout << lines << endl;
    unordered_map<array<int, 3>, bool, ArrayHasher> lava;
    vector<array<int, 3>> lavapts;
    
    for(int i = 0; i < lines.size(); i++) {

        stringstream ss(lines[i]);
        string str;
        array<int, 3> coords;
        int c = 0;
        while (getline(ss, str, ',')) {coords[c] = stoi(str); c++;}
        lava.insert({coords, true});
        lavapts.push_back(coords);
        cout << i <<endl;
    }
    int facescovered;

    for (auto pt : lavapts) {
        for (int dim=0;dim<3;dim++) {
            array<int, 3> neighb1 = pt;
            array<int, 3> neighb2 = pt;
            neighb1[dim]++;
            neighb2[dim]--;
            if (lava[neighb1]) {
                cout << pt << "\t is next to \t" << neighb1 << endl;
                facescovered++;
            }
            if (lava[neighb2]) { 
                cout << pt << "\t is next to \t" << neighb2 << endl;
                facescovered++;
            }
        }
    }

    cout << "faced covered: " << facescovered <<endl;
    cout << "num droplets: " << lines.size() <<endl;
    int res = lines.size() *6 - facescovered;
    cout << "res: " << res << endl;
}

