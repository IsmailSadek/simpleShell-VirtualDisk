#pragma once
#include <iostream>
#include "stdc++.h"
#include "DirectoryEntry.h"
using namespace std;

class Directory : public DirectoryEntry
{
    list< DirectoryEntry>DirectoryTable;
    Directory* parent;

    /*void writeDirectory() {
        int dsize = 32 * DirectoryTable.size();
        string dtb;
        string deb;
        for (int i = 0; i < dsize; i++)
            DirectoryTable.begin();
        
    }*/

public:
    //Directory()
    Directory(string name, char attribute, int firstCluster, Directory p) {
        //DirectoryEntry(name, attribute,firstCluster);
        *parent = p;
    }


};