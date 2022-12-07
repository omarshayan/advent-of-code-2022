#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;
int main(){
    ifstream reader("input.txt");
    stringstream buffer;
    buffer << reader.rdbuf();
    string str = buffer.str();

    int markerlen = 14;
    for (int i = 0 ; i < str.length(); i++) {
        string marker = str.substr(i, markerlen);
        sort(marker.begin(), marker.end());
        bool unique = true;
        for (int j = 0; j < markerlen - 1; j++) {
            if (marker[j] == marker[j+1]) {
                unique = false;
            }
        }
        if (unique) { cout << i + markerlen << endl; return 0;}
    }
    return 0;
}
