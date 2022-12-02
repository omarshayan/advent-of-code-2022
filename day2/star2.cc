#include <bits/stdc++.h>
#include <iostream>
#include <iterator>
#include <fstream>
#include <numeric>
#include <vector>
#include <string>
#include <cstring>
#include <map>


using namespace std;

int convertRPSCode(string code)
{
   map<string, int> map; 
   map.insert(pair<string, int>("A", 0));
   map.insert(pair<string, int>("B", 1));
   map.insert(pair<string, int>("C", 2));
   map.insert(pair<string, int>("X", 2));
   map.insert(pair<string, int>("Y", 0));
   map.insert(pair<string, int>("Z", 1));

  return map[code];
}

int main()
{
    vector<int> opponent_moves;
    vector<int> my_moves;
    int elf_idx = 0;
    // read input    
    ifstream reader("input.txt");
    while(!reader.eof())
    {
        string rps_round;
        getline(reader, rps_round);
        cout << rps_round << endl;
        if (rps_round != "") {
            int opp_move = convertRPSCode(rps_round.substr(0,1));
            opponent_moves.push_back(opp_move);
            my_moves.push_back((opp_move + convertRPSCode(rps_round.substr(2,1))) % 3);
        }
    }
    
        cout << "okay"  << endl;
    int score = 0;
    for(int i=0;i<my_moves.size();i++)
    {
        cout << my_moves[i] << " vs " << opponent_moves[i];
        score += my_moves[i] + 1;
        if (my_moves[i] == (opponent_moves[i] + 1) % 3) { score += 6; cout << " win!"; }
        if (opponent_moves[i] == (my_moves[i] + 1) % 3) { score += 0; }
        if (my_moves[i] == opponent_moves[i]) { score += 3; cout << " draw.";}
        cout << endl;
    }

    cout << "final score: " << score << endl;
    return 0;
}
