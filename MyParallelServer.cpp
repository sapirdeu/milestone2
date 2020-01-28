#include "MyParallelServer.h"

#define TIME_OUT -2

// threads vector
vector<thread> threads;


// the functions that runs a specific client.
void threadFunc(mutex *newMutex, ClientSocket client, ClientHandler *newCH) {
    newCH->runClient(client, newMutex);
}


// open server that listens parallely to clients and handles them.
void MyParallelServer::open(int port, ClientHandler *ch) {

    // server socket
    ServerSocket server(port);
    server.listen(SOMAXCONN);
    server.timeOutSetting(0, 0);

    // client socket
    ClientSocket client = server.accept();
    server.timeOutSetting(120, 0);

    // when we handle a client only one at a time
    // so we change the boolean flag and lock it with mutex.
    *(this->shouldStop) = false;
    mutex *newMutex = new mutex();
    this->newMutex = newMutex;

    // while client is being handled.
    while (*this->shouldStop == 0) {
        if (TIMEOUT == client.getSocketFD()) {
            *shouldStop = true;
        } else {
            //creating the thread.
            thread newThread(threadFunc, newMutex, client, ch);
            threads.push_back(move(newThread));
            // accepting a new client.
            client = server.accept();
        }
    }

    // close the connection between the current client to the server.
    stop(server.getSocketFD());
}

// the method receives socketFD number and closes the connection.
void MyParallelServer::stop(int socketFD) {
    close(socketFD);

    // run the last thread, wait for it and when it finishes pop it from the threads vector.
    while (threads.size() > 0) {
        threads.back().join();
        threads.pop_back();
    }
}