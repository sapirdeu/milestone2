#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include <iostream>
#include <strings.h>
#include <vector>
#include <pthread.h>
#include <thread>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "Server.h"
#include "ConnectionManager.h"

using namespace std;

using namespace server_side;

class MySerialServer : public Server {
private:
    bool *shouldExit;
public:
    //ctor
    MySerialServer() {
        this->shouldExit= new bool(false);
    }
    virtual void open(int, ClientHandler*);
    virtual void stop(int);

};

#endif //EX4_MYSERIALSERVER_H
