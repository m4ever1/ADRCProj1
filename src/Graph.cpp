#include "Graph.hpp"
#include "Connection.hpp"
#include <queue>

void Graph::addConnection(int src, int dest, int type)
{
    if (this->adjMap[src].size() == 0)
        this->numVertices++;

    this->adjMap[src].push_back(Connection(dest, type));
    
}

void Graph::removeConnection(int src, int dest, int type)
{
    adjMap[src].remove(Connection(dest, type));
}

void Graph::printGraph()
{
    std::cout << "**************** GRAPH ****************" << std::endl;
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

void Graph::DFSUtil(int vertID, unordered_map<int, bool>* visited, pair<int, int>* cutC)
{
    // Mark the current node as visited and 
    // print it 
    (*visited)[vertID] = true; 
    //std::cout << vertID << " "; 
  
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

bool Graph::isConnectionCut(int currV, int nextV, pair<int, int>* cutC) 
{
    // If cutC is null then it means we're performing this check on 
    // 'CheckConnected' which doesn't remove bridges, so we just return false
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

bool Graph::CheckBiConnected()
{
    std::cout << "********** CHECK BICONNECTED **********" << std::endl;
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
                return(false);
            }
        }
    }

    return(true);
}

bool Graph::CheckConnected()
{
    std::cout << "*********** CHECK CONNECTED ***********" << std::endl;
    int firstEntry;

    // Get the graph map's first entry
    for (auto mapEntry : adjMap)
    {
        firstEntry = mapEntry.first;
        break;
    }

    // Run DFS on that entry and check if its connected
    if(!DFS(firstEntry))
        return(false);
    else
        return(true);

    return(true);
}

bool Graph::CheckAcyclic()
{   
    std::cout << "************ CHECK ACYCLIC ************" << std::endl;

    std::queue<int> queue;

    // Create an array of roles: Provider (1) and Customer (3)
    int roles[] = {1, 3};

    // Mark all the vertices as not visited 
    unordered_map<int, bool>* visited = new unordered_map<int, bool>;
    for (auto mapEntry : adjMap)
    {
        (*visited)[mapEntry.first] = false;
    }

    // Iterate through every node
    for (auto mapEntry : adjMap)
    {
        if ((*visited)[mapEntry.first] == false)
        {
            // Mark the node as visited and push it to the queue
            (*visited)[mapEntry.first] = true;
            queue.push(mapEntry.first);

            // While the FIFO queue is not empty
            while(queue.size() != 0)
            {
                int frontOfQueue = queue.front();
                queue.pop();

                for (auto listEntry: adjMap[frontOfQueue])
                {
                    int destination = listEntry.getDest();
                    int destinationType = listEntry.getType();

                    if((*visited)[destination] == true)
                    {
                        return false;
                    }
                    else
                    {
                        (*visited)[destination] = true;
                        queue.push(destination);
                    }    
                }
            }
        }
    }

    free(visited);
    return true;
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