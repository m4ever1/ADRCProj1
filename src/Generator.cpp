#include <stdlib.h>     /* srand, rand */
#include "Generator.hpp"
using namespace std;


Graph Generator::generate(int nrNodes)
{
    for(int i = 0; i < nrNodes; i++)
    {
        genGraph.addVertice(i);
    }
    srand (time(NULL));
    for(int i = 0; i < nrNodes; i++)
    {
        int numConn = rand()  % nrNodes + 1;

        for(int j = 0; j < numConn; j++)
        {
            int typeRnd = rand() % 3 + 1;
            int dest = rand() % nrNodes + 1;
            genGraph.addConnection(i, dest, typeRnd);
            int recpType = Connection::getReciprocalType(typeRnd);
            genGraph.addConnection(dest, i, recpType);
        }
    }
    return(genGraph);
}