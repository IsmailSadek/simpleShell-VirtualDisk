#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;
using namespace std;
using std::filesystem::exists;

class FAT
{
private:
    int* fat_table;
    void initialize() {
        for (int i = 0; i < 1024; i++) {
            if (i < 5)
                fat_table[i] = -1;
            else if (i == 1023)
                fat_table[i] = 1234;
            else
                fat_table[i] = 0;
        }
        /*for (int i = 0; i < 1024; i++) {
            cout << fat_table[i];
        }*/
        cout << endl;
    }
    void write_fat_table() {
        std::fstream fs;
        fs.open("Virtual Desk.txt");
        if (fs.is_open()) {
            cout << "\t hello \t" << endl;

            char arrayofbytes[1024][4] = {};
            for (int i = 0; i < 1024; i++)
            {
                char bytes;
                int n = fat_table[i];
                if (n == -1) {
                    arrayofbytes[i][3] = '$';
                    arrayofbytes[i][2] = '0';
                    arrayofbytes[i][1] = '0';
                    arrayofbytes[i][0] = '0';
                }
                else {
                    int y = n % 10;
                    bytes = '0' + y;
                    arrayofbytes[i][3] = bytes;
                    n /= 10;
                    y = n % 10;
                    bytes = '0' + y;
                    arrayofbytes[i][2] = bytes;
                    n /= 10;
                    y = n % 10;
                    bytes = '0' + y;
                    arrayofbytes[i][1] = bytes;
                    n /= 10;
                    y = n % 10;
                    bytes = '0' + y;
                    arrayofbytes[i][0] = bytes;
                }
                //printing the fat table
                 //cout << "Integer: " << fat_table[i] << " ";
                 //cout << "Byte Array: ";
                /* for (int j = 0; j < 4; j++)
                 {
                     cout << arrayofbytes[i][j] <<" ";
                 }*/
                 //cout << endl;
            }
            //cout << endl;
            fs.seekg(1024, ios::beg); // seeking to the place of the fat table

            for (int i = 0; i < 1024; i++) {
                for (int j = 0; j < 4; j++) {
                    fs << arrayofbytes[i][j];
                    //cout << arrayofbytes[i][j] << " ";
                }
            }
            fs.close();
        }
    }
    int* read_fat_table() {
        int retrievedFatTable[1024] = {};
        std::fstream fs;
        fs.open("Virtual Desk.txt");
        char readingFatTable[4 * 1024] = {};
        char FatTable2[1024][4] = {};
        if (fs.is_open()) {
            fs.seekg(1024, ios::beg);
            fs.read(readingFatTable, 4 * 1024);
            fs.close();
        }
        int p = 0;
        int counter = 0;
        for (int i = 0; i < 1024; i++) {
            for (int j = 0; j <= 3; j++) {

                FatTable2[i][j] = readingFatTable[counter];
                //cout << FatTable2[i][j] << " ";
                counter++;
            }
            //cout << endl;
        }
        for (int i = 0; i < 1024; i++) {
            if (FatTable2[i][3] == '$') {
                retrievedFatTable[i] = -1;
            }
            else {
                p = FatTable2[i][3] - '0';
                p += (FatTable2[i][2] - '0') * 10;
                p += (FatTable2[i][1] - '0') * 100;
                p += (FatTable2[i][0] - '0') * 1000;
                retrievedFatTable[i] = p;
            }
            //cout << retrievedFatTable[i] << endl;
        }
        return retrievedFatTable;
    }
    void printFatTable() {
        int* actualFatTable = read_fat_table();
        for (int i = 0; i < 1024; i++) {
            cout << i << '\t' << actualFatTable[i] << endl;
        }
    }
    int getAvailableBlock() {
        int* searchFatTable = read_fat_table();
        for (int i = 5; i < 1024; i++) {
            if (searchFatTable[i] == 0) {
                return i;
            }
        }
        return -1;
    }
    int getAvailableBlocks() {
        int* searchFatTable = read_fat_table();
        int counter = 0;
        for (int i = 5; i < 1024; i++) {
            if (searchFatTable[i] == 0) {
                counter += 1;
            }
        }
        return counter;
    }
    int getNext(int index) {
        int* getValueinFatTable = read_fat_table();
        int valueInThisIndex = getValueinFatTable[index];
        return valueInThisIndex;
    }
    void setNext(int index, int value) {
        fat_table[index] = value;
        write_fat_table();
    }
public:
    FAT() {
        fat_table = new int[1024];
        initialize();
        write_fat_table();
        //read_fat_table();
        //setNext(5, 5);
        //cout << getNext(5) << endl;
        //printFatTable();
        /*int fblock=getAvailableBlock();
        int cblock = getAvailableBlocks();
        cout << fblock << "..........." << cblock << endl;*/
    }
};