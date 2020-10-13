#include "Connection.hpp"

Connection::Connection(int destination, int type) {
    this->dest = destination;
    this->type = type;
}
void Connection::setType(int type) {
    this->type = type;
}

int Connection::getType() {
    return type;
}

void Connection::setDest(int dest) {
    this->dest = dest;
}

int Connection::getDest() {
    return dest;
}

int Connection::getReciprocalType(int type) 
{
    switch (type)
    {
    case 1:
        return(3);
    case 2:
        return(2);
    default:
        return(1);
    }
}

bool operator== (const Connection& lhs, const Connection& rhs) 
{
    return(lhs.dest == rhs.dest && lhs.type == rhs.type);
}


Connection::~Connection() {

}