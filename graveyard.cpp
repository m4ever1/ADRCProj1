// std::list<int>::iterator it;
// std::list<int>::iterator aux;
// for(it = checkList.begin(); it != checkList.end(); ++it)
// {
//     if(*it == entry)
//         continue;
//     if(conn.getDest() == *it)
//     {
//         break;
//     }
//     if ( == checkList.end())
//     {
//         return false;
//     }
// }

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
    // simpleG->printGraph();


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