#include "Io.hpp"
#include "Graph.hpp"

int main(int argc, char **argv) 
{
    if(argc < 2)
    {
        std::cout << "Error: No file argument\nUsage: " << argv[0] << " [FILE]\n";
        return(0);
    }
    fileIO fileObj(argv[1]);
    fileObj.openFile();

    Graph graphObj, graphReplicaObj;
    string str;
    int src, dest, type;

    while((str = fileObj.readLine()) != "EOF")
    {
        sscanf(str.c_str(), "%d %d %d\n", &src, &dest, &type);
        graphObj.addConnection(src, dest, type);
    }

    graphObj.printGraph();

    std::cout << "Number of vertices = " << graphObj.getNumVertices() << std::endl;

    // Check if graph is connect
    if(graphObj.CheckConnected())
        std::cout << "CONNECTED" << std::endl;
    else
        std::cout << "NOT CONNECTED" << std::endl;

    // Check if graph is biconnected
    if(graphObj.CheckBiConnected())
        std::cout << "BICONNECTED" << std::endl;
    else
    {   
        std::cout << "NOT BICONNECTED" << std::endl;
    }

    // Check if graph is biconnected
    if(graphObj.CheckAcyclic())
        std::cout << "ACYCLIC" << std::endl;
    else
    {   
        std::cout << "CYCLIC" << std::endl;
    }
           
    return 0;
}