#include <vector>
#include <map>
#include <ranges>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <cstdio>
#include <deque>
#include <thread>
using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << "";
    }
    os << "]\n";
    return os;
}

int main() {

    ifstream reader("inputr.txt");
    int keyrow = 2000000;
   int maxrow = 4000000;
   // int maxrow = 20;
    string line;
    vector<vector<int>>grid;
    vector<string> lines;
    vector<set<int>> idxs; 
    set<int> keybeacs;
    while(getline(reader, line)) { lines.push_back(line);} 
    cout << lines << endl;
    vector<int> sensx;
    vector<int> sensy;
    vector<int> beacx;
    vector<int> beacy;
    for(int i = 0; i < lines.size(); i++) {
        int sx, sy, bx, by;
        sscanf(lines[i].c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &sx, &sy, &bx, &by);
        sensx.push_back(sx);
        sensy.push_back(sy);
        beacx.push_back(bx);
        beacy.push_back(by);
       // if (beacy== keyrow) {keybeacs.insert(beacx);}
    }

    //for each sensor, find the collection of points right outside of its range
    //now we have a long list of coordinates. loop through them and find the one that occurs 4x
    map<pair<int,int>, int> edgepts;
    vector<pair<int,int>> candidates;
    for (int i=0;i<sensx.size();i++){
        cout << "i: " <<i << endl;
        int dist = abs(sensx[i] - beacx[i]) + abs(sensy[i]-beacy[i]) + 1;
        cout << "dist = " << dist <<endl;
            for (int j=0;j<dist;j++){
                int x1 = sensx[i] - dist + j;
                int y1 = sensy[i] + j;
                edgepts[{y1, x1}]++;
                if (edgepts[{y1, x1}] == 2) {candidates.push_back({y1,x1});}
                int x2 = sensx[i] + j;
                int y2 = sensy[i] + dist - j;
                edgepts[{y2, x2}]++;
                if (edgepts[{y2, x2}] == 2) {candidates.push_back({y2,x2});}
                int x3 = sensx[i] + dist - j;
                int y3 = sensy[i] - j;
                edgepts[{y3, x3}]++;
                if (edgepts[{y3, x3}] == 2) {candidates.push_back({y3,x3});}
                int x4 = sensx[i] - j;
                int y4 = sensy[i] - dist + j;
                edgepts[{y4, x4}]++;
                if (edgepts[{y4, x4}] == 2) {candidates.push_back({y4,x4});}
            }
    }
    cout << "num edgepts: " << edgepts.size() << endl;
    cout << "num cands: " << candidates.size() << endl; int c = 0;
    /*
    for (auto pt : edgepts){
        cout << "edge pt: \t x: " << pt.first.first << ",\ty: " << pt.first.second << "\t has been seen " << pt.second << endl;
        if (pt.second > 1) {
            candidates.push_back(pt.first);
        }
    }
    cout  << "end?"<< endl;
    /*
    for (auto pt : edgepts){
        cout << "C: " << c << endl;
        //cout << "edge pt: \t x: " << pt.first << ",\ty: " << pt.second << endl;
        if (count(edgepts.begin(), edgepts.end(), pt) > 1 &&
            pt.first >= 0 && pt.first <= maxrow &&
            pt.second >= 0 && pt.second <= maxrow) {
        if (count(edgepts.begin(), edgepts.end(), pt) > 1){
            cout << "Found candidate! \tx: " << pt.first << " \ty: " << pt.second <<endl; 
            candidates.push_back(pt);
            //return 0;
        }
        c++;
    }*/
    for (auto pt : candidates) {
        bool good = true;
        for (int i=0;i<sensx.size();i++){
            int range = abs(sensx[i] - beacx[i]) + abs(sensy[i]-beacy[i]);
            int dist = abs(sensx[i] - pt.second) + abs(sensy[i]-pt.first);
            if (dist <= range) {good = false;}
        }
        if (good &&
            pt.first >= 0 && pt.first <= maxrow &&
            pt.second >= 0 && pt.second <= maxrow){
            cout << "Found the point! \ty: " << pt.first << " \tx: " << pt.second <<endl; 
        }
    }
    /*
    vector<vector<char>> plot(maxrow+1, vector<char>(maxrow +1, '.'));

    for (auto pt : edgepts) {
        cout << "pt: " << pt.first.first << ", " << pt.first.second << ":\t" << pt.second <<endl;
        if (pt.first.first >= 0 && pt.first.first <= 20 &&
            pt.first.second >= 0 && pt.first.second <= 20) {
            plot[pt.first.first][pt.first.second] = '#';
        }
    }
    for (int i=0;i<sensx.size();i++) {
        if (sensy[i] >= 0 && sensy[i] <= 20 &&
            sensx[i] >= 0 && sensx[i] <= 20) {
            plot[sensy[i]][sensx[i]] = 'S';
        }
        if (beacy[i] >= 0 && beacy[i] <= 20 &&
            beacx[i] >= 0 && beacx[i] <= 20) {
            plot[beacy[i]][beacx[i]] = 'B';
        }
    }
    for (auto v : plot ) {
        cout << v;
    }
    */

}

