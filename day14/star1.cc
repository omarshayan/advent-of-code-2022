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

    ifstream reader("input.txt");
    string line;
    vector<string> lines;
    vector<int> y;
    vector<int> x;
    while(getline(reader, line)) { 
            stringtream ss(line);
            string str;
            while (getline(ss, str, ' ')) {
                // might need to push these back in separate lines?
                if (str !="->"){
                    x.push_back(stoi(str.substr(0, 3)));
                    y.push_back(stoi(str.substr(4, str.length()-4)));
                }
            }
    }
    cout <<"HI"<< endl;
    int minx = *min_element(x.begin(), x.end());
    int width = *max_element(x.begin(), x.end()) - minx;
    int miny = *min_element(y.begin(), y.end());
    int height = *max_element(y.begin(), y.end()) - miny;
    cout <<"HI"<< endl;
    vector<vector<char>> grid(height, vector<char>(width, 'o'));
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    for(int i = 0; i < x.size()-1; i++) {
        if (x[i] == x[i+1]) {
            for(int yr=y[i];yr<=y[i+1];yr++) {
                cout << yr << ", " << x[i]<< endl;;
                grid[yr - miny][x[i] - minx] = '#';
            }
        } else if (y[i] == y[i+1]) {
            for(int xr=x[i];xr<=x[i+1];xr++) {
                cout << y[i] << ", " << xr << endl;;
                grid[y[i]- miny][xr - minx] = '#';
            }
        }
    }
    cout <<"HI"<< endl;
    for (auto v : grid){
        cout << v << endl;
    }
}

