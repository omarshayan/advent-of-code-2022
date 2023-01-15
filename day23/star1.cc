#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
using namespace std;
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};
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

void visualizeElves(unordered_map<pair<int,int>, int, pair_hash> elves) {
    int minx, miny = 10000;
    int maxx, maxy = -10000;
    for (auto elf: elves) {
        if (elf.first.first < miny) {miny = elf.first.first;}
        if (elf.first.first > maxy) {maxy = elf.first.first;}
        if (elf.first.second < minx) {minx = elf.first.second;}
        if (elf.first.second > maxx) {maxx = elf.first.second;}
    }
    for(int y = miny; y <= maxy; y++ ){
        for(int x = minx; x <= maxx; x++ ){
            if(elves[{y, x}] > 0) {cout << '#';}
            else {cout << '.';}

        }
        cout <<endl;
    }
}


int main() {

    unordered_map<pair<int,int>, int, pair_hash> elves;

    ifstream reader("inputr.txt");
    string line;
    vector<string> lines;
    while(getline(reader, line)) { lines.push_back(line);} 
    cout << lines << endl;
    
    int id = 1;
    for(int i = 0; i < lines.size(); i++) {
        for (int j = 0;j<lines[0].size(); j++) {
            if (lines[i][j] == '#') {
                elves.insert({{i, j}, id});
                id++;
            }
        }
    }


    vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // north
    int firstdir = 0;
    
    visualizeElves(elves);
    
    for (int i=0;i<10;i++) {
        for (auto dir: dirs ) {
            cout << dir.first << ", " <<dir.second <<endl;
        }

        // phase 1: consider
        unordered_map<pair<int,int>, vector<int>, pair_hash> newelves;
        for (auto elf : elves) {
            if (elf.second == 0) {continue;}
            pair<int, int> pos = elf.first;
            pair<int, int> newpos = pos;

            int checki =elves[{pos.first, pos.second + 1}] + 
                        elves[{pos.first, pos.second - 1}] +
                        elves[{pos.first + 1, pos.second}] + 
                        elves[{pos.first - 1, pos.second}] +
                        elves[{pos.first + 1, pos.second + 1}] + 
                        elves[{pos.first + 1, pos.second - 1}] + 
                        elves[{pos.first - 1, pos.second + 1}] + 
                        elves[{pos.first - 1, pos.second - 1}];
            if (checki == 0) {
                newelves[{newpos.first, newpos.second}].push_back(elf.second);
                continue;
            }

            for (auto dir : dirs) {
                int check;
                if (dir.second == 0) {
                    check = elves[{pos.first + dir.first, pos.second + 0}] + 
                            elves[{pos.first + dir.first, pos.second + 1}] + 
                            elves[{pos.first + dir.first, pos.second - 1}];
                } else if (dir.first == 0) { 
                    check = elves[{pos.first + 0, pos.second + dir.second}] + 
                            elves[{pos.first + 1, pos.second + dir.second}] + 
                            elves[{pos.first - 1, pos.second + dir.second}];
                }
                if (check == 0) {
                    newpos = {pos.first + dir.first, pos.second + dir.second};
                    break;
                }
            }
            newelves[{newpos.first, newpos.second}].push_back(elf.second);
        }

        // phase 2:  moves!
        unordered_map<pair<int,int>, int, pair_hash> newelvesfr;
        for (auto newelf: newelves) {
            pair<int, int> newpos = newelf.first;
            if (newelf.second.size() == 1) {
                newelvesfr[newpos] = newelf.second[0];
            } else {
                cout << "collision!" << endl;
                for (int elf : newelf.second) { 
                    for (auto origelf : elves) {
                        if (origelf.second == elf) {newelvesfr[origelf.first] = elf;}
                    }
                }
            }
        }
        
        // check same
        elves = newelvesfr;
        rotate(dirs.begin(), dirs.begin()+1, dirs.end());
        visualizeElves(elves);
        cout <<endl;
    }


    // find ground tiles nad shit;
    int minx = 10000, miny = 10000;
    int maxx = 0, maxy = 0;
    cout << maxx << endl;
    for (auto elf: elves) {
        cout << elf.second << ":\t" << elf.first.first << ", " << elf.first.second << endl;
        if (elf.first.first < miny) {miny = elf.first.first;}
        if (elf.first.first > maxy) {maxy = elf.first.first;}
        if (elf.first.second < minx) {minx = elf.first.second;}
        if (elf.first.second > maxx) {maxx = elf.first.second; cout<< maxx <<endl;}
    }

    cout << "bounds are\tx: " << minx << " to " << maxx << "\t and y: " << miny << " to " << maxy << endl;
    int res;
    for(int y = miny; y <= maxy; y++ ){
        for(int x = minx; x <= maxx; x++ ){
            if(elves[{y, x}] > 0) {}
            else {res++;}

        }
    }
    cout << "total: " << res << endl;
}


