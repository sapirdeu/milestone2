#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

#include <mutex>
#include "Solver.h"
#include "Searchable.h"
#include "ConnectionManager.h"
#include "ServerSocket.h"
#include "ClientSocket.h"

using namespace connection_manager;

class ClientHandler {
public:
    // the function is responsible for the communication of the client
    virtual void runClient(ClientSocket, mutex *) = 0 ;
};


#endif //EX4_CLIENTHANDLER_H
