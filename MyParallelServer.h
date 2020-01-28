#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <strings.h>
#include <vector>
#include "Server.h"
#include "CacheMap.h"

using namespace std;
using namespace server_side;


class MyParallelServer : public Server {
private:
    bool *shouldStop;
    mutex* newMutex;

public:
    //ctor
    MyParallelServer() {
        this->shouldStop= new bool(false);
    }

    virtual void open(int, ClientHandler*);
    virtual void stop(int);

    //dtor
    ~MyParallelServer(){
        delete this->newMutex;
        delete this->shouldStop;
    }
};

#endif //EX4_MYPARALLELSERVER_H
