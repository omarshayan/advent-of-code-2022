#include <bits/stdc++.h>
#include <iostream>
#include <iterator>
#include <fstream>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

int main()
{
    cout << "hello!" << endl;
    vector<vector<int>> calorie_counts(1);
    int elf_idx = 0;
    // read input    
    ifstream reader("input.txt");
    while(!reader.eof())
    {
        string calories;
        getline(reader, calories);
        if (calories.compare("") == 0)
        {
            calorie_counts.push_back(vector<int>());
            elf_idx++;
        }
        else 
        {
            calorie_counts[elf_idx].push_back(stoi(calories)); 
        }

    }

    int max_cals = 0;
    int total_cals;
    for (int elf_idx=0; elf_idx<calorie_counts.size(); elf_idx++)
    {
        total_cals = accumulate(calorie_counts[elf_idx].begin(), calorie_counts[elf_idx].end(), 0);
        if (total_cals > max_cals) { max_cals = total_cals; }
    }
    cout << max_cals << endl;
    // istream_iterator<int> start(reader), end;
    // vector<int> calorie_counts(start, end);

    // copy(calorie_counts.begin(), calorie_counts.end(),
    //         ostream_iterator<int>(cout, "\n"));
    return 0;


}
