#include "io.hpp"

int main(int argc, char **argv) 
{
    if(argc < 2)
    {
        std::cout << "Error: No file argument\nUsage: " << argv[0] << " [FILE]\n";
        return(0);
    }
    fileIO fileObj = fileIO(argv[1]);
    fileObj.openFile();
    string str;
    while((str = fileObj.readLine()) != "EOF")
    {
        std::cout << str << std::endl;
    }
    return 0;
}