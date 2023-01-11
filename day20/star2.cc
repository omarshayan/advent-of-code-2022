#include <vector>
#include <list>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <deque>
using namespace std;
using iter_l = list<int64_t>::const_iterator;


int main() {

    ifstream reader("inputreal.txt");
    string line;
    vector<string> lines;
    unordered_map<int, int> nums;
    list<int64_t> n;
    list<int64_t> idxs;
    int64_t key = 811589153;
    int rounds = 10;
    while(getline(reader, line)) { lines.push_back(line);} 
    for(int64_t i = 0; i < lines.size(); i++) {
        idxs.push_back(i);
        n.push_back(stoi(lines[i]));
    }
    vector<iter_l> iters;

    auto s = n;
    int sz = n.size();
    for (auto it = n.cbegin(); it != n.cend(); it++){
        iters.push_back(it);
    }

    for (int r=0;r<rounds;r++) {
        int c = 0;
        //cout << "iters size: " << iters.size();
        for (auto x : iters) { cout << *x << ", ";} cout << endl;
        cout << endl;
        cout << endl;
        for (iter_l& it : iters){
            cout << endl;
            //for (auto x : n) { cout << x << ", ";} cout << endl;
            cout << r << ", " << c << "\t"; 
            cout << *it << " is it, " ;
            const int64_t val_i = (*it*key) % (sz-1);
            //cout << "got val, ";
            int64_t val = val_i;
            while(val < 0) val+= (sz-1);
            //cout << "inced val, ";
            c++;
            cout << "eol";
            if (val == 0) continue;

            cout << ", moving";
            auto target = it;
            if (target == n.end()) {target = n.begin();}
            ////cout << "checked target, ";
            for (int64_t i=0;i<val;i++) {
                if (++target == n.end()) {target = n.begin();}
            }
            cout << ", calced";
            //cout << "moving "  << *it << " to " << *target << endl;
            //n.erase(it);
            cout << ", erased";
            //cout << endl << endl;for (auto x : n) { cout << x << ", ";} cout << " erased " << endl;
            //n.insert(next(target), *it);
            n.splice(next(target), n, it);

            //cout << endl << endl;for (auto x : n) { cout << x << ", ";} cout << " inserted " << endl;
            cout << ", moved";

        }
    }
    cout <<"done"<<endl;
    for (auto x : n) { cout << x << ", ";} cout << endl;
    int64_t idx0 = 0;
    auto it_i = n.begin();
    while(*it_i != 0) {it_i++; idx0++;}
    cout << "0 idx :" << idx0 <<endl;
    int64_t ns = n.size() -1;
    int64_t idx1 = (1000 + idx0) % n.size();
    int64_t idx2 = (2000 + idx0) % n.size();
    int64_t idx3 = (3000 + idx0) % n.size();;
    cout << "idx1 : " << idx1 << endl;
    cout << "idx2 : " << idx2 << endl;
    cout << "idx3 : " << idx3 << endl;
    auto it1 = n.begin();
    auto it2 = n.begin();
    auto it3 = n.begin();
    advance(it1, idx1);
    advance(it2, idx2);
    advance(it3, idx3);
    cout << "idx1 : " << *it1*key << endl;
    cout << "idx2 : " << *it2*key << endl;
    cout << "idx3 : " << *it3*key << endl;
    cout << key * ( *it1 + *it2 + *it3 )<< endl;
    cout << "sum: " << ( *it1 + *it2 + *it3 ) << endl;
}

