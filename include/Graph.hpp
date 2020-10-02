#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include "Connection.hpp"

using namespace std;

// (key,value) -> list -> {(node nr of tail, type of connection) 
// (key1,value1) -> list -> idem
// idem...

class Graph {
    unordered_map<int ,list<Connection>> adjMap; //unordered hasmap of lists of vertices
public:
    void addVertice(int);
    void addConnection(int, int, int);
    void printGraph();
};