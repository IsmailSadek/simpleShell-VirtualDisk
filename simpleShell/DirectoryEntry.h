#pragma once
#include <iostream>

using namespace std;

class DirectoryEntry
{
public:
    string dir_name;
    char dir_attribute;//0x0 , 0x10
    char dir_empty[12] = { '0','0','0','0','0','0','0','0','0','0','0','0' };
    int dir_firstcluster;
    int dir_filesize = 0;

    string convertinttobytes(int fcluster) {
        char cfcluster;
        char arrayofbytes[4] = {};
        int y = fcluster % 10;
        cfcluster = '0' + y;
        arrayofbytes[3] = cfcluster;
        fcluster /= 10;
        y = fcluster % 10;
        cfcluster = '0' + y;
        arrayofbytes[2] = cfcluster;
        fcluster /= 10;
        y = fcluster % 10;
        cfcluster = '0' + y;
        arrayofbytes[1] = cfcluster;
        fcluster /= 10;
        y = fcluster % 10;
        cfcluster = '0' + y;
        arrayofbytes[0] = cfcluster;
        return arrayofbytes;
    }

    int convertbytestoint(char* bytes) {
        int fsize = 0;
        int p = 0;
        p = bytes[3] - '0';
        p += (bytes[2] - '0') * 10;
        p += (bytes[1] - '0') * 100;
        p += (bytes[0] - '0') * 1000;
        fsize = p;
        return fsize;
    }

    string getBytes(DirectoryEntry d) {
        string dentry;
        dentry.append(d.dir_name);
        dentry.append(1, d.dir_attribute);
        for (int i = 0; i < 11; i++) {
            dentry.append(1, d.dir_empty[i]);
        }
        int fcluster = d.dir_firstcluster;
        string sfcluster = convertinttobytes(fcluster);
        dentry.append(sfcluster);
        int fsize = d.dir_filesize;
        string sfsize = convertinttobytes(fsize);
        dentry.append(sfsize);

        return dentry;
    }

    DirectoryEntry getDirectoryEntry(string dentry) {
        DirectoryEntry d;
        d.dir_name = dentry.substr(0, 10);
        d.dir_attribute = dentry[11];
        char arrayofbytes[4] = {};
        for (int i = 24; i < 28; i++) {
            arrayofbytes[i - 24] = dentry[i];
        }
        d.dir_firstcluster = convertbytestoint(arrayofbytes);
        return d;
    }

    //public:
    DirectoryEntry() {
        dir_name = {};
        dir_attribute = {};
        dir_firstcluster = 5;
        dir_filesize = 0;
    }
    //DirectoryEntry() = default;
    DirectoryEntry(string name, char attribute, int firstCluster) {
        dir_name = name;
        dir_attribute = attribute;
        dir_firstcluster = firstCluster;
        /*if (attribute==0) {
            if (name.length() > 11) {
                dir_name = name.substr(0, 7) + name.substr(name.length() - 4);
            }
            else
        }
        else {
            dir_name = name.substr(0, min(11, (int)name.size()));
        }*/
    }
};