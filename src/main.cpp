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
    Generator gen;
    genGraph = gen.generateGraph(4);

    std::cout << "Number of vertices = " << graphObj.getNumVertices() << std::endl;

    // Check if graph is connect
    if(graphObj.CheckBiConnected())
    {
        std::cout << "YES" << std::endl;
    }
    else
    {
        std::cout << "no" << std::endl;
    }
    
    std::cout << "\n\n" << std::endl;

    genGraph.printGraph();
    // Check if graph is biconnected

    

    return 0;
}