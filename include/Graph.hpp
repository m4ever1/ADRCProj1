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
    void DFSUtil(int , unordered_map<int, bool>*, pair<int, int>*);
    bool isConnectionCut(int, int, pair<int, int>*);
public:
    void addVertice(int);
    void addConnection(int, int, int);
    void printGraph();
    int getNumVertices();
    bool DFS(int, pair<int, int>*);
    bool CheckBiConnected();
    bool CheckConnected();
    bool CheckAcyclic();
    unordered_map<int ,list<Connection>> CloneAdjacencyList();
    void removeConnection(int, int, int);
};