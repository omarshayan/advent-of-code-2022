#include <map>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
int main() {
    ifstream reader("input.txt");
    string line;

    map<tuple<char,char>, char> conversions;
    bool parsingConversions = false;
    while(getline(reader, line)) {
        if (line == "") {
           parsingConversions = true; 
        }

        if (parsingConversions) {
            stringstream ss;
            string s;
            vector<string> conversionline;
            while (getline(ss, s, ' ')) { conversionline.push_back(s); }
            const char* pair = conversionline[0].c_str();
            tuple <char, char> pair_tup = make_tuple(pair[0], pair[1]);
            char result = conversionline[0].c_str()[0];
            conversions.insert({pair_tup, result});
            cout << get<0>(pair_tup) << get<1>(pair_tup) << ": " << result << endl;
        }
        else {
            string startstring = line;
        }
    }
    for(auto it = conversions.cbegin(); it != conversions.cend(); ++it) {
        cout << get<0>(it -> first) << get<1>(it -> first) << ": " << it -> second << endl;
    }
}
