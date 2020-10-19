#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include <utility> 
#include "Connection.hpp"

using namespace std;

// (key,value) -> list -> {(node nr of tail, type of connection) 
// (key1,value1) -> list -> idem
// idem...

class Graph {
    unordered_map<int ,list<Connection>> adjMap; //unordered hasmap of lists of vertices
    int numVertices = 0;
    bool DFSUtil(int , unordered_map<int, bool>*, pair<int, int>*, unordered_map<int, bool>*, bool);
    bool isConnectionCut(int, int, pair<int, int>*);
public:
    bool doesConnExist(int, int);
    void addVertice(int);
    void addConnection(int, int, int);
    void printGraph();
    int getNumVertices();
    bool DFS(int, pair<int, int>*);
    bool checkConnected();
    bool CheckBiConnected();
    bool CheckConnected();
    bool cyclicUtil(int , unordered_map<int, bool>*, unordered_map<int, bool>*);
    bool CheckCyclic(list<int>*);
    bool CheckCommerciallyConnected(bool conencted);
    unordered_map<int ,list<Connection>> CloneAdjacencyList();
    void removeConnection(int, int, int);
    void reset();
};