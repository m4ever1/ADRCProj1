#pragma once
#include <iostream>
#include <string>
#include <fstream> 
using namespace std;

class fileIO
{
public:
    fileIO(string fileName_);
    void openFile();
    ~fileIO();
    string readLine();
private:
    string fileName;
    ifstream file;
};
