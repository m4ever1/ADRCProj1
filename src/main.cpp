#include "Io.hpp"
#include "Graph.hpp"
#include "Generator.hpp"
#include "SimpGraph.hpp"
#include <list>
#include <chrono>

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main(int argc, char **argv) 
{
    using namespace std::chrono;
    if(argc < 2)
    {
        std::cout << "Error: No file argument\nUsage: " << argv[0] << " [FILE]\n";
        return(0);
    }
    

    double start, end;
    
    start = timeSinceEpochMillisec();

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

    end = timeSinceEpochMillisec();
    std::cout << std::endl;
    std::cout << "TIME READING FILE" << std::endl;
    std::cout << ((end - start)/1000) << std::endl;
    std::cout << std::endl;

    std::cout << "**************** GRAPH ****************" << std::endl;
    // graphObj.printGraph();
    std::cout << "Number of vertices = " << graphObj.getNumVertices() << std::endl;

    // Generator gen;
    // genGraph = gen.generateGraph(5);

    // Check if graph is connect
    start = timeSinceEpochMillisec();
    bool connected = graphObj.CheckConnected();
    end = timeSinceEpochMillisec();

    std::cout << std::endl;
    std::cout << "TIME CHECKING CONNECTED" << std::endl;
    std::cout << ((end - start)/1000) << std::endl;
    std::cout << std::endl;
    // Check if graph is biconnected
    /* 
        TODO: OUTPUT BRIDGE
    */
    start = timeSinceEpochMillisec();
    bool biConnected = graphObj.CheckBiConnected();
    end = timeSinceEpochMillisec();
    std::cout << std::endl;
    std::cout << "TIME CHECKING BICONNECTED" << std::endl;
    std::cout << ((end - start)/1000) << std::endl;
    std::cout << std::endl;
    // Check if graph is commercially acyclic
    /*
        TODO: OUTPUT PROVIDER-CUSTOMER CYCLE
    */
    start = timeSinceEpochMillisec();
    list<int> cicleQuestioMark;
    bool cyclic = graphObj.CheckCyclic(&cicleQuestioMark);
    end = timeSinceEpochMillisec();
    std::cout << std::endl;
    std::cout << "TIME CHECKING CYCLIC (SLOW)" << std::endl;
    std::cout << ((end - start)/1000) << std::endl;
    std::cout << std::endl;
    // Check if graph is commercially connected
    start = timeSinceEpochMillisec();
    bool commerciallyConnected = graphObj.CheckCommerciallyConnected(connected);
    end = timeSinceEpochMillisec();
    std::cout << std::endl;
    std::cout << "TIME CHECKING CC (SLOW)" << std::endl;
    std::cout << ((end - start)/1000) << std::endl;
    std::cout << std::endl;
    
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

    std::cout << "************ CHECK COMMERCIALLY ACYCLIC ************" << std::endl;
    if(cyclic)
        std::cout << "COMMERCIALLY CYCLIC" << std::endl;
    else
        std::cout << "ACYCLIC" << std::endl;
    
    std::cout << "**** CHECK COMMERCIALLY CONNECTED *****" << std::endl;
    if(commerciallyConnected)
        std::cout << "COMMERCIALLY CONNECTED" << std::endl;
    else
        std::cout << "NOT COMMERCIALLY CONNECTED" << std::endl;
           
    // graphObj.printGraph();

    
    Graph* cicle = new Graph;
    start = timeSinceEpochMillisec();
    bool ciclic = graphObj.CheckCyclicFast(cicle);
    end = timeSinceEpochMillisec();
    std::cout << std::endl;
    std::cout << "TIME CHECKING CYCLIC (FAST)" << std::endl;
    std::cout << ((end - start)/1000) << std::endl;
    std::cout << std::endl;

    // cicle->printGraph();
    if(ciclic)
    {
        std::cout << "Cyclic" << std::endl;
    }
    else
    {
        std::cout << "Not Cyclic" << std::endl;
    }
    start = timeSinceEpochMillisec();
    bool CC = graphObj.CheckCommerciallyConnectedFast();
    end = timeSinceEpochMillisec();
    std::cout << std::endl;
    std::cout << "TIME CHECKING CC (FAST)" << std::endl;
    std::cout << ((end - start)/1000) << std::endl;
    std::cout << std::endl;
    if(CC)
    {
        std::cout << "CC" << std::endl;
    }
    else
    {
        std::cout << "Not CC" << std::endl;
    }
    
    free(cicle);
    return 0;
}