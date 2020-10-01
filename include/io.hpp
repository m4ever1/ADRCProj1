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
    fileIO(fileIO &&) = default;
    fileIO(const fileIO &) = default;
    fileIO &operator=(fileIO &&) = default;
    fileIO &operator=(const fileIO &) = default;
    ~fileIO();
    string readLine();
    int isEOF();
private:
    string fileName;
    ifstream file;
};
