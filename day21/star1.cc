#include <cstdio>
#include <unordered_map>
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
    for (int64_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]\n";
    return os;

}


struct Monkey {
    char operation;
    string name;
    string monk1;
    string monk2;
    string parent;
    int val;
    bool isleaf;
}; 

int64_t evalMonkey(Monkey m, unordered_map<string, Monkey> monkeymap) {
    if (m.isleaf) {
        return m.val;
    }
    int64_t op1 = evalMonkey(monkeymap[m.monk1], monkeymap);
    int64_t op2 = evalMonkey(monkeymap[m.monk2], monkeymap);
    if (op1 < 0 || op2 < 0) cout << "fucked up at " << m.name << endl;
    switch (m.operation) {
        case '/':
            if (op2 == 0) cout << "fuck" <<endl;
            return op1 / op2;
            break;
        case '*':
            return op1 * op2;
            break;
        case '+':
            return op1 + op2;
            break;
        case '-':
            return op1 - op2;
            break;
    }
    cout << "uh oh" << endl;
}

unordered_map<string, bool> getHumanPathMonkeys(unordered_map<string, Monkey> monkeymap) {
    unordered_map<string, bool> humanPathMonkeys;
    string parent;
    string child = "humn";
    while (child != "root") {
        parent = monkeymap[child].parent;
        humanPathMonkeys.insert({child, true});
        child = parent;
    }
    return humanPathMonkeys;
}

int64_t calculateHumanBranch(int64_t compval, string curr, unordered_map<string, Monkey> monkeymap, unordered_map<string, bool> humanpath) {
    string mchild;
    string hpchild;
    int64_t hpsum;
    bool ord = false;

    if(humanpath[monkeymap[curr].monk1]) {
        hpchild = monkeymap[curr].monk1;
        mchild = monkeymap[curr].monk2;
        ord = true;
    } else {
        hpchild = monkeymap[curr].monk2;
        mchild = monkeymap[curr].monk1;
    }
    int64_t msum = evalMonkey(monkeymap[mchild], monkeymap);
    switch (monkeymap[curr].operation) {
        case '/':
            hpsum = ord ? (compval * msum) : (msum / compval);
            break;
        case '*':
            hpsum = compval / msum;
            break;
        case '+':
            hpsum = compval - msum;
            break;
        case '-':
            hpsum = ord ? (compval + msum) : (msum - compval);
            break;
    }

    if (hpchild == "humn") {
        return hpsum;
    } else {
        return calculateHumanBranch(hpsum, hpchild, monkeymap, humanpath);
    }
    
}



int main() {

    ifstream reader("input.txt");
    string line;
    vector<vector<int64_t>>grid;
    vector<string> lines;
     
    unordered_map<string, Monkey> monkeys;

    while(getline(reader, line)) { lines.push_back(line);} 
    cout << lines << endl;
    cout << lines.size() << endl;
    for(int64_t i = 0; i < lines.size(); i++) {
        const int64_t l = lines[i].length();
        char* cstr = new char[l+1];
        strcpy(cstr, lines[i].c_str());
        char monke[5];
        char operand1[5];
        char operand2[5];
        char operation;
        int value = -1;
        Monkey monkey;

        sscanf(cstr, "%4s: %d", monke, &value);
        if (value == -1) {
            sscanf(cstr, "%4s: %4s %c %4s", monke, operand1, &operation, operand2);
            cout << "monkey: " << monke << "\t" << operand1  << " " << operation << " " << operand2 << endl;
            monkey.monk1 = string(operand1);
            monkey.monk2 = string(operand2);
            monkey.operation = operation;
            monkey.isleaf = false;

        } else { 
            cout << "monkey: " << monke << "\t" << value << endl;
            monkey.val = value;
            monkey.isleaf = true;
        } 
        string key = string(monke);
        monkey.name = key;
        monkeys.insert({key, monkey});
        
    }
    for (auto m : monkeys) {
        if (!m.second.isleaf) {
            monkeys[m.second.monk1].parent = string(m.first);
            monkeys[m.second.monk2].parent = string(m.first);
        }
    }
    int64_t res = evalMonkey(monkeys["root"], monkeys);
    cout << "res: " << res<<endl;
    unordered_map<string, bool> humanpath = getHumanPathMonkeys(monkeys);

    for (auto h: humanpath) { 
        cout << h.first << endl;
    }

    string mchild;
    string hpchild;
    if(humanpath[monkeys["root"].monk1]) {
        hpchild = monkeys["root"].monk1;
        mchild = monkeys["root"].monk2;
    } else {
        hpchild = monkeys["root"].monk2;
        mchild = monkeys["root"].monk1;
    }

    int64_t mbranchsum = evalMonkey(monkeys[mchild], monkeys);

    int64_t humnval = calculateHumanBranch(mbranchsum, hpchild, monkeys, humanpath);
    cout << "final: " << humnval << endl;
}

