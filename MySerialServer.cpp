#include "MySerialServer.h"

using namespace connection_manager;

// serverFunc is the function that the server run in a new thread
void serverFunc(bool* stop,ClientHandler* clientH, mutex* newMutex,
                ServerSocket server,ClientSocket client) {

    while ((*stop) == false) {
        if (-2 != client.getSocketFD()) {
            clientH->runClient(client, newMutex);
            client = server.accept();
        }else{
            *stop=true;
        }
    }
    server.close();

}

// the function open a new server the listen to one client
void MySerialServer::open(int port, ClientHandler* clientH) {
    mutex* newMutex=new mutex();
    // create setver that listen to a client
    ServerSocket server(port);
    server.listen(SOMAXCONN);
    server.timeOutSetting(0, 0);

    // the server accept the client
    ClientSocket client=server.accept();
    server.timeOutSetting(120, 0);
    *(this->shouldExit)= false;

    // run the function that the server need to run as a differnet thread
    thread serverThread(serverFunc,this->shouldExit,clientH,newMutex, server,client);
    serverThread.detach();
    if(*(this->shouldExit)) {
        close(server.getSocketFD());
    }
}

// the function close the socket of the server
void MySerialServer::stop(int socketServer) {
    close(socketServer);
}