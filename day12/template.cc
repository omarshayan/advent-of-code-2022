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
            os << ", ";
    }
    os << "]\n";
    return os;
}

int main() {

    ifstream reader("input.txt");
    string line;
    vector<vector<int>>grid;
    int cycle = 1;
    int x = 1; 
    deque<int> addxcounters;
    deque<int> addantbuffer;
    vector<int> signalstrengths;
    vector<string>commands;
    while(getline(reader, line)) { commands.push_back(line);} 
    cout << commands << endl;
    for(int i = 0; i < commands.size() + 2; i++) {

//
///
        vector<string> command;
        if (i < commands.size()){
            string line = commands[i];
            stringstream ss(line);
            string str;
            while (getline(ss, str, ' ')) {command.push_back(str);}
            if (command[0] != "noop"){
                int addant = stoi(command[1]);
        //        cout <<   "add " << addant << endl;
                addantbuffer.push_back(addant);
                addxcounters.push_back(0);
            }

        }
        while (addxcounters.front() ==2 ) { 
            x += addantbuffer.front();
            addantbuffer.pop_front();
            addxcounters.pop_front();
        }

        if (cycle == 20 ||
            cycle == 60 ||
            cycle == 100 ||
            cycle == 140 ||
            cycle == 180 ||
            cycle == 220) {
        cout << "cycle: " << cycle << "\t x: " << x << endl; 
            signalstrengths.push_back(cycle*x);
        }

        cycle += 1;
/*
        cout << "cycle: " << cycle << "\t x: " << x << endl; 
        cout << "counters\t";*/
        for (auto& c : addxcounters){
            c++;
       //     cout << c <<", ";
        }
    //    cout << "\taddants\t";
        for (auto c : addantbuffer){
     //       cout << c <<", ";
        }
      //  cout << endl;
    }
    int sum = 0;
    for (auto i : signalstrengths) { sum += i; }
    cout << signalstrengths << endl;
    cout << "sum: " << sum; 



    

    
}

