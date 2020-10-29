#include "utils.hpp"

pair<int, int> keyWithLargestValue(unordered_map<int, int> map)
{
    int largest = 0;
    pair<int, int> ret;
    for(auto entry : map)
    {
        if(entry.second > largest)
        {
            largest = entry.second;
            ret = entry;
        }
    }
    return ret;
}
