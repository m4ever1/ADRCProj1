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

    // std::cout << "**************** GRAPH ****************" << std::endl;
    // std::cout << "Number of vertices = " << graphObj.getNumVertices() << std::endl;

    bool commerciallyConnected = false;
    bool commerciallyConnectedFast = false;
    srand(time(NULL));
    Generator gen;
    // while(commerciallyConnected == commerciallyConnectedFast)
    // {
        genGraph.reset();
        genGraph = graphObj;
        // genGraph = gen.generateGraph((rand() % 1001));
        std::cout << "**************** GRAPH ****************" << std::endl;
        std::cout << "Number of vertices = " << genGraph.getNumVertices() << std::endl;
        
        // Check if graph is connect
        start = timeSinceEpochMillisec();
        bool connected = genGraph.CheckConnected();
        end = timeSinceEpochMillisec();
        std::cout << std::endl;
        std::cout << "TIME CHECKING CONNECTED" << std::endl;
        std::cout << ((end - start)/1000) << std::endl;
        std::cout << std::endl;

        // Check if graph is biconnected
        // start = timeSinceEpochMillisec();
        // bool biConnected = genGraph.CheckBiConnected();
        // end = timeSinceEpochMillisec();
        // std::cout << std::endl;
        // std::cout << "TIME CHECKING BICONNECTED (BRUTE FORCE)" << std::endl;
        // std::cout << ((end - start)/1000) << std::endl;
        // std::cout << std::endl;

        start = timeSinceEpochMillisec();
        bool biConnectedFast = genGraph.CheckBiConnectedFast(nullptr);
        end = timeSinceEpochMillisec();
        std::cout << std::endl;
        std::cout << "TIME CHECKING BICONNECTED (FAST)" << std::endl;
        std::cout << ((end - start)/1000) << std::endl;
        std::cout << std::endl;

        // Check if graph is commercially acyclic
        start = timeSinceEpochMillisec();
        list<int> cycleQuestionMark;
        bool cyclic = genGraph.CheckCyclic(&cycleQuestionMark);
        end = timeSinceEpochMillisec();
        std::cout << std::endl;
        std::cout << "TIME CHECKING CYCLIC (SLOW)" << std::endl;
        std::cout << ((end - start)/1000) << std::endl;
        std::cout << std::endl;

        // Check if graph is commercially connected
        start = timeSinceEpochMillisec();
        commerciallyConnected = genGraph.CheckCommerciallyConnected(connected);
        end = timeSinceEpochMillisec();
        std::cout << std::endl;
        std::cout << "TIME CHECKING CC (SLOW)" << std::endl;
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
        // std::cout << "************* CHECK BICONNECTED *************" << std::endl;
        // if(biConnected)
        //     std::cout << "BICONNECTED" << std::endl;
        // else
        //     std::cout << "NOT BICONNECTED" << std::endl;
        std::cout << "************* CHECK BICONNECTED FAST *************" << std::endl;
        if(biConnectedFast)
            std::cout << "BICONNECTED" << std::endl;
        else
            std::cout << "NOT BICONNECTED" << std::endl;

        std::cout << "******** CHECK COMMERCIALLY ACYCLIC *********" << std::endl;
        if(cyclic) 
        {
            std::cout << "CYCLIC" << std::endl;
            std::cout << "Cycle: " << std::endl;

            for (auto i : cycleQuestionMark)
            {
                std::cout << i << std::endl;
            }
            
        }
        else
            std::cout << "COMMERCIALLY ACYCLIC" << std::endl;
        
        std::cout << "******* CHECK COMMERCIALLY CONNECTED ********" << std::endl;
        if(commerciallyConnected)
            std::cout << "COMMERCIALLY CONNECTED" << std::endl;
        else
            std::cout << "NOT COMMERCIALLY CONNECTED" << std::endl;


        std::cout << "***** CHECK COMMERCIALLY CONNECTED FAST *****" << std::endl;
        if(commerciallyConnectedFast)
            std::cout << "COMMERCIALLY CONNECTED" << std::endl;
        else
            std::cout << "NOT COMMERCIALLY CONNECTED" << std::endl;

    // }
    // fileObj.outputToFile(genGraph);
    
    return 0;
}