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

    vector<int> elf_cals(calorie_counts.size());
    int total_cals;

    for (int elf_idx=0; elf_idx<calorie_counts.size(); elf_idx++)
    {
        total_cals = accumulate(calorie_counts[elf_idx].begin(), calorie_counts[elf_idx].end(), 0);
        elf_cals[elf_idx] = total_cals;
        cout << total_cals << endl;
    }
    sort(elf_cals.begin(), elf_cals.end(), greater<int>());
    cout << "results: " << endl;
    cout << elf_cals[0] << endl;
    cout << elf_cals[1] << endl;
    cout << elf_cals[2] << endl;
    cout << elf_cals[0] + elf_cals[1] + elf_cals[2] << endl;
    return 0;


}
