
#include "io.hpp"




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
string fileIO::readLine()// returns a string containing the line, if EOF/ERROR returns NULL
{
    string line;
    if(this->file.is_open())
    {
        if(getline(this->file, line))
            return line;
        else
            return "";
    }
    else
    {
        std::cerr << "FILE IS CLOSED\n"; 
        return(NULL);
    }
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
