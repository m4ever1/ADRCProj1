#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Graph.hpp" 
using namespace std;

class fileIO
{
public:
    fileIO(string fileName_);
    void openFile();
    ~fileIO();
    string readLine();
    void outputToFile(Graph);
private:
    string fileName;
    ifstream file;
};
