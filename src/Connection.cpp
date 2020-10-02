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
Connection::~Connection() {

}