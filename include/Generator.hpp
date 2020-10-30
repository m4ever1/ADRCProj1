#pragma once
#include <stdlib.h>     /* srand, rand */
#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;


class Generator {
    Graph genGraph;
public:
    Graph generateGraph(int);
};