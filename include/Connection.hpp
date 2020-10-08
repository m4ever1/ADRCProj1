#pragma once

class Connection 
{
    int dest;
    int type;
public:
    Connection(int, int);
    void setType(int);
    int getType();
    void setDest(int);
    int getDest();
    int getReciprocalType();
    friend bool operator== (const Connection&, const Connection&);
    ~Connection();
};