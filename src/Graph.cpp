#include "Graph.hpp"
#include "Connection.hpp"



void Graph::addConnection(int src, int dest, int type)
{
    this->adjMap[src].push_back(Connection(dest, type));
    this->numVertices++;
}

void Graph::printGraph()
{
    // unordered_map<int ,list<Connection>>::iterator itr;
    for(auto mapEntry : adjMap)
    {
        std::cout << mapEntry.first << " ";
        for(auto listEntry : mapEntry.second)
        {
            std::cout << listEntry.getDest() << " " << listEntry.getType() << std::endl;
        }
    }
}

int Graph::getNumVertices()
{
    return this->numVertices;
}