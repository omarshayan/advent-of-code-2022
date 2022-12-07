#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class File {
    public:
        string name;
        int size;
        File (string s, string n) :size(stoi(s)),  name(n) {}
};

class Node {
    public:
        string name;
        Node* parent;
        vector<Node*> children;
        vector<File> contents;
        Node (Node* p, string n) : parent(p), name(n) {}

};

int traverse(Node* dir, int& sum, int& smalldirsum) {
    if (dir == NULL)
        return sum;

    int dirsum = 0;
    for (auto file : dir -> contents) {
//        cout << "\tcontent: " << file.name << ": " << file.size << endl;
        dirsum += file.size;

    }

    
    for (auto child : dir -> children) {
//        cout << "traversing " << child -> name << endl;
        dirsum += traverse(child, sum, smalldirsum);
    }
    

    sum += dirsum;
    if (dirsum <= 100000 && dirsum > 0) { 
        cout << "dir " << dir -> name << " has small sum " << dirsum << endl;
       // cout << "adding " << dirsum << endl; 
        smalldirsum += dirsum; }

    return dirsum;
}

int main() {
    ifstream reader("inputtrue.txt");
    string command_str;
    Node* pardir = NULL;
    Node* currdir = new Node(NULL, "root");
    Node* root = currdir;
    currdir -> children.push_back(new Node(root, "/"));

    // load input into n-ary tree
    while (getline(reader, command_str)) {
        vector<string> command;
        string s;
        stringstream ss(command_str);
        while (getline(ss, s, ' ')) { command.push_back(s); };

        if (command[0] == "$") {
            if (command[1] == "cd") {
                if (command[2] == "..") {
                    currdir = currdir -> parent;
                    cout << "cding to parent .. " << endl;
                }
                else {
                    int child_idx;
                    for (auto child : currdir -> children) {
                        if (child -> name == command[2]) {
                            currdir = child;
                            cout << "cding into " << currdir -> name << endl;
                        }
                    }
                }
            }    
        }
        else {
            
            if (command[0] == "dir") {
                cout << "adding dir " << command[1] << " to " << currdir -> name << endl;
                bool there = false;
                for (auto child : currdir -> children) {
                    if (child -> name == command[1]) { there = true; }
                }
                if (!there) { currdir -> children.push_back(new Node(currdir, command[1])); }
            }    
            else {
                cout << "adding file " << command[1] << " to " << currdir -> name << endl;
                File file(command[0], command[1]);
                bool there = false;
                for (auto file : currdir -> contents) {
                    if (file.name == command[1]) { there = true; }
                }
                if (!there) {currdir -> contents.push_back(file); }
            }    
        }
    }
    cout << "\n\n\n" << endl;

    // traverse tree and sum dirs with total size of at most 100000 
    int sum = 0, smalldirsum = 0;
    sum = traverse(root, sum, smalldirsum);
    cout << "sum: " << sum << endl;
    cout << "smalldirsum: " << smalldirsum << endl;

    
}

