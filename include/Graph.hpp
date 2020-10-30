#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include <utility> 
#include <algorithm>
#include "Connection.hpp"
#include "utils.hpp"
#include <unordered_set>
#include <stack>
#include <stdlib.h>  
#include <ctime>
#define NIL -1 

using namespace std;

// (key,value) -> list -> {(node nr of tail, type of connection) 
// (key1,value1) -> list -> idem
// idem...

class Graph {
protected:
    unordered_map<int ,list<Connection>> adjMap; //unordered hasmap of lists of vertices
    unordered_map<int, int> redirectMap;
    int numVertices = 0;
    bool DFSUtil(int , unordered_map<int, bool>*, pair<int, int>*, int);
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
    bool CheckBiConnectedFast(pair<int, int>*);
    bool CheckConnected();
    bool cyclicUtil(int , unordered_map<int, bool>*, unordered_map<int, bool>*);
    bool CheckCyclic(list<int>*);
    bool CheckCommerciallyConnected(bool);
    bool CheckCommerciallyConnectedFast();
    unordered_map<int ,list<Connection>> CloneAdjacencyList();
    void removeConnection(int, int, int);
    bool CheckCyclicFast(Graph*);
    bool GetSCCGraph(int, Graph*, bool);
    bool bridgeUtil(int, unordered_map<int, bool>*, unordered_map<int, int>*,  
                                  unordered_map<int, int>*, unordered_map<int, int>*);
    void DFSwTimingsUtil(int, 
        unordered_map<int, int>*, 
        stack<int>*, 
        unordered_map<int, bool>*, 
        int*, 
        bool, 
        Graph*,
        list<int>*);

    void aggregateV(list<int>);
    void connectVtoList(int, list<Connection>);
    unordered_map<int ,list<Connection>> getAdjMap();
    void reset();
};

