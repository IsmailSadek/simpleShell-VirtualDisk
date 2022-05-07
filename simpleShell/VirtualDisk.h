#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;
using namespace std;
using std::filesystem::exists;

class VirtualDisk
{
private:
    void initialize()
    {
        if (exists("Virtual Desk.txt") == 0)
        {
            ofstream myfile("Virtual Desk.txt");
            if (myfile.is_open())
            {
                //reserves space for the super block
                for (int count = 0; count < 1024; count++)
                {
                    myfile << '0';
                }
                //reserves space for the fat table
                for (int count = 1024; count < 5 * 1024; count++)
                {
                    myfile << '*';
                }
                //reserves space for the actual data
                for (int count = 5 * 1024; count < 1024 * 1024; count++)
                {
                    myfile << '#';
                }
                myfile.close();
            }
            else {
                cout << "Unable to open file";
            }
        }
        else {
            cout << "the file exists" << endl;
        }
    }
    void writeBlock(string datatoBeWritten, int index) {
        std::fstream fs;
        fs.open("Virtual Desk.txt");
        if (fs.is_open()) {

            int seekvalue = index * 1024;
            fs.seekg(seekvalue, ios::beg); // seeking to the place of the cluster
            
            for (int i = 0; i < 1024; i++) {
                fs << datatoBeWritten[i];
            }
            fs.close();
        }
    }
    string getBlock(int index) {
        std::fstream fs;
        fs.open("Virtual Desk.txt");
        char reading[1024] = {};
        if (fs.is_open()) {
            int indexValue = 1024 * index;
            fs.seekg(indexValue, ios::beg);
            
            fs.read(reading, 1024);
            fs.close();
        }
        return reading;
    }
public:
    VirtualDisk() {
        initialize();
    }
};
