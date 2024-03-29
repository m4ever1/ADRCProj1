
#include "Io.hpp"

fileIO::fileIO(string fileName_)
{
    this->fileName = fileName_;
}
void fileIO::openFile()
{
    try
    {
        this->file.open(this->fileName);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
string fileIO::readLine()// returns a string containing the line, if EOF returns "EOF" string
{
    string line;
    if(this->file.is_open())
    {
        if(getline(this->file, line))
            return line;
        else
            return "EOF";
    }
    else
    {
        std::cerr << "FILE IS CLOSED\n"; 
        return(NULL);
    }
}

void fileIO::outputToFile(Graph G)
{
    ofstream outfile;
    
    outfile.open("./input/generated.txt");
    for(auto mapEntry : G.getAdjMap())
    {
        for(auto conn : mapEntry.second)
        {
            outfile << mapEntry.first << " " << conn.getDest() << " " << conn.getType() << std::endl;
        }

    }
    outfile.close();
}

fileIO::~fileIO()
{
    try
    {
        this->file.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
