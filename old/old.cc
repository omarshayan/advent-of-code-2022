#include <map>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <set>

using namespace std;

void inserchar(char start , char end, map<tuple<char,char>, char> charmap, map<char, int>& charcount, int i){
    if(i==40){ return;}
    i++;
   char middle = charmap[make_tuple(start, end)];
   cout << "found a " << middle << "from " << start << ", " << end << endl;
   charcount[middle]++;
   inserchar(middle, end, charmap, charcount, i);
   inserchar(start, middle, charmap, charcount, i);
}

int main() {
    ifstream reader("myinput.txt");
    string line;
    string startstr;
    int startlen;

            cout << "hi" << endl;
    map<tuple<char,char>, char> conversions;
    bool parsingConversions = false;
    while(getline(reader, line)) {
            cout << "hi" << endl;
        if (line == "") {
           parsingConversions = true; 
        }

        if (parsingConversions && line != "") {

            stringstream ss(line);
            string s;
            vector<string> conversionline;
            while (getline(ss, s, ' ')) { conversionline.push_back(s); }
            const char* pair = conversionline[0].c_str();
            tuple <char, char> pair_tup = make_tuple(pair[0], pair[1]);
            char result = conversionline[2].c_str()[0];
            conversions.insert({pair_tup, result});
        }
        else if (!parsingConversions){
            startstr = line;
            startlen = line.length();
        }
    }
    cout << "start string: " << startstr << endl;
    char startseq[startlen];
    strcpy(startseq, startstr.c_str());
    for(auto it = conversions.cbegin(); it != conversions.cend(); ++it) {
        cout << get<0>(it -> first) << get<1>(it -> first) << ": " << it -> second << endl;
    }
    
    
    set<char> charset;
    for (auto c : conversions) {
       charset.insert(c.second); 
    }
    
    map<char, int> charcount;
    for (auto c : charset) {
        charcount.insert({c, 0});
        cout << "adding " << c << " to map" << endl;
    }

    for (int i = 0; i<startlen - 1; i++) {
        charcount[startseq[i]]++;
        inserchar(startseq[i], startseq[i+1],  conversions, charcount, 0);
    }
    charcount[startseq[startlen-1]]++;
    for (auto c : charcount) {
        cout << c.first << ": " << c.second << endl;
    }
}
