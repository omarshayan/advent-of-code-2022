#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include <unordered_map>
#include <stdio.h>
#include <cstdio>
#include <string.h>
#include <sstream>
#include <deque>
#include <stdlib.h>
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

class Node {
    public:
        string valve;
        int score;
        Node(string v, int s): valve(v), score(s){}
};

unordered_map<string, int> memomap{};

int memoized(map<string, int> &flowrates, map<string,map<string,int>> &dists, string curr, map<string, bool> opened, int minleft, bool elephant);

int run(map<string, int> &flowrates, map<string,map<string,int>> &dists, string curr, map<string, bool> opened, int minleft, bool elephant){
    if (minleft <=0) {
       /* 
        cout << "at " <<curr << " with " << minleft << " with opened: ";
        for (auto o : opened){
            cout << o.first << ": " << o.second << "\t";
        }
        cout << endl;
       */ 
        if (elephant) {  return run(flowrates, dists, "AA", opened, 26, false);}
        else { return 0;}
    }
    opened[curr] = true;
    int score = (minleft)*flowrates[curr];
    int best = score;
    int kek = 0;
    //cout << minleft <<endl;
    for (auto adj : dists[curr]) {
        if(opened[adj.first]){continue;}
        if(minleft ==26 && elephant == true){cout << "on iter " << kek << "\t out of " << dists[curr].size() << endl; kek++;}
        //if(minleft ==30){cout << "on iter " << kek << "\t out of " << dists[curr].size() << endl; kek++;}
        //cout << "opening " << v << endl;
        best = max(best, score + memoized(flowrates, dists, adj.first, opened, minleft - adj.second - 1, elephant));
        //    return score + run(flowrates, dists, curr, opened, minleft - 1);
        //cout << "visiting " << adj.first << " ,dist " << adj.second << endl;
    }
    if (elephant) {return max(best, run(flowrates, dists, "AA", opened, 26, false));}
    else  {return best;}
    //return best;
}

int memoized(map<string, int> &flowrates, map<string,map<string,int>> &dists, string curr, map<string, bool> opened, int minleft, bool elephant) {
    stringstream memokey{};
    for (auto v : opened){memokey << v.second;}
    memokey << curr << minleft << elephant;
    if (memomap.find(memokey.str()) != memomap.end()) {
     //   cout <<"did a useflu thing" << endl;
        return memomap[memokey.str()];
    }
    int res = run(flowrates, dists, curr, opened, minleft, elephant);
    memomap[memokey.str()] = res;
    return res;
}

int main() {
    auto start = chrono::system_clock::now();
    ifstream reader("inputr.txt");
    string line;
    vector<string> lines;
    map<string, vector<string>> tunnelmap;
    map<string, int> flowrates;
    while(getline(reader, line)) { lines.push_back(line);} 
    for(int i = 0; i < lines.size(); i++) {
        char valve[3];
        int flowrate;
        char tunnels[500];
        vector<string> tunnelsv;
        cout << "line: " << lines[i] << endl;
        if (lines[i].find("tunnels") != string::npos) {
            sscanf(lines[i].c_str(), "Valve %s has flow rate=%d; tunnels lead to valves %[^\n]", valve, &flowrate, tunnels);
            string tunnelss(tunnels);
            stringstream ss(tunnelss);
            string str;
            while (getline(ss, str, ',')) {
                if (str.length() > 2) {str = str.substr(1,2);}
               tunnelsv.push_back(str);
            }
        } else {
            sscanf(lines[i].c_str(), "Valve %s has flow rate=%d; tunnel leads to valve %[^\n]", valve, &flowrate, tunnels);
            string tunnelss(tunnels);
            if (tunnelss.find(',') == string::npos) { cout << "Coudln't find comma in " << valve << endl;tunnelsv.push_back(tunnelss); }
        }
            cout << "valve: " << valve <<  ", array: " << tunnels << endl;;
            flowrates.insert({string(valve), flowrate});
            tunnelmap.insert({valve, tunnelsv});
    }

    vector<Node> frontier;
    vector<Node> next;
    map<string, map<string, int>> dists;
    map<string, bool> visited;
    for (auto n : tunnelmap){
        cout << n.first << endl;
        cout << n.second << endl;
        map<string, int> m;
        m.insert({n.first, 0});
        dists[n.first] = map<string, int>();
    }

    for (auto n: tunnelmap){
        for (auto n : tunnelmap){
            visited[n.first] = false; 
        }
        string v = n.first;
        frontier.clear();
        visited[v] = true;
        
        int level = 1;

        frontier.push_back(Node(v, 0));
        while(frontier.size() > 0){
            for (Node node : frontier) {
                cout << "exploring " << tunnelmap[node.valve];
                for (string neighbor : tunnelmap[node.valve]){
                    int score = node.score;
                    if (!visited[neighbor]) { 
                        visited[neighbor] = true;
                        next.push_back(Node(neighbor, score));
                        if (flowrates[neighbor] > 0) {
                            dists[v].insert({neighbor, level});
                        }
                        cout << v << "is " << level << " away from " << neighbor << endl;
                    }
                }
            }
            frontier = next;
            next.clear();
            level++;
        }
    }
    map<string, bool> o;
    for (auto n : tunnelmap) {
        o.insert({n.first, false});
    }
    for (auto n : dists ){
        cout << n.first << ": \t"<< endl;
        for (auto adj : n.second) {
            cout <<  adj.first << " ,dist " << adj.second << ", ";
        }
        cout << endl;
    }
   // int res = memoized(flowrates, dists, "AA", o, 30, false);
    int res = memoized(flowrates, dists, "AA", o, 26, true);
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "time :" << elapsed_seconds.count() << endl;
    cout << "res: " << res <<endl;
}

