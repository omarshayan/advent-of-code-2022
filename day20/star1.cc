#include <vector>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
using namespace std;
template <typename t> void move(std::vector<t>& v, size_t oldIndex, size_t newIndex)
{
    if (oldIndex > newIndex)
        std::rotate(v.rend() - oldIndex - 1, v.rend() - oldIndex, v.rend() - newIndex);
    else        
        std::rotate(v.begin() + oldIndex, v.begin() + oldIndex + 1, v.begin() + newIndex + 1);
}

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
    vector<string> lines;
    unordered_map<int, int> nums;
    vector<int> n;
    vector<int> idxs;
    while(getline(reader, line)) { lines.push_back(line);} 
    for(int i = 0; i < lines.size(); i++) {
        nums.insert({i, stoi(lines[i])});
        idxs.push_back(i);
        n.push_back(stoi(lines[i]));
    }
    vector<int> s = n;
    for (int i=0;i<nums.size();i++) {
        cout << n << endl;
        auto id = find(idxs.begin(), idxs.end(), i);
        int idx_i = id - idxs.begin();
        int val = n[idx_i];
        int idx_new = (idx_i + val + 2*(nums.size() - 1)) % (nums.size() - 1);
        //cout << "move " << val << " from " << idx_i << " to " << idx_new <<endl;
        move(n, idx_i, idx_new);
        move(idxs, idx_i, idx_new);
        if (val < 0 && idx_new == 0) {
            move(n, idx_new, n.size() - 1);
            move(idxs, idx_new, n.size() - 1);
        } 
        else if (val > 0 && idx_new == n.size()-1) {
            move(n, n.size() - 1, 0);
            move(idxs, n.size() - 1, 0);
        }
        cout << i;
    }
    cout << "final vec: " << n << endl;
    //cout << "final idx: " << idxs << endl;
    auto idx0f = find(n.begin(), n.end(), 0);
    int idx0 = idx0f - n.begin();
    cout << "0 idx :" << idx0 <<endl;
    int ns = n.size() -1;
    int idx1 = (1000 + idx0) % n.size();
    int idx2 = (2000 + idx0) % n.size();
    int idx3 = (3000 + idx0) % n.size();;
    cout << "idx1 : " << idx1 << endl;
    cout << "idx2 : " << idx2 << endl;
    cout << "idx3 : " << idx3 << endl;
    cout << "idx1 : " << n[idx1] << endl;
    cout << "idx2 : " << n[idx2] << endl;
    cout << "idx3 : " << n[idx3] << endl;
    cout << n[idx1] + n[idx2] + n[idx3] << endl;
}

