#include "SimpGraph.hpp"

void SimpGraph::aggregateV(list<int> vertList, list<Connection> connlist)
{
    for (auto vert: vertList)
    {
        connlist.remove(Connection(vert, 1));
        connlist.remove(Connection(vert, 2));
        connlist.remove(Connection(vert, 3));
    }
    for(auto vert : vertList)
    {
        connectVtoList(vert, connlist);
    }
}

void SimpGraph::connectVtoList(int src, list<Connection> connList)
{
    if (adjMap[src].size() == 0)
        numVertices++; 

    if (src > maxValue)
        this->maxValue = src;
    this->adjMap[src] = connList;
}
