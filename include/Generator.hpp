#pragma once
#include <stdlib.h>     /* srand, rand */
#include "Graph.hpp"

using namespace std;


class Generator {
    Graph genGraph;
public:
    Graph generateGraph(int);
};