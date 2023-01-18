#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
#include <queue>
using namespace std;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << " ";
    }
    os << "]\n";
    return os;
}
void visBlizz(vector<vector<vector<bool>>> blizzies, int width, int height, pair<int, int> pos){

    vector<char> chars = {'^', '>','v', '<', };
    for(int i = 0; i < height; i++) {
        for (int c = 0; c < width; c++) {
            char ch = '.';
            int count = 0;
            for(int j = 0; j < 4; j++) {
                if (blizzies[j][i][c]) {
                    ch = chars[j];
                    count++;
                }
            }
            if (count > 1) {ch = 'X';}
            if (pos.first == i && pos.second == c) {ch = 'E';}
            cout << ch;
        }
        cout << endl;
    }
    cout << endl;
}


vector<vector<vector<bool>>> moveBlizzies(vector<vector<vector<bool>>> blizzies) {
    vector<vector<bool>>blizziesN = blizzies[0];
    vector<vector<bool>>blizziesE = blizzies[1];
    vector<vector<bool>>blizziesS = blizzies[2];
    vector<vector<bool>>blizziesW = blizzies[3];

    rotate(blizziesN.begin()+1, blizziesN.begin()+2, blizziesN.end()-1);
    rotate(blizziesS.begin()+1, blizziesS.end()-2, blizziesS.end()-1);

    for(vector<bool>& blizz : blizziesE) {
        rotate(blizz.begin()+1, blizz.end()-2, blizz.end()-1);
    }
    for(vector<bool>& blizz : blizziesW) {
        rotate(blizz.begin()+1, blizz.begin()+2, blizz.end()-1);
    }
    vector<vector<vector<bool>>> newblizzies;
    newblizzies.push_back(blizziesN);
    newblizzies.push_back(blizziesE);
    newblizzies.push_back(blizziesS);
    newblizzies.push_back(blizziesW);
    return newblizzies;
}

vector<pair<int, int>> getNeighbs(vector<vector<vector<bool>>> blizzies, pair<int, 
                int> pos, vector<pair<int, int>> dirs, int width, int height) {
    vector<pair<int, int>> neighbs;
    bool occ = false;
    for (auto blizzdir : blizzies) {
        if (blizzdir[pos.first][pos.second]){
            occ = true;
        }
    }
    if(!occ) {neighbs.push_back(pos);}
    if (pos == make_pair(0, 1)) {neighbs.push_back({1, 1}); return neighbs;}
    if (pos == make_pair(height-2, width-2)) {neighbs.push_back({height-1, width-2}); return neighbs;}
    for (auto dir: dirs) {
        bool blizz = false;
        int y = pos.first + dir.first;
        int x = pos.second + dir.second;
        if (y < 1 || y > height - 2) {continue;}
        if (x < 1 || x > width - 2) {continue;}
        for (auto blizzdir : blizzies) {
            if (blizzdir[y][x]){
                blizz = true;
            }
        }
        if(!blizz) {neighbs.push_back({y, x});}
    }
    return neighbs;
}

int bfs(vector<vector<vector<bool>>> blizzies, unordered_map<string, int>& visited,
         pair<int, int> pos, vector<pair<int, int>> dirs, int width, int height, int steps) {
     cout << "on step " << steps << "\t\t"; 
     //int timestate = steps % ((width-2) * (height-2));
     int timestate = steps % 600;
     string id = to_string(pos.first) +","+ to_string(pos.second) +","+ to_string(timestate);
     visited[id] = steps;
     if (pos == make_pair(height-1, width-2)) {
          if (steps < 21) {
          cout << "done in " << steps << " steps. path: " <<endl;

          }
         return steps;
     }

     blizzies = moveBlizzies(blizzies);
     vector<pair<int, int>> neighbs = getNeighbs(blizzies, pos, dirs, width, height);

     visBlizz(blizzies, width, height, pos);
     cout << "neighbs of " << pos.first << ", " << pos.second << " are\t";
     for ( auto neighb : neighbs) { 
         cout << neighb.first << ", " << neighb.second << " | ";
     }
     cout << endl;
     int best = 10000;
     steps = steps+1;
     for (auto neighb : neighbs) {
         cout << "exploring " << neighb.first << ", " << neighb.second << endl;
         int timestaten = (steps) % ((width-2) * (height-2));
         cout << "hi1" <<endl;
         string idn = to_string(neighb.first) +","+ to_string(neighb.second) +","+ to_string(timestaten);
         cout << "hi2" <<endl;
         if(visited[idn] ==0 || visited[idn] >= steps){
             cout << "hi3" <<endl;
             cout<< visited.size() << endl;

             int res = bfs(blizzies, visited, neighb, dirs, width, height, steps);
             cout << "hi4" <<endl;
             if (res < best) { best  =res;}

         }
         cout << "hi5" <<endl;
     }
     return best;

}

int main() {

    ifstream reader("input.txt");
    string line;
    vector<vector<int>>grid;
    vector<string> lines;
    while(getline(reader, line)) { lines.push_back(line);} 
    cout << lines << endl;

    int height = lines.size();
    int width = lines[0].size();

    vector<vector<vector<bool>>> blizzies;
    vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; //null north east south west
    vector<char> chars = {'^', '>', 'v', '<'};

    vector<vector<bool>> blizziesN(height, vector<bool>(width, 0));
    vector<vector<bool>> blizziesE(height, vector<bool>(width, 0));
    vector<vector<bool>> blizziesS(height, vector<bool>(width, 0));
    vector<vector<bool>> blizziesW(height, vector<bool>(width, 0));

    for(int i = 1; i < lines.size()-1; i++) {
        for (int c = 1; c < lines[0].size()-1; c++) {
            switch(lines[i][c]) {
                case '^':
                    blizziesN[i][c] = 1;
                    break;
                case '>':
                    blizziesE[i][c] = 1;
                    break;
                case 'v':
                    blizziesS[i][c] = 1;
                    break;
                case '<':
                    blizziesW[i][c] = 1;
                    break;
                default:
                    break;
            }
        }

    }
    cout << "HI" << endl;
    blizzies.push_back(blizziesN);
    blizzies.push_back(blizziesE);
    blizzies.push_back(blizziesS);
    blizzies.push_back(blizziesW);


    cout << "HI" << endl;
    int steps = 0;
    bool done = false;
    pair<int, int> start = make_pair(0, 1);
     visBlizz(blizzies, width, height, start);
    cout << "HI" << endl;
    unordered_map<string, int> visited;
    vector<pair<int, int>> path;
    path.push_back(start);
  // int res = bfs(blizzies, visited,start, dirs, width, height, steps);
    cout << "width: " <<width << "\t height: " << height << endl;
   // cout << "res; " << res << endl;

    vector<pair<int, int>> frontier;
    frontier.push_back(start);
    vector<int> results;
    
    while (frontier.size() > 0) {
        vector<pair<int, int>> next;
         blizzies = moveBlizzies(blizzies);
         cout << frontier.size() << endl;

        for (auto  pos: frontier){

            // cout << "on step " << steps << "\t\t"; 
             int timestate = steps % (600);
     //int timestate = steps % ((width-2) * (height-2));
             //string id = to_string(pos.first) +","+ to_string(pos.second) +","+ to_string(timestate);
             if (pos == make_pair(height-1, width-2)) {
                  cout << "done in " << steps << " steps. path: " <<endl;
                  return 0;
                  results.push_back(steps);
             }

             vector<pair<int, int>> neighbs = getNeighbs(blizzies, pos, dirs, width, height);

             for (auto neighb : neighbs) {
                 int timestaten = (steps) % ((width-2) * (height-2));
                 string idn = to_string(neighb.first) +","+ to_string(neighb.second) +","+ to_string(timestaten);
                 if(visited[idn] == 0){
                     visited[idn] = steps;
                     next.push_back(neighb);

                 }
             }
        }
        frontier = next;
        steps++;
    }
    cout << "final results:\t" << results << endl;
    cout << "minimum steps: " << *min_element(results.begin(), results.end()) << endl;
}

