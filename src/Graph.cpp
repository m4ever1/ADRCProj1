#include "Graph.hpp"
#include "Connection.hpp"


void Graph::addConnection(int src, int dest, int type)
{
    this->adjMap[src].push_back(Connection(dest, type));
    this->numVertices++;
}

void Graph::removeConnection(int src, int dest, int type)
{
    adjMap[src].remove(Connection(dest, type));
}

void Graph::reset() 
{
    numVertices = 0;
    // unordered_map<int ,list<Connection>>::iterator itr;
    adjMap.clear();
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

void Graph::DFSUtil(int vertID, unordered_map<int, bool>* visited, pair<int, int> cutC)
{
    // Mark the current node as visited and 
    // print it 
    (*visited)[vertID] = true; 
    cout << vertID << " "; 
  
    // Recur for all the vertices adjacent 
    // to this vertex 
    for(auto listEntry : adjMap[vertID])
    {
        int nextV = listEntry.getDest();
        if((!(*visited)[nextV]) && !isConnectionCut(vertID, nextV, cutC))//need to build a comparator function for the pairs,
        {
            DFSUtil(nextV, visited, cutC);
        }
    }
}

bool Graph::isConnectionCut(int currV, int nextV, pair<int, int> cutC) 
{
    return((currV == cutC.first && nextV == cutC.second) || (currV == cutC.second && nextV == cutC.first));
}

bool Graph::DFS(int startingV, pair<int, int>* cutC = nullptr)
{
    bool connected = true;
    // Mark all the vertices as not visited 
    unordered_map<int, bool>* visited = new unordered_map<int, bool>;
    for (auto mapEntry : adjMap)
    {
        (*visited)[mapEntry.first] = false;
    }
    // Call the recursive helper function 
    // to print DFS traversal 
    DFSUtil(startingV, visited, *cutC);
    for(auto entry : *visited)// inefficient, better to have a counter inside the DFS stack
    {
        if(entry.second == false)
        {
            connected = false;
        }
    }
    free(visited);
    return connected;
}

bool Graph::CheckBiConnected()
{
    list<pair<int, int>> checkedConnections;
    for (auto mapEntry : adjMap)
    {
        for(auto listEntry : mapEntry.second)
        {
            int src = mapEntry.first;
            int dest = listEntry.getDest();
            // Add to checked connections
            pair<int, int> cutC = make_pair(src, dest);
            checkedConnections.push_back(make_pair(src, dest));
            // Check if connected
            if(!DFS(src, &cutC))
            {
                return(false);
            }
        }
    }
    return(true);
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