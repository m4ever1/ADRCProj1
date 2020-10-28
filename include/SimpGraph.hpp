#pragma once
#include "Graph.hpp"

class SimpGraph : public Graph 
{
public:
    void aggregateV(list<int>, list<Connection>);
    void connectVtoList(int, list<Connection>);
};