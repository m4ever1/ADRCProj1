#pragma once
#include "Graph.hpp"

using namespace std;

class SimpGraph: public Graph {
public:
    void aggregateV(list<int>, list<Connection>);
    void connectVtoList(int, list<Connection>);
    bool CheckCyclicFast(Graph*);
    bool GetSCCGraph(int, SimpGraph*, bool);
    void DFSwTimingsUtil(int, 
        unordered_map<int, int>*,
        unordered_map<int,int>*, 
        unordered_map<int, bool>*, 
        int*, 
        bool, 
        Graph*, 
        list<Connection>*, 
        list<int>*);
};