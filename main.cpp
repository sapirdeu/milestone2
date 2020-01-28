#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
//#include "MySerialServer.h"
//#include "StringReverser.h"
#include "CacheManager.h"
#include "State.h"
#include "MatrixSearchable.h"
#include "ProblemSolver.h"
#include "MyClientHandler.h"
#include "MyTestClientHandler.h"
#include "MyParallelServer.h"
#include "FileCacheManager.h"
#include "Astar.h"
#include "BestFirstSearch.h"
#include "BFS.h"
#include "DFS.h"
#include "Main.h"

using namespace server_side;
using namespace std;

CacheMap *CacheMap::cacheObj = NULL;
unordered_map<string, string> *CacheMap::probToSol = NULL;

int main(int argc, char **argv) {
    int port;

    // check that the input it valid
    if (argc > 2) {
        printf("Invalid input");
        exit(4);
    } else {
        if (argc == 1) {
            port = 5600;
        } else {
            port = stoi(argv[1]);
        }
    }

    // run the main.
    boot::Main *runMain = new boot::Main();
    runMain->main(port);

    delete runMain;
    return 0;
}
