#pragma once
#include <iostream>

using namespace std;

class Commands
{
private:
    string items[13] = { "cd", "cls", "dir", "exit", "copy", "del", "help", "md", "rd", "rename", "type", "import", "export" };
    string values[13] = { "Displays the name of or changes the current directory.", "Clears the screen.",  "List the contents of directory.",
                        "Quits the SHELL.",  "Copies one or more files to another location.",  "Deletes one or more files.",
                        "Provides Help information for commands.",  "Creates a directory.",  "Removes a directory.",
                         "Renames a file or files.",  "Displays the contents of a text file.",  "Import text file(s) from your computer.",
                            "Export text file(s) to your computer.", };
    void help() {
        for (int i = 0; i < 13; i++) {
            cout << items[i] << '\t' << values[i] << endl;
        }
    }
    void specific_help(string help_arg) {
        int arg_index = 0;
        int counter = 0;
        for (int i = 0; i < 13; i++) {
            if (items[i] == help_arg) {
                arg_index = i;
                counter += 1;
            }
        }
        if (counter > 0)
            cout << items[arg_index] << '\t' << values[arg_index] << endl;
        else {
            cout << "This command \"" << help_arg << "\" isn't recognised." << endl;
        }
    }
public:
    Commands() {
        help();
    }
    Commands(string help_arg) {
        specific_help(help_arg);
    }
};