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

    std::cout << "**************** GRAPH ****************" << std::endl;
    //graphObj.printGraph();
    std::cout << "Number of vertices = " << graphObj.getNumVertices() << std::endl;

    Generator gen;
    genGraph = gen.generateGraph(5);

    // Check if graph is connect
    bool connected = graphObj.CheckConnected();
    
    // Check if graph is biconnected
    /* 
        TODO: OUTPUT BRIDGE
    */
    bool biConnected = graphObj.CheckBiConnected();

    // Check if graph is commercially acyclic
    /*
        TODO: OUTPUT PROVIDER-CUSTOMER CYCLE
    */
    bool acyclic = !graphObj.CheckCyclic(nullptr);

    // Check if graph is commercially connected
    bool commerciallyConnected = graphObj.CheckCommerciallyConnected(connected);

    
    std::cout << "*********** CHECK CONNECTED ***********" << std::endl;
    if(connected)
        std::cout << "CONNECTED" << std::endl;
    else
        std::cout << "NOT CONNECTED" << std::endl;

    std::cout << "********** CHECK BICONNECTED **********" << std::endl;
    if(biConnected)
        std::cout << "BICONNECTED" << std::endl;
    else
        std::cout << "NOT BICONNECTED" << std::endl;

    std::cout << "************ CHECK ACYCLIC ************" << std::endl;
    if(acyclic)
        std::cout << "ACYCLIC" << std::endl;
    else
        std::cout << "CYCLIC" << std::endl;
    
    std::cout << "**** CHECK COMMERCIALLY CONNECTED *****" << std::endl;
    if(commerciallyConnected)
        std::cout << "COMMERCIALLY CONNECTED" << std::endl;
    else
        std::cout << "NOT COMMERCIALLY CONNECTED" << std::endl;
           

    return 0;
}