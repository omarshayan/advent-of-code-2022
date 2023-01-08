#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
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
            os;
    }
    os << "]";
    return os;
}

int findHighestRock(vector<vector<int>> rockstack) {
    for (int i=rockstack.size()-1;i>=0;i--) {
        if (accumulate(rockstack[i].begin(), rockstack[i].end(), 0) > 0) { return i +1; }
    }
    return 0; 
}

bool checkCollision(vector<vector<int>> rockstack, vector<vector<int>> shape, int x, int y) {
    if (x < 0 || x + shape[0].size() > 7) return true;
    if (y < 0 || y + shape.size() > rockstack.size()) return true;

    for (int i=0;i<shape.size();i++) {
        for (int j=0;j<shape[0].size();j++) {
            if (rockstack[y+i][x+j] == 1 && shape[i][j] == 1) return true;
        }
    }
    return false;
}

vector<int> getRockContour(vector<vector<int>> rockstack) {
    vector<int> contour;
    for (int x=0;x<7;x++) {
        for (int i=rockstack.size()-1;i>=0;i--) {
            if (rockstack[i][x] == 1) { contour.push_back(i); break; }
        }
    }
    return contour;
}
int main() {


    vector<vector<vector<int>>> shapes { {{1, 1, 1,1}}, 
                                         {{0, 1, 0}, {1, 1, 1}, {0, 1, 0}},
                                         {{1, 1, 1}, {0, 0, 1}, {0, 0, 1}},
                                         {{1}, {1}, {1}, {1}},
                                         {{1, 1}, {1, 1}} };

    ifstream reader("input.txt");
    string line;
    vector<vector<int>>grid;
    string jetstream;
    while(getline(reader, line)) { jetstream = line; } 
    cout << jetstream << endl;

    vector<vector<int>> rockstack; 
    vector<int> emptyrow({0, 0, 0, 0, 0, 0, 0});


    int shapeidx = 0;
   
    bool collision = false;
    int jetidx = 0;
    int lastmax = 0;
    
    map<pair<vector<int>,int>, bool> seenContours;
    map<pair<int, int>, bool> cycles;
    bool cyclefound = false;
    bool cyclehit = false;
    
    pair<int, int> icyclestate;
    pair<int, int> cyclestate;
    long irocks;
    long iheight;
    long heightgained;
    long N = 1000000000000;

    for (long r=0;r<1000000000000;r++) {
        if (cyclefound && !cyclehit && make_pair(shapeidx, jetidx) == icyclestate) {
            cyclehit = true;
            cout << "hit cycle. rocks fallen: " << r << "\t max height: " << findHighestRock(rockstack) << endl;
            cyclestate = make_pair(shapeidx, jetidx);

            long cyclelength = r - irocks;
            long cycleheight = findHighestRock(rockstack) - iheight; 
            cout << "cycle length is " << cyclelength<< endl;

            long cycles = (1000000000000 - irocks)/cyclelength;
            cout << "cycles consumed: " << cycles<< endl;
            long remrocks = 1000000000000 - cycles*cyclelength - irocks;
            cout << "remaining: " << remrocks << endl;
            heightgained = cycles*cycleheight - cycleheight;
            cout << "gained " << heightgained << endl;
            
            r = N - remrocks;
            cout << "r is now " << r << endl;
        }
        if (r >= N) break;

        if (!cyclefound && cycles[make_pair(shapeidx, jetidx)]) { cout << "found a cycle after " << r << " rocks fallen!\t" << endl;
            cyclefound = true;
            irocks = r;
            iheight = findHighestRock(rockstack);

            icyclestate = make_pair(shapeidx, jetidx);
        }

        cycles[make_pair(shapeidx, jetidx)] = true;


        //for (int v=rockstack.size()-1;v>=0;v--) { cout << rockstack[v] <<endl;}
        // fill top of stack
       // cout << "highest rock at: " << findHighestRock(rockstack) << endl;
        while (rockstack.size() < shapes[shapeidx].size() + 3 + findHighestRock(rockstack)) {
            rockstack.push_back(emptyrow);
        }
        //cout << "highest rock at: " << findHighestRock(rockstack) << endl;
        int rockx = 2;
        int rocky = findHighestRock(rockstack) + 3;
        collision = false;

        while (!collision) {
            // move the rock
            //cout << "curr rock at " << rockx << ", " << rocky <<endl;
            //cout << jetstream[jetidx] << endl;
            switch(jetstream[jetidx]) {
                case '<':
                    if (!checkCollision(rockstack, shapes[shapeidx], rockx-1, rocky)) rockx--;
             //       cout << "move rock left to " << rockx << "\t " << checkCollision(rockstack, shapes[shapeidx], rockx, rocky) << endl;
                    break;
                case '>':
                    if (!checkCollision(rockstack, shapes[shapeidx], rockx+1, rocky)) rockx++;
              //      cout << "move rock right to " << rockx <<  "\t " << checkCollision(rockstack, shapes[shapeidx], rockx, rocky)<<endl;
                    break;
                default:
                    return 0;
            }

            //lower the rock
            if (!checkCollision(rockstack, shapes[shapeidx], rockx, rocky-1)) 
            {
                rocky--;
            } else {
                collision = true;
            }

            jetidx = (jetidx+1) % jetstream.length();
        }
        // place rock
        for (int i=0;i<shapes[shapeidx].size();i++) {
            for (int j=0;j<shapes[shapeidx][0].size();j++) {
                if (shapes[shapeidx][i][j] == 1) rockstack[rocky+i][rockx+j] = shapes[shapeidx][i][j];
            }
        }
        shapeidx = (shapeidx+1) % shapes.size();
        //cout << "-------------------------------------------------" <<endl;
        
    }
    cout << "rokc heihgtt at " << findHighestRock(rockstack);

    long res = heightgained + findHighestRock(rockstack);

    cout << "res: " << res << endl;
}

