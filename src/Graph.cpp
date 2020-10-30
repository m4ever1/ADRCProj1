#include "Graph.hpp"
#include "Connection.hpp"
#include <queue>
#include <list>


using namespace std;

void Graph::addVertice(int src)
{
    adjMap[src] = {};
    numVertices++;
}

void Graph::addConnection(int src, int dest, int type)
{
    if (this->adjMap[src].size() == 0)
        this->numVertices++; 
    numConn++;
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
    unordered_map<int, int> pre;
    stack<int> post;
    unordered_map<int, bool> visited;

    for(auto mapEntry : adjMap)
    {
        (visited)[mapEntry.first] = false;
    }
    int time = 1;
    DFSwTimingsUtil(startingV, &pre, &post, &visited, &time, false, nullptr, nullptr);
    for(auto mapEntry : adjMap)
    {
        if(!(visited)[mapEntry.first])
        {
            DFSwTimingsUtil(mapEntry.first, &pre, &post, &visited, &time, false, nullptr, nullptr);
        }
    }
    for(auto mapEntry : adjMap)
    {   
        (visited)[mapEntry.first] = false;
    }

    list<int> vertList;
    bool cyclic = false;
    while (!(post.empty()))
    {

        DFSwTimingsUtil(post.top(), nullptr, &post, &visited, &time, true, nullptr, &vertList);

        if(vertList.size() > 1)
        {
            cyclic = true;
            if(!fullGraph)
                return true;
        }
        
        (*outputG).aggregateV(vertList);
        vertList.clear();
    }
    for (auto mapEntry : adjMap)
    {
        for(auto entry: mapEntry.second)
        {
            int newNode = (*outputG).redirectMap[mapEntry.first];
            int oldDest = entry.getDest();
            int newDest = (*outputG).redirectMap[oldDest];
            int type = entry.getType();
            if(newDest != newNode)
            {                
                (*outputG).addConnection(newNode, newDest, type);
                (*outputG).addConnection(newDest, newNode, Connection::getReciprocalType(type));
            }
        }
    }

    return cyclic;
}
// returns true if bridge was found
bool Graph::bridgeUtil(int vertID, unordered_map<int, bool>* visited, unordered_map<int, int>* disc,  
                                  unordered_map<int, int>* low, unordered_map<int, int>* parent, pair<int,int>* output) 
{ 
    // A static variable is used for simplicity, we can  
    // avoid use of static variable by passing a pointer. 
    static int time = 0; 
  
    // Mark the current node as visited 
    (*visited)[vertID] = true; 
  
    // Initialize discovery time and low value 
    (*disc)[vertID] = (*low)[vertID] = ++time; 
  
    // Go through all vertices aadjacent to this 
 
    for (auto listEntry : adjMap[vertID]) 
    { 
        int dest = listEntry.getDest();  // v is current adjacent of u 
  
        // If v is not visited yet, then recur for it 
        if (!(*visited)[dest]) 
        { 
            (*parent)[dest] = vertID; 
            if(bridgeUtil(dest, visited, disc, low, parent, output))
            {
                return true;
            }
            // Check if the subtree rooted with v has a  
            // connection to one of the ancestors of u 
            (*low)[vertID]  = min((*low)[vertID], (*low)[dest]); 
  
            // If the lowest vertex reachable from subtree  
            // under v is  below u in DFS tree, then u-v  
            // is a bridge 
            if ((*low)[dest] > (*disc)[vertID]) 
            {  
                {   
                    (*output).first = vertID;
                    (*output).second = dest;
                    return true;
                }
            } 
        } 
  
        // Update low value of u for parent function calls. 
        else if (dest != (*parent)[vertID]) 
            (*low)[vertID]  = min((*low)[vertID], (*disc)[dest]); 
    }
    return false;
} 

bool Graph::CheckBiConnectedFast(pair<int, int>* bridge)
{
    unordered_map<int, int> disc;
    unordered_map<int, int> low;
    unordered_map<int, int> parent;
    unordered_map<int, bool> visited;

    for(auto mapEntry : adjMap)
    {
        (visited)[mapEntry.first] = false;
        parent[mapEntry.first] = NIL;
    }

    for(auto mapEntry : adjMap)
    {
        if(!visited[mapEntry.first])
        {
            if(bridgeUtil(mapEntry.first, &visited, &disc, &low, &parent, bridge))
            {
                return false;
            }
        }
    }
    return true;
}

void Graph::DFSwTimingsUtil(
    int vertID, 
    unordered_map<int, int>* pre, 
    stack<int>* post, 
    unordered_map<int, bool>* visited, 
    int* time, 
    bool reversed, 
    Graph* outputG,
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
                    DFSwTimingsUtil(dest, pre, post, visited, time, reversed, nullptr, nullptr);
                }
            }
        }
        (*post).push(vertID);
        (*time)++;
    }
    else
    {
        (*vertList).push_back(vertID);
        (*visited)[vertID] = true;
        (*post).pop();

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
                if(!(*visited)[dest])
                {   
                    DFSwTimingsUtil(dest, pre, post, visited, time, reversed, outputG, vertList);
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
    redirectMap.clear();
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

bool Graph::CheckCyclic(list<int>* listOut)
{
    unordered_map<int, bool> recStack;
    unordered_map<int, bool> visited;

    for (auto mapEntry : adjMap)
    {
        (visited)[mapEntry.first] = false;
        (recStack)[mapEntry.first] = false;
    }
        
    for (auto mapEntry : adjMap)
    {
        if (cyclicUtil(mapEntry.first, &visited, &recStack))
        {
            if(listOut != nullptr)
            {
                for(auto entry : recStack)
                {
                    if(entry.second)
                        (*listOut).push_back(entry.first);
                } 
            }
            return true;
        }
    }
    return false;
}

bool Graph::CheckCommerciallyConnectedFast()
{
    Graph simpleG;

    unordered_map<int ,list<Connection>> mapToUse;

    if(GetSCCGraph(adjMap.begin()->first, &simpleG, true))
    {
        // simpleG.printGraph();
        
        mapToUse = (simpleG).getAdjMap();    
    }
    else
    {
        mapToUse = adjMap;
    }
    //OLHAR PARA OUTPUTG
    std::list<int> checkList;
    stack<int> checkStack;
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
        {
            checkList.push_front(mapEntry.first);
            checkStack.push(mapEntry.first);
        }

    }
    if(checkList.size() == 1)
    {
        return true;
    }

    while (!checkStack.empty())
    {
        int entry = checkStack.top();
        checkStack.pop();
        for(auto otherEntry : checkList)
        {
            if(otherEntry == entry)
                continue;
            bool isConnected = false;
            for(auto conn: mapToUse[entry])
            {

                if(conn.getDest() == otherEntry)
                {
                    isConnected = true;
                    break;
                }
            }
            if(!isConnected)
                return false;
        }
        checkList.remove(entry);
    }
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

void Graph::aggregateV(list<int> vertList)
{

    int root = vertList.front();
    for(auto vert : vertList)
    {
        redirectMap[vert] = root;

    }
}

void Graph::connectVtoList(int src, list<Connection> connList)
{
    
    if (adjMap[src].size() == 0)
        numVertices++; 

    for(auto entry: connList)
    {
        int oldDest = entry.getDest();
        int newDest = redirectMap[oldDest];
        entry.setDest(newDest);
    }
    this->adjMap[src] = connList;
}

