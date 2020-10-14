#include "Io.hpp"
#include "Graph.hpp"
#include "Generator.hpp"

int main(int argc, char **argv) 
{
    if(argc < 2)
    {
        std::cout << "Error: No file argument\nUsage: " << argv[0] << " [FILE]\n";
        return(0);
    }
    fileIO fileObj(argv[1]);
    fileObj.openFile();

    Graph graphObj, genGraph;

    string str;
    int src, dest, type;

    while((str = fileObj.readLine()) != "EOF")
    {
        sscanf(str.c_str(), "%d %d %d\n", &src, &dest, &type);
        graphObj.addConnection(src, dest, type);
    }
    graphObj.printGraph();
    std::cout << "Number of vertices = " << graphObj.getNumVertices() << std::endl;

    Generator gen;
    genGraph = gen.generateGraph(5);
    // Check if graph is connect
    std::cout << "Is graph CONNECTED?" << std::endl;
    if(graphObj.checkConnected())
    {
        std::cout << "YES" << std::endl;
    }
    else
    {
        std::cout << "no" << std::endl;
    }
    
    std::cout << std::endl;

    genGraph.printGraph();
    std::cout << "Number of vertices = " << genGraph.getNumVertices() << std::endl;
    std::cout << "Is graph CONNECTED?" << std::endl;
    if(genGraph.checkConnected())
    {
        std::cout << "YES" << std::endl;
    }
    else
    {
        std::cout << "no" << std::endl;
    }
    // Check if graph is biconnected

    

    return 0;
}