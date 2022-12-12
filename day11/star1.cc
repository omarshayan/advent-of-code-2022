#include <vector>
#include <cstdio>
#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
#include <functional>
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
    deque<int> addxcounters;
    deque<int> addantbuffer;
    vector<int> signalstrengths;
    vector<string>commands;
    vector<deque<int>> monkeyinventories;
    vector<int> testints;
    vector<function<int(int, string)>> operations;
    vector<tuple<int,int>> throwopts;
    vector<string> operands;
    int monkeyidx;
    while(getline(reader, line)) { 
       
        stringstream ss(line);
        string str;
        if (line.find("Monkey") != string::npos){
            sscanf(line.c_str(), "Monkey %d:", &monkeyidx);
            cout << monkeyidx << endl;
        }
        else if (line.find("Starting items") != string::npos){
            deque<int> inventory;
            getline(ss, str, ' ');
            getline(ss, str, ' ');
            getline(ss, str, ' ');
            getline(ss, str, ' ');
            while (getline(ss,str, ' ')) { 
                cout<<str << endl; 
                inventory.push_back(stoi(str));
            }
            monkeyinventories.push_back(inventory);
            
        }
        else if (line.find("Operation") != string::npos){
            
            char operationtype;
            char operandstr[10];
            int operand;
            cout << line << endl;
            sscanf(line.c_str(), "  Operation: new = old %c %s", &operationtype, operandstr);
            getline(ss,str, ' ');
            cout << operandstr << endl;
            operands.push_back(operandstr);

            if (operationtype == '*') {
                auto func = [](int i, string operand){ if(!isdigit(operand[0])){ return i*i; } else return i*stoi(operand);};
                operations.push_back(func);
            }
            if (operationtype == '+') {
                auto func = [](int i, string operand){ if(!isdigit(operand[0])){ return i+i; } else return i+stoi(operand);};
                operations.push_back(func);
            }
        }
        else if (line.find("Test") != string::npos){
            int dividand;
            sscanf(line.c_str(), "  Test: divisible by %d", &dividand);
            testints.push_back(dividand);
            getline(reader,line);
            int trueopt;
            sscanf(line.c_str(), "    If true: throw to monkey %d", &trueopt);
            getline(reader,line);
            int falseopt;
            sscanf(line.c_str(), "    If false: throw to monkey %d", &falseopt);
            throwopts.push_back(make_tuple(trueopt,falseopt));
        }
    } 

    int monkeybusiness;
    cout << operations.size() << endl;

    vector<int> inspectcounts(8); 
    for (int i=0;i<20;i++){
        for (int m=0;m<=monkeyidx;m++){
            cout << "=========Monkey " << m << endl;
            while (monkeyinventories[m].size() > 0){
            int item = monkeyinventories[m].front();
            cout << "Monkey inspects an item with a worry level of " << item << endl;
                int a = 5;
                operations[m](5, operands[m]);
                item = operations[m](item, operands[m])/3;
                cout << "Worry level is multiplied by " << operands[m] << " to " << item << endl;
                if (item % testints[m] == 0){
                    monkeyinventories[get<0>(throwopts[m])].push_back(item);
                } else {
                    cout << "Current worry level is not divisible by " << testints[m] << endl;
                    monkeyinventories[get<1>(throwopts[m])].push_back(item);
                    cout << "Item with worry level " << item<< "is thrown to monkey" << get<1>(throwopts[m]) << endl;

                }
                monkeyinventories[m].pop_front();
                inspectcounts[m]++;
            }
        }
    for (auto inv : monkeyinventories ) {
        for (auto i : inv){
            cout << i <<", ";
        }
        cout << endl;
    }
    }

    cout << inspectcounts << endl;
    
}

