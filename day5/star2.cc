#include <stdio.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
int main()
{
    vector<string> cratelines;    
    vector<int> crateidxs;
    vector<vector<char>> stacks (9, vector<char>());
    ifstream reader("input.txt");

    bool parsingStacks = true;

    string line;
    while(!reader.eof())
    {
        getline(reader, line);
        cout << line << endl;
        
        if (parsingStacks) {
            if (line != "") {
           cratelines.push_back(line); 
            }
        }
        else {
            int numcrates;
            int startstack;
            int endstack;
            vector<string> v;
            string s ;
            //cout << "line: " << line << endl;
            stringstream ss(line);
            while (getline(ss, s, ' ')) {
                v.push_back(s); 
                //cout << " token : " << s << endl;
            }
  /*          cout << "hi" << endl;
            cout << v[1] << endl;
            cout << v[2] << endl;
            cout << v[3] << endl;*/
            numcrates =  stoi(v[1]);
            startstack = stoi(v[3]) - 1;
            endstack = stoi(v[5]) - 1;
 //           cout << "hi1" << endl;
            vector<char> cratemoverstack;
            for (int i=0;i<numcrates;i++) {
                cratemoverstack.push_back( stacks[startstack][stacks[startstack].size()-1]);
                stacks[startstack].pop_back();
            }
            for (int i=cratemoverstack.size()-1;i>=0;i--) {
                stacks[endstack].push_back(cratemoverstack[i]);
            }
            cratemoverstack.empty();
//            cout << "hi2" << endl;
//            
            int stackidx = 1;
            for (auto stack : stacks) {
                cout << stackidx << ": ";
                for (auto c : stack ){
                    cout << c << ", ";
                }
                cout << endl;
                stackidx++;
            }
        }
        if (line == "") { 
           for (int i=1;i<=9;i++) {
               crateidxs.push_back(cratelines[cratelines.size()-1].find(to_string(i)));
           }
           cratelines.pop_back();
           reverse(cratelines.begin(), cratelines.end());
           for (auto line : cratelines) {
               for (int i=0;i<crateidxs.size();++i) {
//                   cout << "crateidx: " << crateidxs[i] << endl;
                   if (line.at(crateidxs[i]) !=  ' ') { stacks[i].push_back(line.at(crateidxs[i])); }
               }
           }
           cout << "parsingstacks false" << endl;
            parsingStacks = false; 
            for (auto stack : stacks) {
                for (auto c : stack ){
                    cout << c << ", ";
                }
                cout << endl;
            }
            for (auto stack : stacks) {
                for (auto c : stack ){
                    cout << c << ", ";
                }
                cout << endl;
            }
        }
    }
    

}
