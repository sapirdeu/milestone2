#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include <iostream>
#include <sstream>
#include "CacheMap.h"
#include "CacheManager.h"

using namespace std;

class FileCacheManager : public CacheManager<string, string> {

public:

    // the method returns true if the problem exists in the cache map, otherwise false.
    virtual bool isSolExists(string prob) {

        unordered_map<string, string> *probToSol = CacheMap::loadCacheFile()->getProbToSol();

        return probToSol->count(prob);
//        if (probToSol->count(problem) == 0) {
//            return false;
//        }
//        return true;
    }

    // the method receives a problem and returns its solution from the map.
    virtual string getSol(string prob) {
        unordered_map<string, string> *cashMap = CacheMap::loadCacheFile()->getProbToSol();
        //stringstream stringstream1;
        //stringstream1 << problem;
//        if (!cashMap->count(problem)) {
//            __throw_logic_error("the solution does not exist");
//        }
        if (isSolExists(prob)) {
            return cashMap->at(prob);
        }
        return "";
    }

    // the method saves a problem and its solution in the cache map.
    virtual void saveSol(string prob, string sol) {
        //cout << prob <<endl;
        unordered_map<string, string> *cashMap = CacheMap::loadCacheFile()->getProbToSol();
        cashMap->insert(pair<string, string>(prob, sol));
    }
};


#endif //EX4_FILECACHEMANAGER_H
