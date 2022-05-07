#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <filesystem>
#include <fstream>
#include <string.h>
#include <vector>
#include <math.h>
#include <cmath>
#include "stdc++.h"
#include "VirtualDisk.h"
#include "Fat.h"
#include "Commands.h"

namespace fs = std::filesystem;
using namespace std;
using std::filesystem::exists;

int main() {
    cout << "MINI-FAT Project [Version 1.0]" << endl;
    VirtualDisk fatfile;
    FAT consto;
    while (1)
    {
        cout << fs::current_path() << ">"; // .root_path();
        
        string inputCommand;
        getline(cin, inputCommand);
        vector<string> Parsed_input; 
        istringstream ss(inputCommand);
        string word; // for storing each word
        while (ss >> word)
        {
            Parsed_input.push_back(word);
        }
        for (int i = 0; i < Parsed_input.size(); i++)
        {
            transform(Parsed_input[i].begin(), Parsed_input[i].end(), Parsed_input[i].begin(), ::tolower);
        }
        
        if (Parsed_input[0] == "help")
        {
            if (Parsed_input.size() == 1)
                Commands get_help;
            else
                Commands get_help(Parsed_input[1]);
        }
        else if (Parsed_input[0] == "exit")
        {
            exit(0);
            //return 0;
        }
        else if (Parsed_input[0] == "cls")
        {
            system("CLS");
        }
        else
        {
            cout << "\" " << Parsed_input[0] << " \" " << "This command isn't recognised" << endl << endl;
        }
        
    }
    return 0;
}
