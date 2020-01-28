#ifndef EX4_SERVERSOCKET_H
#define EX4_SERVERSOCKET_H

#include "ConnectionManager.h"
#include "ClientSocket.h"

using namespace connection_manager;

class ServerSocket {
    Socket sSocket;
public:

    // ctor
    ServerSocket(int port) {
        int size = 1;
        setsockopt(sSocket.socketFD, SOL_SOCKET, SO_REUSEADDR, &size, sizeof(int));
        sockaddr_in addr_in;
        addr_in.sin_family = AF_INET;
        addr_in.sin_port = htons(port);
        addr_in.sin_addr.s_addr = INADDR_ANY;

        // binding the port to the socket
        if (-1 == bind(sSocket.socketFD, (sockaddr *) &addr_in, sizeof(addr_in))) {
            throw system_error(error_code(errno, generic_category()), "Error: cannot bind.");
        }
    }

    void listen(int clientsNum) {
        // if failed listening.
        if (-1 == ::listen(sSocket.socketFD, clientsNum)) {
            throw system_error(error_code(errno, generic_category()), "Error: cannot listen.");
        }
    }

    // setting the timeout.
    void timeOutSetting(int seconds, int useconds = 0) {
        sSocket.timeOutSetting(seconds, useconds);
    }

    int getSocketFD() {
        return this->sSocket.getSocketFD();
    }

    // accepting clients
    ClientSocket accept() {
        sockaddr_in addr;
        socklen_t size = sizeof(addr);
        int cSocketFD = ::accept(sSocket.socketFD, (sockaddr *) &addr, &size);
        if (cSocketFD < 0) {
            // timeout error
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                return ClientSocket(TIMEOUT);
            } else {
                throw system_error(error_code(errno, generic_category()), "Error: cannot accept.");
            }
        }

        Socket cSocket(cSocketFD);
        // setting timeout.
        cSocket.timeOutSetting(0);
        return cSocket;
    }

    // closing the connection.
    void close() {
        sSocket.close();
    }
};

#endif //EX4_SERVERSOCKET_H
