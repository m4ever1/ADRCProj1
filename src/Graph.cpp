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

unordered_map<int ,list<Connection>> Graph::getAdjMap()
{
    return (adjMap);
}

bool Graph::CheckCyclicFast(Graph* outputG)
{
    int vert = adjMap.begin()->first;
    return(GetSCCGraph(vert, outputG, false));
    
}

bool Graph::GetSCCGraph(int startingV, Graph* outputG, bool fullGraph = false) //returns true if cyclic
{
    unordered_map<int, int>* pre = new unordered_map<int,int>;
    unordered_map<int, int>* post = new unordered_map<int,int>;
    unordered_map<int, bool>* visited = new unordered_map<int,bool>;

    for(auto mapEntry : adjMap)
    {
        (*visited)[mapEntry.first] = false;
    }
    int time = 1;
    DFSwTimingsUtil(startingV, pre, post, visited, &time, false, nullptr, nullptr, nullptr);
    for(auto mapEntry : adjMap)
    {
        if(!(*visited)[mapEntry.first])
        {
            DFSwTimingsUtil(mapEntry.first, pre, post, visited, &time, false, nullptr, nullptr, nullptr);
        }
    }
    for(auto mapEntry : adjMap)
    {   
        (*visited)[mapEntry.first] = false;
    }

    pair<int, int> lastV;

    list<Connection> connList; 
    list<int> vertList;
    if (fullGraph)
    {

        while (!(post->empty()))
        {
            lastV = keyWithLargestValue(*post);
            cout << "Oldest discovered: " << lastV.first << " Value: " << lastV.second << endl;

            this->maxValue = this->maxValue + 1;
 

            DFSwTimingsUtil(lastV.first, nullptr, post, visited, &time, true, nullptr, &connList, &vertList);
            (*outputG).aggregateV(vertList, connList);
            // (*outputG).printGraph();
            connList.clear();
            vertList.clear();
            cout << "*********" << endl;
        }
        for (auto mapEntry : adjMap)
        {
            for(auto entry: mapEntry.second)
            {
                int newNode = (*outputG).redirectMap[mapEntry.first];
                int oldDest = entry.getDest();
                int newDest = (*outputG).redirectMap[oldDest];
                int type = entry.getType();
                if(newDest != newNode && oldDest != newDest)
                    (*outputG).addConnection(newNode, newDest, type);
            }
        }
           
    }
    else
    {
        //NEEDS CHANGE, ONLY FINDS A CYCLE IF IT HAS THE LASTV vertice IN IT!!!!!!!
        lastV = keyWithLargestValue(*post);
        DFSwTimingsUtil(lastV.first, nullptr, post, visited, &time, true, outputG, &connList, &vertList);

    }
    
    cout << "Final Adjacency List" << endl;
    if(outputG != nullptr)
        (*outputG).printGraph();

    if ((*outputG).getNumVertices() > 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void Graph::DFSwTimingsUtil(
    int vertID, 
    unordered_map<int, int>* pre, 
    unordered_map<int,int>* post, 
    unordered_map<int, bool>* visited, 
    int* time, 
    bool reversed, 
    Graph* outputG,
    list<Connection>* connList,
    list<int>* vertList
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
            if(type == desiredType)
            {
                if(!(*visited)[dest])
                {
                    DFSwTimingsUtil(dest, pre, post, visited, time, reversed, nullptr, nullptr, nullptr);
                }
                
            }
        }
        (*post)[vertID] = *time;
        (*time)++;
    }
    else
    {
        (*vertList).push_back(vertID);
        (*visited)[vertID] = true;
        (*post).erase(vertID);

        if(outputG != nullptr)
        {
            (*outputG).addVertice(vertID);   
        }

        int desiredType = 3;
        for(auto listEntry : adjMap[vertID])
        {
            int dest = listEntry.getDest();
            int type = listEntry.getType();
            if(type == desiredType)
            {

                // (*outputG).addConnection(vertID, dest, type);
                // (*outputG).addConnection(dest, vertID, Connection::getReciprocalType(type));
                if(!(*visited)[dest])
                {
                    
                    DFSwTimingsUtil(dest, pre, post, visited, time, reversed, outputG, connList, vertList);
                }
                else
                {

                    (*connList).push_back(Connection(dest, type));
                }
                
            }
            else
            {
                (*connList).push_back(Connection(dest, type));
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

bool Graph::CheckCommerciallyConnectedFast()
{
    Graph* simpleG = new Graph;

    unordered_map<int ,list<Connection>> mapToUse;

    if(CheckCyclicFast(simpleG))
    {
        simpleG->reset();
        GetSCCGraph(adjMap.begin()->first, simpleG, true);
        mapToUse = (*simpleG).getAdjMap();    
    }
    else
    {
        mapToUse = adjMap;
    }
    
    std::list<int> checkList;
    bool check = true;
    for (auto mapEntry : mapToUse)
    {
        check = true;
        for(auto listEntry: mapEntry.second)
        {
            if (listEntry.getType() == 3)
            {
                check = false;
                break;
            }
        }
        if(check)
            checkList.push_front(mapEntry.first);
    }
    if(checkList.size() == 1)
    {
        return true;
    }
    //SUBSTITUIDO POR DFS LMAOOOO
    unordered_set<int> set;
    for (auto entry: checkList)
    {
        for(auto conn: mapToUse[entry])
        {
            set.insert(conn.getDest());
        }
        for(auto otherEntry: checkList)
        {
            if(otherEntry == entry)
                continue;
            if(set.find(otherEntry) == set.end())
            {
                simpleG->printGraph();
                free(simpleG);
                return false;
            }
        }
        set.clear();
    }
    // std::list<int>::iterator at;
    // for(auto entry : checkList)
    // {
    //     for(auto conn : mapToUse[entry])
    //     {
    //         at = std::find(checkList.begin() , checkList.end(), conn.getDest());
    //         if(at == checkList.end())
    //         {    
    //             free(simpleG);
    //             return false;
    //         }
    //     }
    // }
    simpleG->printGraph();
    free(simpleG);
    return true;
    
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

void Graph::aggregateV(list<int> vertList, list<Connection> connlist)
{

    int root = vertList.front();
    for(auto vert : vertList)
    {
        redirectMap[vert] = root;

    }
    // connectVtoList(root, connlist);
}

void Graph::connectVtoList(int src, list<Connection> connList)
{
    
    if (adjMap[src].size() == 0)
        numVertices++; 

    if (src > maxValue)
        this->maxValue = src;
    for(auto entry: connList)
    {
        int oldDest = entry.getDest();
        int newDest = redirectMap[oldDest];
        entry.setDest(newDest);
    }
    this->adjMap[src] = connList;
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
