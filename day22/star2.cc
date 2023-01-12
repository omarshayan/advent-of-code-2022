#include <vector>
#include <unordered_map>
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

pair<int, int> addpairs(pair<int, int> p1, pair<int, int> p2) {
    return make_pair(p1.first + p2.first, p2.second + p1.second);
}

inline void wrappos(pair<int, int>& newpos, int height, int width) {
        if (newpos.first == -1) newpos.first = height-1;
        if (newpos.first == height) newpos.first = 0;
        if (newpos.second == -1) newpos.second = width-1;
        if (newpos.second == width) newpos.second = 0;
}

int main() {

    int sz = 50;
    ifstream reader("inputr.txt");
    string line;
    vector<string> lines;
    vector<vector<char>> grid;
    unordered_map<int, pair<int, int>> faceoffsets;

    while(getline(reader, line)) { lines.push_back(line);} 
    int width = 0;
    int height = lines.size()-2;
    int startx = height;
    for(int i = 0; i < lines.size()-2; i++) {
        if (lines[i].length() > width) { width = lines[i].length(); }
    }
    cout << " width: " << width << "\t height: " << height << endl;
    for(int i = 0; i < lines.size()-2; i++) {
        vector<char> row;
        for(int c = 0; c < lines[i].length(); c++) {
            if (i ==0 && lines[i][c] == '.') {startx = min(startx, c);}
            switch (lines[i][c]) {
                case ' ':
                    row.push_back('0');
                    break;
                case '.':
                    row.push_back('.');
                    break;
                case '#':
                    row.push_back('#');
                    break;
                default: 
                    row.push_back('0');
                    break;
            }
        }
        if (
        for(int c = lines[i].length(); c < width; c++) { row.push_back('0');}
        grid.push_back(row);
    }

    string instructions = lines[lines.size()-1];
    vector<int> steps;
    vector<char> turns;
    int insidx;
    int i =0;
    while (i<instructions.length()) {
        if (isdigit(instructions[i])) {
            steps.push_back(stoi(instructions.substr(i, instructions.length()-i)));
            while(isdigit(instructions[i])) {i++;}
        } else {
            turns.push_back(instructions[i]);
            i++;
        }
    }
    cout << steps;
    cout << turns;
    //for ( auto I  : grid ) {cout << I << endl;}

    vector<pair<int, int>> dirs = {  {-1, 0}, {0, 1},{1, 0}, {0, -1} }; // up right down left
    pair<int, int> pos = {0, startx};
    int facing = 1;


    for (int i=0;i<steps.size();i++) {
    //for (int i=0;i<10;i++) {
        cout << "on instruction " << i << ",\t facing " << facing <<  "\t" << steps[i] << " " << turns[i] <<endl;
        for (int j=0;j<steps[i];j++) {
            cout << "\tstep " << j <<"\tpos: " << pos.first <<", " << pos.second << "\ton a " << grid[pos.first][pos.second] << endl;
            pair<int, int> newpos = addpairs(pos, dirs[facing]);
            wrappos(newpos, height, width);

            if (grid[newpos.first][newpos.second] == '#') { 
                break;
            }
            while (grid[newpos.first][newpos.second] == '0') {
                newpos = addpairs(newpos, dirs[facing]);
                wrappos(newpos, height, width);
                //cout << "\t\twrapping "<<"\tpos: " << newpos.first <<", " << newpos.second << endl;
            }
            if (grid[newpos.first][newpos.second] == '#') { 
                break;
            }
            pos = newpos;
        }
        if(i == steps.size()-1) {break;}
        facing = (turns[i] == 'R') ? (facing+1) : (facing);
        facing = (turns[i] == 'L') ? (facing-1) : (facing);
        facing = (facing + 4) % 4;
    }
    cout << "final pos: " << pos.first+1 <<", " << pos.second+1 << endl;
    cout << "final facing: " << facing<< endl;
    facing = (facing +3) % 4;
    cout << "answer: " << 1000 * (pos.first+1) + 4 * (1+pos.second) + facing << endl;
}

