#include "Graph.hpp"
#include "Connection.hpp"
#include <queue>

void Graph::addVertice(int src)
{
    adjMap[src] = {};
    numVertices++;
}

void Graph::addConnection(int src, int dest, int type)
{
    if (this->adjMap[src].size() == 0)
        this->numVertices++;

    this->adjMap[src].push_back(Connection(dest, type));
    
}

void Graph::removeConnection(int src, int dest, int type)
{
    adjMap[src].remove(Connection(dest, type));
    if(adjMap.find(src) == adjMap.end()) // key 'src' is not present in the dict
        this->numVertices--;
}

bool Graph::doesConnExist(int src, int dest)
{
    for(auto listEntry : adjMap[src])
    {
        if(listEntry.getDest() == dest)
            return(true);
    }
    return(false);
}


void Graph::reset() 
{
    numVertices = 0;
    // unordered_map<int ,list<Connection>>::iterator itr;
    adjMap.clear();
}

void Graph::printGraph()
{
    for(auto mapEntry : adjMap)
    {
        std::cout << "Source: " << mapEntry.first << "\n";
        for(auto listEntry : mapEntry.second)
        {
            std::cout << "  Destination: " << listEntry.getDest() << " Type: " << listEntry.getType() << std::endl;
        }
    }
}

int Graph::getNumVertices()
{
    return this->numVertices;
}
    // DFS inspired by:
    // https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/

bool Graph::DFSUtil(int vertID, unordered_map<int, bool>* visited, pair<int, int>* cutC, unordered_map<int, bool>* finished = nullptr)
{
    // Mark the current node as visited
    (*visited)[vertID] = true; 
  
    // Recur for all the vertices adjacent 
    // to this vertex 
    for(auto listEntry : adjMap[vertID])
    {
        int destination = listEntry.getDest();
        int destinationType = listEntry.getType();

        // If we're doing checks for backlinks we pass a finished nodes map
        if (finished != nullptr) 
        {   
            // If we're checking backlinks we only care for Provider->Customer paths
            if (destinationType != 1)
                continue;

            // Check if the it's a backlink
            if ((*visited)[destination] && !((*finished)[destination])) {
                return false;
            }
        }

        if((!(*visited)[destination]) && (cutC == nullptr || !isConnectionCut(vertID, destination, cutC)))//need to build a comparator function for the pairs,
        {
            if (!DFSUtil(destination, visited, cutC, finished))
                return false;
        }
    }

    return true;
}

bool Graph::isConnectionCut(int currV, int nextV, pair<int, int>* cutC) 
{
    if (cutC == nullptr)
        return false;

    return((currV == cutC->first && nextV == cutC->second) || (currV == cutC->second && nextV == cutC->first));
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
    DFSUtil(startingV, visited, cutC);
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
bool Graph::checkConnected()
{
    int src = adjMap.begin()->first;
    if(!DFS(src))
    {
        return(false);
    }
    return(true);
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
                std::cout << "Bridge: Source - " << cutC.first << " Destination - " << cutC.second << std::endl;
                return false;
            }
        }
    }

    return true;
}

bool Graph::CheckConnected()
{
    int firstEntry;

    // Get the graph map's first entry
    for (auto mapEntry : adjMap)
    {
        firstEntry = mapEntry.first;
        break;
    }

    // Run DFS on that entry and check if its connected
    if(DFS(firstEntry))
        return true;
    else
        return false;

    return(true);
}

bool Graph::CheckAcyclic()
{
    unordered_map<int, bool>* finished = new unordered_map<int, bool>;
    unordered_map<int, bool>* visited = new unordered_map<int, bool>;

    for (auto mapEntry : adjMap)
    {
        (*visited)[mapEntry.first] = false;
        (*finished)[mapEntry.first] = false;
    }
        
    for (auto mapEntry : adjMap)
    {
        // Perform DFS and pass a finished nodes map in order to check for backlinks
        // If DFSUtil returns 'false' then it means it found a backlink and the graph
        // has a customer-provider cycle
        if (!DFSUtil(mapEntry.first, visited, nullptr, finished))
            return false;

        // Mark the node as finished 
        (*finished)[mapEntry.first] = true;
    }

    return true;
}

bool Graph::CheckCommerciallyConnected(bool connected)
{
    if (!connected)
        return false;

    return true;
}


// bool Graph::CheckAcyclic()
// {   
//     std::cout << "************ CHECK ACYCLIC ************" << std::endl;

//     std::queue<int> queue;


//     // Mark all the vertices as not visited 
//     unordered_map<int, bool>* visited = new unordered_map<int, bool>;
//     for (auto mapEntry : adjMap)
//     {
//         (*visited)[mapEntry.first] = false;
//     }

//     // Iterate through every node
//     for (auto mapEntry : adjMap)
//     {
//         if ((*visited)[mapEntry.first] == false)
//         {
//             // Mark the node as visited and push it to the queue
//             (*visited)[mapEntry.first] = true;
//             queue.push(mapEntry.first);

//             // While the FIFO queue is not empty
//             while(queue.size() != 0)
//             {
//                 int frontOfQueue = queue.front();
//                 queue.pop();

//                 for (auto listEntry: adjMap[frontOfQueue])
//                 {
//                     int destination = listEntry.getDest();
//                     int destinationType = listEntry.getType();

//                     if((*visited)[destination] == true)
//                     {
//                         return false;
//                     }
//                     else
//                     {
//                         (*visited)[destination] = true;
//                         queue.push(destination);
//                     }    
//                 }
//             }
//         }
//     }

//     free(visited);
//     return true;
// }

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
