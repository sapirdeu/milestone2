#ifndef EX4_MAIN_H
#define EX4_MAIN_H
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

namespace boot {
    class Main {
    public:
        //main
        int main(int port) {

            CacheManager<string,string> *cacheM = new FileCacheManager();
            MyParallelServer myPS;

            ISearcher<string,pair<int,int>> *searcher = new Astar<pair<int,int>>();
            //ISearcher<string,pair<int,int>> *searcher = new BestFirstSearch<pair<int, int>>();
             //ISearcher<string,pair<int,int>> *searcher = new BFS<pair<int,int>>();
            //ISearcher<string,pair<int,int>> *searcher = new DFS<pair<int,int>>();

            Solver<Searchable<pair<int,int>> *,string> *solver =
                    new ProblemSolver<string,pair<int,int>>(searcher);

            ClientHandler *clientH = new MyClientHandler<pair<int,int>>(solver,cacheM);
            myPS.open(port,clientH);

            delete cacheM;
            delete searcher;
            delete solver;
            delete clientH;
            delete CacheMap::loadCacheFile();

            return 0;
        }
    };
};

#endif //EX4_MAIN_H
