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
    // DFS inspired by:
    // https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/

void Graph::DFSUtil(int vertID, unordered_map<int, bool>* visited)
{
    // Mark the current node as visited and 
    // print it 
    (*visited)[vertID] = true; 
    cout << vertID << " "; 
  
    // Recur for all the vertices adjacent 
    // to this vertex 
    for(auto listEntry : adjMap[vertID])
    {
        int currV = listEntry.getDest();
        if(!(*visited)[currV])
        {
            DFSUtil(currV, visited);
        }
    }
}

void Graph::DFS(int startingV)
{
    // Mark all the vertices as not visited 
    unordered_map<int, bool>* visited = new unordered_map<int, bool>;
    for (auto mapEntry : adjMap)
    {
        (*visited)[mapEntry.first] = false;
    }
    // Call the recursive helper function 
    // to print DFS traversal 
    DFSUtil(startingV, visited);
}

void Graph::CheckBiConnected()
{
    for (auto mapEntry : adjMap)
    {
        for(auto listEntry : mapEntry.second)
        {
            // Remove connection
            // Check if connect
            // Restore Connection
        }
    }
}

// unordered_map<int ,list<Connection>> Graph::CloneAdjacencyList()
// {
//     unordered_map<int ,list<Connection>> replicaMap;

//     for(auto mapEntry : adjMap)
//     {
//         for(auto listEntry : mapEntry.second)
//         {
//             replicaMap[mapEntry.first].push_back(Connection(listEntry.getDest(), listEntry.getType());
//         }
//     }
// }