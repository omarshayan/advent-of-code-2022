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

struct Node {
    tuple<int, int> coords;
    char elevation; 
    int id;
    Node(tuple<int,int> c, char e, int id) : coords(c), elevation(e), id(id) {}
    Node() {}
};

int main() {

    char elevations[] = "abcdefghijklmnopqrstuvwxyz";
    ifstream reader("inputr.txt");
    string line;
    vector<vector<int>>grid;
    int linenum = 0;
    Node start;
    Node end;
    while(getline(reader, line)) {
//        cout << line << endl;

        stringstream ss(line);
        vector<int> gridline;
        string str;
        for (int i = 0; i < line.size(); i++) {
            gridline.push_back(line[i] - '0');
            if (line[i] == 'S') {
                start = Node(make_tuple(linenum, i), 'S', 0);
            }
            if (line[i] == 'E') {
                end = Node(make_tuple(linenum, i), 'E', -1);
            }
        }
        grid.push_back(gridline);
        linenum++;
    }

    int rows = grid.size();
    int cols = grid[0].size();
    int n = cols*rows;
    queue<Node> q;
    map<tuple<int,int>, bool> visited;
    for (int i=0;i<rows;i++) {
        for (int j=0;j<cols;j++) {
        visited[make_tuple(i, j)] = false;
        }
    }
    vector<Node> prev;
    int idcounter;

    while (q.size() > 0) {
        Node node = q.front();
        int y = get<0>(node.coords);
        int x = get<1>(node.coords);
        cout << strchr(elevations, grid[y][x]);
        q.pop();
        if (y < rows &&  
            !visited[make_tuple(y+1, x)] &&
            abs(strchr(elevations, grid[y+1][x]) - strchr(elevations, grid[y+1][x])) <= 1)
        {
            
            q.push(Node(make_tuple(y+1, x), grid[y+1][x]);
        }
        if (!visited[make_tuple(y, x+1)] && x < cols) {

        }
        if (!visited[make_tuple(y-1, x)] && y > 0) {

        }
        if (!visited[make_tuple(y, x-1)] && x > 0) {

        }
    }


    cout << "total: " <<  endl;

    

    
}

