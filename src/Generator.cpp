#include "Generator.hpp"

Graph Generator::generateGraph(int nrNodes)
{
    for(int i = 1; i < nrNodes + 1; i++)
    {
        genGraph.addVertice(i);
    }

    srand (time(NULL));
    for(int i = 1; i < nrNodes + 1; i++)
    {
        int numConn = rand() % 21;
        // std::cout << "\n" << numConn <<"\n" << std::endl;
        for(int j = 0; j < numConn; j++)
        {
            int typeRnd = rand() % 3 + 1;

            int dest = rand() % nrNodes + 1;
            if(dest != i && !genGraph.doesConnExist(i, dest))
            {
                genGraph.addConnection(i, dest, typeRnd);
                int recpType = Connection::getReciprocalType(typeRnd);
                genGraph.addConnection(dest, i, recpType);
            }
        }
    }
    return(genGraph);
}