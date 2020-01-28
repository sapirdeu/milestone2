#ifndef EX4_SERVER_H
#define EX4_SERVER_H

#include "ClientHandler.h"

namespace server_side {

    class Server {

    public:
        // receives port and client handler and open connection to serve the client.
        virtual void open(int, ClientHandler *) = 0;

        // terminates the connection.
        virtual void stop(int) = 0;
    };
}


#endif //EX4_SERVER_H
