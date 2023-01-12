#include <cstdio>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
using namespace std;

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

int max_rem(int minleft, unordered_map<string, int> bots, unordered_map<string, int> resources) {
    int rem_geo = 0;
    for (int i = minleft; i > 0; i--) {
        rem_geo += minleft * bots["geo"];
        bots["geo"]++;
    }
    return resources["geo"] + rem_geo;
}
void add_resources(int minleft, unordered_map<string, int> bots, unordered_map<string, int> &resources) {
    for (auto bot : bots) {
        resources[bot.first] += bot.second;
    }
}
string getstate(int minleft, unordered_map<string, int> bots, unordered_map<string, int> resources) {
    string res;
    res += minleft;
    for (auto b: bots) {
        res += b.second;
    }
    for (auto r: resources) {
        res += r.second;
    }
    return res;
}

struct Params {
    vector<int> orebot_orecosts;
    vector<int> claybot_orecosts;
    vector<int> obsibot_orecosts;
    vector<int> obsibot_claycosts;
    vector<int> geobot_orecosts;
    vector<int> geobot_obsicosts;
    vector<int> maxcosts;
};

int dfs(int bp, int minleft, unordered_map<string, int> bots, unordered_map<string, int> resources, Params params, int &bestsofar, unordered_map<string, bool>& states, bool prevskipped) {
    string state = getstate(minleft, bots, resources);
    if (states[state]) {return 0;}
    states[state] = true;
    if (max_rem(minleft, bots, resources) <= bestsofar) {return 0;}
    
    if (minleft == 0) {
        return resources["geo"];
    }

    if (resources["ore"] >= params.geobot_orecosts[bp] && resources["obsi"] >= params.geobot_obsicosts[bp]) {
        unordered_map<string, int> resources_new = resources; unordered_map<string, int> bots_new = bots;
          //  cout << "building geobot with " << minleft << " min left." <<endl;
        resources_new["ore"] -= params.geobot_orecosts[bp];
        resources_new["obsi"] -= params.geobot_obsicosts[bp];
        add_resources(minleft, bots_new, resources_new);
        bots_new["geo"]++;
        return dfs(bp, minleft-1, bots_new, resources_new, params, bestsofar, states, false);
    }

    int best= 0;
    if (resources["ore"] >= params.obsibot_orecosts[bp] && resources["clay"] >= params.obsibot_claycosts[bp]) {
        if (!(prevskipped && resources["ore"]-bots["ore"] >= params.obsibot_orecosts[bp] && resources["clay"]-bots["clay"] >= params.obsibot_claycosts[bp])) {
           //cout << "building obsibot with " << minleft << " min left." <<endl;
             unordered_map<string, int>resources_new = resources; unordered_map<string, int>bots_new = bots;
            resources_new["ore"] -= params.obsibot_orecosts[bp];
            resources_new["clay"] -= params.obsibot_claycosts[bp];
            add_resources(minleft, bots_new, resources_new);
            bots_new["obsi"]++;
            best = max(best, dfs(bp, minleft - 1, bots_new, resources_new, params, bestsofar, states, false));
        }
    }
    if (resources["ore"] >= params.claybot_orecosts[bp]) {
        if (!(prevskipped && resources["ore"]-bots["ore"] >= params.claybot_orecosts[bp])) {
            unordered_map<string, int> resources_new = resources; unordered_map<string, int> bots_new = bots;
            resources_new["ore"] -= params.claybot_orecosts[bp];
            add_resources(minleft, bots_new, resources_new);
            bots_new["clay"]++;
            best = max(best, dfs(bp, minleft - 1, bots_new, resources_new, params, bestsofar, states, false));
        }
    }
    if (bots["ore"] < 5 &&resources["ore"] >= params.orebot_orecosts[bp]) {
        if (!(prevskipped && resources["ore"]-bots["ore"] >= params.orebot_orecosts[bp])) {
            unordered_map<string, int> resources_new = resources; unordered_map<string, int> bots_new = bots;
            resources_new["ore"] -= params.orebot_orecosts[bp];
            add_resources(minleft, bots_new, resources_new);
            bots_new["ore"]++;
            best = max(best, dfs(bp, minleft - 1, bots_new, resources_new, params, bestsofar, states, false));
        }
    }
    add_resources(minleft, bots, resources);

    return max(best, dfs(bp, minleft-1, bots, resources, params, bestsofar, states, true));
}


int main() {

    ifstream reader("input.txt");
    string line;
    vector<vector<int>>grid;
    vector<string> lines;
      
    Params params;

    while(getline(reader, line)) { lines.push_back(line);} 
    cout << lines << endl;
    for(int i = 0; i < lines.size(); i++) {

        vector<string> buffer;
        int idx;
        int orebot_orecost;
        int claybot_orecost;
        int obsibot_orecost;
        int obsibot_claycost;
        int geobot_orecost;
        int geobot_obsicost;
        sscanf(lines[i].c_str(), "Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.",
                &idx, &orebot_orecost, &claybot_orecost, &obsibot_orecost, &obsibot_claycost, &geobot_orecost, &geobot_obsicost);
        cout << "orebot cost: " << orebot_orecost << "\t goebotobsi: " << geobot_obsicost <<endl;
        params.orebot_orecosts.push_back(orebot_orecost);
        params.claybot_orecosts.push_back(claybot_orecost);
        params.obsibot_orecosts.push_back(obsibot_orecost);
        params.obsibot_claycosts.push_back(obsibot_claycost);
        params.geobot_orecosts.push_back(geobot_orecost);
        params.geobot_obsicosts.push_back(geobot_obsicost);         
    }

    vector<string> recs({"ore", "clay", "obsi", "geo"});
    unordered_map<string, int> bots;
    unordered_map<string, int> resources;
    unordered_map<string, bool> states;
    vector<int> scores;
    for(int i =0; i < lines.size(); i++) {
        states.clear();
        for (auto r : recs) {
            bots[r] = 0;
            resources[r] = 0;
        }
        bots["ore"]++;

        int bestsofar = 0; 
        int res = dfs(i, 24, bots, resources, params, bestsofar, states, false);
        cout << "bp " << i+1 << " has max of " << res << endl;
        scores.push_back(res);
    }
    int qual = 0;
    for (int i=1;i<=lines.size();i++) {
        qual+= scores[i-1]*i;
    }
    cout << "final qual score: " << qual<<endl;

}

