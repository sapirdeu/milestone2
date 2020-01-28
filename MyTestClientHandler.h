#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include <iostream>
//#include "StringReverser.h"
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include "ClientHandler.h"
#include "ConnectionManager.h"
#include "Solver.h"
#include "CacheManager.h"

using namespace std;
using namespace connection_manager;

class MyTestClientHandler : public ClientHandler {
private:
    CacheManager<string,string>* cm;
    Solver<string,string>* solver;

public:
    MyTestClientHandler(Solver<string,string>* reverseSolver,CacheManager<string,string>* newCM ) {
        this->solver=reverseSolver;
        this->cm=newCM;
    }

    // the function runs the client.
    virtual void runClient(ClientSocket client) {

        int finish = 1;
        size_t len;
        while (1 == finish) {
            string outputClient = client.read(1024);
            if (string::npos != outputClient.find("end")) {
                len = outputClient.find("end");
                outputClient =outputClient.substr(0,len);
                finish = 0;
                if(outputClient!="") {
                    string ans = this->solver->solve(outputClient);
                    client.write(ans);
                }
            } else{
                string ans = this->solver->solve(outputClient);
                client.write(ans);
            }
        }
        client.close();
    }
};


#endif //EX4_MYTESTCLIENTHANDLER_H
