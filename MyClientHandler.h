#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H

#include <sstream>
#include <mutex>
#include "ClientHandler.h"
#include "Solver.h"
#include "ISearcher.h"
#include "CacheManager.h"
#include "MatrixSearchable.h"
#include "ProblemSolver.h"

using namespace std;

using namespace connection_manager;

template<class T>
class MyClientHandler : public ClientHandler {

private:
    Solver<Searchable<T> *, string> *solver;
    CacheManager<string, string> *cm;
public:

    MyClientHandler(Solver<Searchable<T> *, string> *solver1,
                    CacheManager<std::string, std::string> *cm) {
        this->solver = solver1;
        this->cm = cm;
    }

    // the function is responsible for the comuunication with the client
    virtual void runClient(ClientSocket client, mutex *newMutex) {
        string path;
        string clientInput = "";
        client.timeOutSetting(0, 0);
        int finished = 0;
        while (finished == 0) {
            clientInput += client.read(1024);
            if (clientInput.find("end") != string::npos) {
                clientInput = clientInput.substr(0, clientInput.find("end"));
                finished = 1;
                if (clientInput != "") {
                    path = createInputServer(newMutex, clientInput);
                    client.write(path);
                }
            }
        }
        client.close();
    }

    // the function create te path to send for the server
    string createInputServer(mutex *newMutex, string clientInput) {
        vector<string> currVec;
        string target;
        string start;
        Searchable<T> *searchable;
        string path;

        clientInput = deleteSpaces(clientInput);
        newMutex->lock();
        if (this->cm->isSolExists(clientInput)) {
            cout << "Solution exists in the cache." << endl;
            path = cm->getSol(clientInput);
            newMutex->unlock();
        } else {
            newMutex->unlock();
            currVec = stringSplitted(clientInput, "\n");
            target = currVec.back();
            currVec.pop_back();
            start = currVec.back();
            currVec.pop_back();
            searchable = new MatrixSearchable(currVec, start, target);
            newMutex->lock();
            path = this->solver->solve(searchable);
            this->cm->saveSol(searchable->to_strings(), path);
            newMutex->unlock();
            delete searchable;
        }
        path = deleteEnd(path);
        return path;
    }

    string deleteEnd(string path) {
        if (path[path.length() - 1] == '\n') {
            path.erase(path.length() - 1, 1);
        }
        return path;
    }

    // the function split stInput by "splitBy"
    vector<string> stringSplitted(string stInput, string splitBy) {
        vector<string> newString;
        string currSplitted;
        size_t pos;
        size_t len;
        while (string::npos != stInput.find(splitBy)) {
            currSplitted = stInput.substr(0, stInput.find(splitBy));
            newString.push_back(currSplitted);
            pos = stInput.find(splitBy);
            pos += 1;
            len = stInput.length() - stInput.find(splitBy);
            stInput = stInput.substr(pos, len);
        }
        return newString;
    }

    // the function delete all the spaces from stInput
    string deleteSpaces(string &stInput) {
        string output = "";
        for (int i = 0; i < stInput.length(); i++) {
            if (' ' != stInput[i]) {
                output += stInput[i];
            }
        }
        return output;
    }

};

#endif //EX4_MYCLIENTHANDLER_H
