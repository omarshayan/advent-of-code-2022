#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
#include <queue>
using namespace std;
std::ostream&
operator<<( std::ostream& dest, __int128_t value )
{
    std::ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << " ";
    }
    os << endl;
    return os;
}

int main() {

    ifstream reader("input.txt");
    string line;
    vector<string> lines;
    while(getline(reader, line)) { lines.push_back(line);} 
    cout << lines << endl;
    vector< vector<int> > snafu;
    for (auto line : lines){
        vector<int> s;
        for (int i = 0; i < line.length(); i++) {
            switch (line[i]) {
                case '=':
                    s.push_back(-2);
                    break;
                case '-':
                    s.push_back(-1);
                    break;
                case '0':
                    s.push_back(0);
                    break;
                case '1':
                    s.push_back(1);
                    break;
                case '2':
                    s.push_back(2);
                    break;
                default:
                    cout << "bad input." << endl;
                    break;
            }
        }
        snafu.push_back(s);
    }
    __int128 sum = 0;
    int maxlength=  0;
    for (auto s : snafu) {
        cout << s;
        __int128 val = 0;
        __int128 exp = 1;
        for (auto rit = s.rbegin(); rit != s.rend(); rit++) {
            val += exp * *rit;
            exp *= 5;
        }
        sum += val;
        maxlength = max(maxlength, int(s.size()));

    }
    cout << "sum : " << sum << endl;
    unordered_map<int, char> map;
    map[-2] = '=';
    map[-1] = '-';
    map[0] = '0';
    map[1] = '1';
    map[2] = '2';

    vector<__int128> snafusum;
    __int128 place = 1;
    while (sum != 0) {
        __int128 placeval = sum % (place*5);
        int digit = placeval/place;
        if (digit == 4) {
            digit = -1;
            placeval = digit*place;
        }
        if (digit == 3) {
            digit = -2;
            placeval = digit*place;
        }
        snafusum.insert(snafusum.begin(), digit);
        sum -= placeval;
        place *= 5;
    }
    for (auto d : snafusum ){ 
        cout << map[d];
    }
    cout << endl;
}


