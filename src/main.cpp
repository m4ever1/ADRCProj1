#include "Io.hpp"
#include "Graph.hpp"
#include "Generator.hpp"
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
    std::cout << "Number of vertices = " << graphObj.getNumVertices() << std::endl;

    bool commerciallyConnectedFast = false;

    genGraph = graphObj;
    
    // Check if graph is connect
    start = timeSinceEpochMillisec();
    bool connected = genGraph.CheckConnected();
    end = timeSinceEpochMillisec();
    std::cout << std::endl;
    std::cout << "TIME CHECKING CONNECTED" << std::endl;
    std::cout << ((end - start)/1000) << std::endl;
    std::cout << std::endl;

    start = timeSinceEpochMillisec();
    pair<int,int> bridge;
    bool biConnectedFast = genGraph.CheckBiConnectedFast(&bridge);
    end = timeSinceEpochMillisec();
    std::cout << std::endl;
    std::cout << "TIME CHECKING BICONNECTED" << std::endl;
    std::cout << ((end - start)/1000) << std::endl;
    std::cout << std::endl;

    // Check if graph is commercially acyclic
    start = timeSinceEpochMillisec();
    list<int> cycleQuestionMark;
    bool cyclic = genGraph.CheckCyclic(&cycleQuestionMark);
    end = timeSinceEpochMillisec();
    std::cout << std::endl;
    std::cout << "TIME CHECKING CYCLIC" << std::endl;
    std::cout << ((end - start)/1000) << std::endl;
    std::cout << std::endl;

    // Check if graph is commercially connected (new algorithm)
    start = timeSinceEpochMillisec();
    commerciallyConnectedFast = genGraph.CheckCommerciallyConnectedFast();
    end = timeSinceEpochMillisec();
    std::cout << std::endl;
    std::cout << "TIME CHECKING CC (FAST)" << std::endl;
    std::cout << ((end - start)/1000) << std::endl;
    std::cout << std::endl;
    
    std::cout << "************** CHECK CONNECTED **************" << std::endl;
    if(connected)
        std::cout << "CONNECTED" << std::endl;
    else
        std::cout << "NOT CONNECTED" << std::endl;
    std::cout << "************* CHECK BICONNECTED *************" << std::endl;
    if(biConnectedFast)
        std::cout << "BICONNECTED" << std::endl;
    else
    {
        std::cout << "NOT BICONNECTED" << std::endl;
        std::cout << "BRIDGE AT " << bridge.first << " to " << bridge.second << std::endl;
    }

    std::cout << "******** CHECK COMMERCIALLY ACYCLIC *********" << std::endl;
    if(cyclic) 
    {
        std::cout << "CYCLIC" << std::endl;
        std::cout << "Cycle at: " << std::endl;

        for (auto i : cycleQuestionMark)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    else
        std::cout << "COMMERCIALLY ACYCLIC" << std::endl;


    std::cout << "***** CHECK COMMERCIALLY CONNECTED *****" << std::endl;
    if(commerciallyConnectedFast)
        std::cout << "COMMERCIALLY CONNECTED" << std::endl;
    else
        std::cout << "NOT COMMERCIALLY CONNECTED" << std::endl;

    return 0;
}