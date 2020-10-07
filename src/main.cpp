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
    Graph graphObj;
    string str;
    int src, dest, type;
    while((str = fileObj.readLine()) != "EOF")
    {
        sscanf(str.c_str(), "%d %d %d\n", &src, &dest, &type);
        graphObj.addConnection(src, dest, type);
    }
    graphObj.printGraph();
    std::cout << "Number of vertices = " << graphObj.getNumVertices() << std::endl;

    return 0;
}