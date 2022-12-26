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
            os << " ";
    }
    os << "]\n";
    return os;
}

int main() {

    ifstream reader("inputr.txt");
    string line;
    vector<string> lines;
    vector<int> y;
    vector<int> x;
    vector<int> newlines;
    while(getline(reader, line)) { 
            stringstream ss(line);
            string str;
            while (getline(ss, str, ' ')) {
                // might need to push these back in separate lines?
                if (str !="->"){
                    x.push_back(stoi(str.substr(0, 3)));
                    y.push_back(stoi(str.substr(4, str.length()-4)));
                }
            }
            newlines.push_back(x.size()-1);
    }
    int minx = *min_element(x.begin(), x.end()) - 250;
    int width = *max_element(x.begin(), x.end()) - minx;
    int miny = *min_element(y.begin(), y.end());
    int height = *max_element(y.begin(), y.end()) - miny;
    vector<vector<char>> grid(*max_element(y.begin(), y.end()) + 2, vector<char>(width + 500, '.'));
    for(int i = 0; i < x.size()-1; i++) {
        if (count(newlines.begin(), newlines.end(), i) > 0) {continue;}
        else if (x[i] == x[i+1]) {
            int start = min(y[i],y[i+1]);
            int end = max(y[i],y[i+1]);
            for(int yr=start;yr<=end;yr++) {
                grid[yr][x[i] - minx] = '#';
            }
        }  else if (y[i] == y[i+1]) {
            int start = min(x[i],x[i+1]);
            int end = max(x[i],x[i+1]);
            for(int xr=start;xr<=end;xr++) {
                grid[y[i]][xr - minx] = '#';
            }
        }
    }

    grid.push_back(vector<char>(width + 500, '#'));
    for (auto v : grid){
        cout << v << endl;
    }

    int sourcex = 500 - minx;
    int sourcey = 0;
    int currx = sourcex;
    int curry = sourcey;
    int counter = 0;
    while(true) {
        cout << "curr in : " << curry << ", " << currx  << endl;
        if (grid[curry+1][currx] == 'F'){
            cout << "we made it to the bottom! counter: " << counter +1 << endl;
            return 0;
        }
        if (grid[curry+1][currx] == '.'){
            cout << "down" << endl;
            curry++;
        }
        else if (grid[curry+1][currx-1] == '.'){
            cout << "down left" << endl;
            curry++;
            currx--;
        }
        else if (grid[curry+1][currx+1] == '.'){
            cout << "down right" << endl;
            curry++;
            currx++;
        }
        else {
            cout << "PLACED!" << endl;
            if (curry == sourcey && currx == sourcex) { cout << "done. counter: " << counter << endl; return 0;}
            grid[curry][currx] = 'o';
            counter++;
            currx = sourcex;
            curry = sourcey;
            for (auto v : grid){
                cout << v << endl;
            }
        }
    }
}

