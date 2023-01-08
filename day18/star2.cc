#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
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
vector<array<int, 3>> getneighbors(array<int, 3> pt, array<int, 3> maxc, array<int, 3> minc ) {
    vector<array<int, 3>> neighbs;
    for (int dim=0;dim<3;dim++) {
        array<int, 3> neighb1 = pt;
        array<int, 3> neighb2 = pt;
        neighb1[dim]++;
        neighb2[dim]--;
        if( neighb1[dim] <= maxc[dim] + 1 ) neighbs.push_back(neighb1);
        if( neighb2[dim] >= minc[dim] - 1) neighbs.push_back(neighb2);
    }
    return neighbs;
}
    

int floodfill(array<int, 3> curr, array<int, 3> maxc, array<int, 3> minc, unordered_map<array<int, 3>, bool, ArrayHasher> lava, unordered_map<array<int, 3>, bool, ArrayHasher>& visited) {
    vector<array<int, 3>> neighbs = getneighbors(curr, maxc, minc);
    int sum = 0;
    for (auto n : neighbs) { 
        if (lava[n]) {sum++; cout << "foudn edge" <<endl;}
        if (!visited[n]) {
            cout << "visiting " << n[0] << ", "<< n[1] << ", "<< n[2] << endl;
            visited[n] = true;
            if(!lava[n]) sum += floodfill(n, maxc, minc, lava, visited);
        }
    }
    return sum;    

}

int main() {

    ifstream reader("inputt.txt");
    string line;
    vector<vector<int>>grid;
    vector<string> lines;
    while(getline(reader, line)) { lines.push_back(line);} 
    cout << lines << endl;
    unordered_map<array<int, 3>, bool, ArrayHasher> lava;
    unordered_map<array<int, 3>, bool, ArrayHasher> visited;
    vector<array<int, 3>> lavapts;
    array< int, 3> minc;
    array< int, 3> maxc;
    maxc.fill(0);
    minc.fill(99999);

    for(int i = 0; i < lines.size(); i++) {

        stringstream ss(lines[i]);
        string str;
        array<int, 3> coords;
        int c = 0;
        while (getline(ss, str, ',')) {coords[c] = stoi(str); c++;}
        for (int dim=0;dim<3;dim++) {
            maxc[dim] = max(maxc[dim], coords[dim]);
            minc[dim] = min(minc[dim], coords[dim]);
        }

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
    array<int, 3> start({1,1,1});
    int surf = floodfill(start, maxc, minc, lava, visited);
    cout << "surf: " << surf <<endl;
}
