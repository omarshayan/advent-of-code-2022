#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <queue>
#include <tuple>
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


struct Node {
    tuple<int, int> coords;
    char elevation; 
    Node(tuple<int,int> c, char e) : coords(c), elevation(e) {}
    Node() {}
};

int main() {

    string elevations = "abcdefghijklmnopqrstuvwxyz";
    ifstream reader("inputr.txt");
    string line;
    vector<vector<char>>grid;
    int linenum = 0;
    Node start;
    Node end;
    vector<Node> frontier;
    while(getline(reader, line)) {

        stringstream ss(line);
        vector<char> gridline;
        string str;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == 'S') {
                start = Node(make_tuple(linenum, i), 'a');
                line[i] = 'a';
                gridline.push_back('a');
                frontier.push_back(start);
            } else if (line[i] == 'E') {
                end = Node(make_tuple(linenum, i), 'z');
                gridline.push_back('z');
            }
            else {
                gridline.push_back(line[i]);
                if(line[i] == 'a') {frontier.push_back(Node(make_tuple(linenum, i), 'a'));}
            }
        }
        cout << gridline << endl;
        grid.push_back(gridline);
        linenum++;
    }

    int rows = grid.size();
    int cols = grid[0].size();
    cout << "rows : " << rows << "\n cols: " << cols << endl;
    int n = cols*rows;
    map<tuple<int,int>, int> visited;
    for (int i=0;i<rows;i++) {
        for (int j=0;j<cols;j++) {
        visited[make_tuple(i, j)] = -1;
        }
    }
    for (Node n : frontier) {
        visited[n.coords] = 0;
    }
    cout << "startcoords: " << get<0>(start.coords) << ", " << get<1>(start.coords) << endl;

    int level = 0;
    while (frontier.size() > 0) {
        vector<Node> next;

        for (Node node : frontier){
            int y = get<0>(node.coords);
            int x = get<1>(node.coords);
            
            if  (grid[y][x] == 'y') { cout << "hit a " << grid[y][x]<< endl;}
            if  (grid[y][x] == 'q') { cout << "hit a " << grid[y][x]<< endl;}
            if  (grid[y][x] == 'l') { 
                cout << "hit a " << grid[y][x]<< endl;
                cout << "at coords " << y << ", " << x << " at elevation " << grid[y][x] << " which is " << (int)elevations.find(grid[y][x]) << ", level " << level << endl;
            }
            //cout << "at coords " << y << ", " << x << " at elevation " << grid[y][x] << " which is " << (int)elevations.find(grid[y][x]) << ", level " << level << endl;
            if (y < rows-1 &&  
                visited[make_tuple(y+1, x)] < 0 &&
                (int)elevations.find(grid[y+1][x]) - (int)elevations.find(grid[y][x]) <= 1)
            {
                tuple<int, int> coords = make_tuple(y+1, x);
                next.push_back(Node(coords, grid[y+1][x]));
                visited[coords] = level+1;
            }

            if (x < cols-1 && 
                visited[make_tuple(y, x+1)] < 0 && 
                (int)elevations.find(grid[y][x+1]) - (int)elevations.find(grid[y][x]) <= 1) 
            {
                tuple<int, int> coords = make_tuple(y, x+1);
                next.push_back(Node(coords, grid[y][x+1]));
                visited[coords] = level+1;
            }
            
            if (y > 0 && 
                visited[make_tuple(y-1, x)] < 0 && 
                (int)elevations.find(grid[y-1][x]) - (int)elevations.find(grid[y][x]) <= 1) 
            {
                tuple<int, int> coords = make_tuple(y-1, x);
                next.push_back(Node(coords, grid[y-1][x]));
                visited[coords] = level+1;

            }

            if (x > 0 && 
                visited[make_tuple(y, x-1)] < 0 && 
                (int)elevations.find(grid[y][x-1]) - (int)elevations.find(grid[y][x]) <= 1) 
            {
                tuple<int, int> coords = make_tuple(y, x-1);
                next.push_back(Node(coords, grid[y][x-1]));
                visited[coords] = level+1;
            }
        }
        frontier = next;
        level++;
    }

    cout << "endcoords: " << get<0>(end.coords) << ", " << get<1>(end.coords) << endl;
    cout << "total: " << visited[end.coords] << endl;

    

    
}

