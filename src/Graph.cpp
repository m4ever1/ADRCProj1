#include "Graph.hpp"
#include "Connection.hpp"
#include <queue>
#include <list>

void Graph::addVertice(int src)
{
    adjMap[src] = {};
    numVertices++;
}

void Graph::addConnection(int src, int dest, int type)
{
    if (this->adjMap[src].size() == 0)
        this->numVertices++; 

    if (src > maxValue)
        this->maxValue = src;
    else if (dest > maxValue)
        this->maxValue = dest;

    this->adjMap[src].push_back(Connection(dest, type));
    
}

void Graph::removeConnection(int src, int dest, int type)
{
    adjMap[src].remove(Connection(dest, type));
    if(adjMap.find(src) == adjMap.end()) // key 'src' is not present in the dict
        this->numVertices--;
}


void Graph::GetSSCGraph(int startingV, bool fullGraph = false) 
{
    unordered_map<int, int>* pre = new unordered_map<int,int>;
    unordered_map<int, int>* post = new unordered_map<int,int>;
    unordered_map<int, bool>* visited = new unordered_map<int,bool>;

    for(auto mapEntry : adjMap)
    {
        (*visited)[mapEntry.first] = false;
    }
    int time = 1;

    DFSwTimingsUtil(startingV, pre, post, visited, &time, false, nullptr);
    
    for(auto mapEntry : adjMap)
    {
        (*visited)[mapEntry.first] = false;
    }

    Graph SSC;
    pair<int, int> lastV;

    if (fullGraph)
    {
        while (!(post->empty()))
        {
            pair<int, int> lastV = keyWithLargestValue(*post);
            cout << "Oldest discovered: " << lastV.first << " Value: " << lastV.second << endl;

            this->maxValue = this->maxValue + 1;
            Graph SSC;

            DFSwTimingsUtil(lastV.first, nullptr, post, visited, &time, true, &SSC);
            
            SSC.printGraph();
            cout << "*********" << endl;

            // Iterate through every node in the discovered cycle
            for (auto node : SSC.adjMap)
            {
                // Check if the node is in the original map
                //if (this->adjMap.find(node.first) == this->adjMap.end())
                //{
                    // In every connection of every node in the discovered cycle
                    for (auto connection : node.second)
                    {
                        int destination = connection.getDest();
                        int destinationType = connection.getType();

                        // If the connection exists in the original map's connection list
                        // of the node in question we remove it
                        bool foundConnection = false;
                        for (auto listEntry : this->adjMap[node.first])
                        {
                            // If we find the 
                            if (connection == listEntry)
                            {
                                foundConnection = true;
 
                                this->adjMap[node.first].remove(listEntry);
                                break;
                            }
                        }

                        // We use max value in order to create a new connection to a new node
                        // where the new node will be an aggregate of every node that belongs to the cycle
                        if (!foundConnection)
                        {
                            this->addConnection(this->maxValue, destination, destinationType);
                        }   
                   }
               //}

                adjMap.erase(node.first);
           }
        }   
    }
    else
    {
        DFSwTimingsUtil(lastV.first, nullptr, post, visited, &time, true, &SSC);
    }
    
    
    cout << "Final Adjacency List" << endl;
    this->printGraph();
}


void Graph::DFSwTimingsUtil(
    int vertID, 
    unordered_map<int, int>* pre, 
    unordered_map<int,int>* post, 
    unordered_map<int, bool>* visited, 
    int* time, 
    bool reversed, 
    Graph* outputG
) 
{
    if(!reversed)
    {
        (*visited)[vertID] = true;
        (*pre)[vertID] = *time;
        (*time)++;

        int desiredType = 1;
 
        for(auto listEntry : adjMap[vertID])
        {
            int dest = listEntry.getDest();
            int type = listEntry.getType();
            if(!(*visited)[dest] && type == desiredType)
            {
                DFSwTimingsUtil(dest, pre, post, visited, time, reversed, nullptr);
            }
        }
        (*post)[vertID] = *time;
        (*time)++;
    }
    else
    {
        (*visited)[vertID] = true;
        (*post).erase(vertID);

        int desiredType = 3;
        for(auto listEntry : adjMap[vertID])
        {
            int dest = listEntry.getDest();
            int type = listEntry.getType();
            if(type == desiredType)
            {
                (*outputG).addConnection(vertID, dest, type);
                (*outputG).addConnection(dest, vertID, Connection::getReciprocalType(type));
                if(!(*visited)[dest])
                {
                    DFSwTimingsUtil(dest, pre, post, visited, time, reversed, outputG);
                }
            }
        }
    }
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

bool Graph::DFSUtil(int vertID, unordered_map<int, bool>* visited, pair<int, int>* cutC = nullptr, int previousType = 0)
{
    // Mark the current node as visited
    (*visited)[vertID] = true; 
  
    // Recur for all the vertices adjacent 
    // to this vertex 
    for(auto listEntry : adjMap[vertID])
    {
        int destination = listEntry.getDest();
        int destinationType = listEntry.getType();
        bool ignore = false;

        switch (previousType)
        {
            // A provider can only go to other providers (C)
            // A Peer-to-Peer can only go to other providers (R)
            case 1:
                if (destinationType != 1)
                    ignore = true;
                break;
            case 2:
                if (destinationType != 1)
                    ignore = true;
                break;
            // Everything else can go to every other type of connection (PRC)
            default:
                break;
        }

        if((!ignore) && (!(*visited)[destination]) && (cutC == nullptr || !isConnectionCut(vertID, destination, cutC)))//need to build a comparator function for the pairs,
        {   
            if (previousType == 0)
                destinationType = 0;

            if (!DFSUtil(destination, visited, cutC, destinationType))
                return false;
        }
    }

    return true;
}

bool Graph::isConnectionCut(int currV, int nextV, pair<int, int>* cutC) 
{
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
        return false;

    return true;
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

bool Graph::cyclicUtil(int vertID, unordered_map<int, bool>* visited, unordered_map<int, bool>* recStack)
{
    if(!(*visited)[vertID])
    {
        (*visited)[vertID] = true;
        (*recStack)[vertID] = true;

        for(auto listEntry : adjMap[vertID])
        {  
            int dest = listEntry.getDest();
            int type = listEntry.getType();
            if(!((*visited)[dest]) && (type == 1) && cyclicUtil(dest, visited, recStack))
            {
                return true;
            }
            else if((*recStack)[dest] && (type == 1))
            {
                return true;
            }
        }
    }
    (*recStack)[vertID] = false;
    return false;
}

bool Graph::CheckCyclic(list<int>* listOut = nullptr)
{
    unordered_map<int, bool>* recStack = new unordered_map<int, bool>;
    unordered_map<int, bool>* visited = new unordered_map<int, bool>;

    for (auto mapEntry : adjMap)
    {
        (*visited)[mapEntry.first] = false;
        (*recStack)[mapEntry.first] = false;
    }
        
    for (auto mapEntry : adjMap)
    {
        // Perform DFS and pass a finished nodes map in order to check for backlinks
        // If DFSUtil returns 'false' then it means it found a backlink and the graph
        // has a customer-provider cycle
        if (cyclicUtil(mapEntry.first, visited, recStack))
        {
            if(listOut != nullptr)
            {
                for(auto entry : *recStack)
                {
                    if(entry.second)
                    {
                        (*listOut).push_back(entry.first);
                    }
                } 
            }
            return true;
        }

    }
    free(recStack);
    free(visited);
    return false;
}

bool Graph::CheckCommerciallyConnected(bool connected)
{
    // If we know the graph is not connected then it means it's also not
    // commercially connected
    if (!connected)
        return false;

    // Get the first node as a starting point
    int src;

    // Mark all the vertices as not visited 
    unordered_map<int, bool>* visited = new unordered_map<int, bool>;


    // Call the recursive helper function 
    // to print DFS traversal 
    for(auto mapEntry : adjMap)
    {
        for (auto mapEntry : adjMap)
        {
            (*visited)[mapEntry.first] = false;
        }
        src = mapEntry.first;
        DFSUtil(src, visited, nullptr, -1);

        for(auto entry : *visited)// inefficient, better to have a counter inside the DFS stack
        {
            if(entry.second == false)
            {    
                free(visited);
                return false;
            }
        }
    }




    free(visited);
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
