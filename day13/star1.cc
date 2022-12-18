#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <deque>
using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << "|";
    }
    os << "\n";
    return os;
}

vector<string> parseList(string buf){
        vector<string> buffer;
        if (buf[0] != '[') {
            buffer.push_back(buf);
            return buffer;
        }
        buf = buf.substr(1, buf.length()-2);
        stringstream ss(buf);
        string str;
        string temp = "";
        int bracketcount = 0;
        while (getline(ss, str, ',')) {
            bracketcount += count(str.begin(), str.end(), '[');
            //cout << "brackets deep: " << bracketcount << endl;
            if ( bracketcount > 0) {
                temp = temp + str + ",";
            } 
            bracketcount -= count(str.begin(), str.end(), ']');
            //cout << "brackets deep: " << bracketcount << endl;
            if (bracketcount < 1) {
                if (temp.length() > 0) {
                    buffer.push_back(temp.substr(0, temp.length()-1));   
                    temp = "";
                } else {

                buffer.push_back(str);
                }
            }
        }
        return buffer;
}

int compareBuffers(string buf1, string buf2){


        vector<string> buffer1 = parseList(buf1);
        vector<string> buffer2 = parseList(buf2);;
        cout << "buf1: " << buffer1 << endl;
        cout << "buf2: " << buffer2 << endl;
        for(int i=0;i<min(buffer1.size(), buffer2.size());i++){
           cout<< "i: " << i << endl; 
                cout << "buf1 first: " << buffer1[i][0] << endl;
                cout << "buf2 first: " << buffer2[i][0] << endl;
               if (buffer1[i][0] != '[' && buffer2[i][0] != '['){
                    if (stoi(buffer1[i]) < stoi(buffer2[i])){
                        return 1;
                    } else if (stoi(buffer1[i]) > stoi(buffer2[i])){
                        return 0;
                    }
               } else {
                    int sub = compareBuffers(buffer1[i], buffer2[i]);
                    if (sub > -1) {return sub;}
               }

        }
        if (buffer1.size() < buffer2.size()) { return 1; }
        else if (buffer1.size() > buffer2.size()) { return 0; }
        else return -1;

}

int main() {

    ifstream reader("inputr.txt");
    string line;
    vector<vector<int>>grid;
    vector<string> buffers;
    while(getline(reader, line)) { if(line!="") {buffers.push_back(line);}}
    cout << buffers << endl;
    int correct = 0;
    cout << buffers.size() << endl;
    for(int i = 0; i < buffers.size(); i+=2) {

        cout << "buf1: " << buffers[i] << endl;
        cout << "buf2: " << buffers[i+1] << endl;
        
        if (compareBuffers(buffers[i], buffers[i+1]) == 1) {correct += (i/2+1); cout << (i/2+1) << " correct!" << endl;} else { cout << (i/2+1) << " false." << endl;}
        cout << "--------------------------------------------" << endl;
            
    }
    cout << "correct: " << correct << endl;
}

