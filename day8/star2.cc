#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

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

    for (auto row : grid ){
        for (auto val : row){
            
        }
    }
    int vistrees = 2*grid.size() + 2*grid[0].size() - 4;
    int max = 0;
    cout << "edge: " << vistrees << endl;
    for (int i = 1; i < grid.size() - 1; i++){
        for (int j = 1; j < grid[0].size() - 1; j++){
            int scoreright= j;
            int scoreleft = grid[0].size()-1 -j;
            int scoreup   = i;
            int scoredown = grid.size()-1 - i;
            int score = 0;

            bool visright = true;
            bool visleft = true;
            bool visup= true;
            bool visdown = true;
            for (int x = 0; x < j; x++){
                if (grid[i][x] >= grid[i][j]) { cout << "rightblock: " << i << ", " << x << endl; scoreright = (j-x); visright = false; }
            }
            for (int x = j + 1; x < grid[0].size(); x++){
                if (grid[i][x] >= grid[i][j]) { scoreleft = (x-j);visleft = false; break; }
                if(!visleft) {break;}
            }
            for (int y = 0; y < i; y++){
                if (grid[y][j] >= grid[i][j]) { scoreup = (i-y);visup = false; }
            }
            for (int y = i + 1; y < grid.size(); y++){
                if (grid[y][j] >= grid[i][j]) { scoredown = (y-i);visdown = false; break; }
                if(!visdown) {break;}
            }
            if ((((visright || visup) || visdown) || visleft)) {cout << "visible tree!" << endl; vistrees ++; }
            score = scoreright*scoreleft*scoreup*scoredown;
            if (score > max ){
                max = score;
            cout << i << ", " << j<< endl;    
               cout<< "right" << scoreright<<  endl;
               cout<< "left "<< scoreleft << endl; 
               cout<< "up   "<< scoreup   << endl;                 
               cout<< "down "<< scoredown << endl; 
            }
        }

    }

    cout << "total: " << vistrees << endl;

    cout << "max: " << max << endl;
    

    
}

