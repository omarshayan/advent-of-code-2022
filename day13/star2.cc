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
            os << "\n";
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
        for(int i=0;i<min(buffer1.size(), buffer2.size());i++){
           cout<< "i: " << i << endl; 
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

    ifstream reader("inputr2.txt");
    string line;
    vector<vector<int>>grid;
    vector<string> buffers;
    while(getline(reader, line)) { if(line!="") {buffers.push_back(line);}}
    int correct = 0;
    cout << buffers << endl;
    cout << buffers.size() << endl;
    for(int i = 0; i < buffers.size(); i++) {
        bool swapped = false;
        for(int j = 0; j < buffers.size() - 1; j++) {
            
            cout << "j: " << j << endl;
            cout << buffers.size() << endl;
            cout << i << endl;
            cout << "buf1: " << buffers[j] << endl;
            cout << "buf2: " << buffers[j+1] << endl;
            string temp; 
            if (compareBuffers(buffers[j], buffers[j+1]) != 1){
                temp = buffers[j];
                buffers[j] = buffers[j+1];
                buffers[j+1] = temp;
                swapped = true;
            }
            cout << "--------------------------------------------" << endl;
        }        
        if (!swapped) { break;}
    }
    cout << "SORTED: " << endl << buffers << endl;
    int code1;
    int code2;
    for (int i =0;i<buffers.size();i++){
        if (buffers[i] == "[[2]]") { code1 = i + 1;}
        if (buffers[i] == "[[6]]") { code2 = i + 1;}
    }
    cout << "sol: " << code1*code2<< endl;
}

