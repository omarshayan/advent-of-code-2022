#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

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

    ifstream reader("inputr.txt");
    string line;
    vector<vector<int>>grid;

    stringstream ss(line);
    vector<string> dirs;
    vector<int> amts;
    string str;
    
    while(getline(reader, line)) {
//        cout << line << endl;
        stringstream ss(line);
        getline(ss, str, ' '); 
        dirs.push_back(str);
        getline(ss, str, ' '); 
        amts.push_back(stoi(str));
    }

    map<tuple<int, int>, int> tailvisited;

    map<int, tuple<int, int>> nodepositions;

     
    for (int node = 0; node < 10; node++) {
        nodepositions[node] = make_tuple(0,0);
    }

    for (int i = 0; i < amts.size(); i++) {
        
        for (int j = 0; j < amts[i]; j++ ) {
            int prevx = get<0>(nodepositions[0]); 
            int prevy = get<1>(nodepositions[0]); 
            if (dirs[i] == "L") { get<0>(nodepositions[0]) -= 1; }
            if (dirs[i] == "R") { get<0>(nodepositions[0]) += 1; }
            if (dirs[i] == "U") { get<1>(nodepositions[0]) += 1; }
            if (dirs[i] == "D") { get<1>(nodepositions[0]) -= 1; }
            cout << "step: " << dirs[i] << " " << amts[i] << "\t" << endl;
            for (int node = 1; node < 10; node++) {
                int headx = get<0>(nodepositions[node - 1]);
                int heady = get<1>(nodepositions[node - 1]);
                int tailx = get<0>(nodepositions[node]);
                int taily = get<1>(nodepositions[node]);
                
                if (abs(heady - taily) > 1 && headx == tailx){
                    taily = prevy; 
                } 

                if (abs(headx - tailx) > 1 && heady == taily){
                    tailx = prevx; 
                } 
                if (abs(headx - tailx) > 1 && abs(heady - taily) > 1) {
                    tailx = prevx;
                    taily = prevy;
                }
                if (abs(heady - taily) > 1 && abs(headx - tailx) == 1) {
                    taily = prevy;
                    tailx = headx;
                }
                if (abs(headx - tailx) > 1 && abs(heady - taily) == 1) {
                    tailx = prevx;
                    taily = heady;
                }
                prevx = get<0>(nodepositions[node]);
                prevy = get<1>(nodepositions[node]);
                get<0>(nodepositions[node]) = tailx;
                get<1>(nodepositions[node]) = taily;
                

            }
            cout <<endl;
            cout << "\t" << "head : " << get<0>(nodepositions[0]) << ", " << get<1>(nodepositions[0]) << endl;
            cout << "\t" << "tail : " << get<0>(nodepositions[9]) << ", " << get<1>(nodepositions[9]) << endl;
            tailvisited[nodepositions[9]]++;
        }
    }
    for (auto&& item : tailvisited)
        cout << get<0>(item.first) << ", " << get<0>(item.first)  << ": " << item.second << '\n';

    
    cout << "res: " << tailvisited.size() << endl;

    

    
}

