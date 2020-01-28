#ifndef EX4_CACHEMAP_H
#define EX4_CACHEMAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

#define FILE_NAME "cacheFile.txt"
#define SEPERATOR "#"
#define SEPERATOR_LINE "#\n"
#define LINE_SEPERATOR_LINE "\n#\n"


using namespace std;

class CacheMap {

    static unordered_map<string, string> *probToSol;

    static CacheMap *cacheObj;

public:

    // the method loads the cache file into the cache map
    static inline CacheMap *loadCacheFile() {

        // if the cache map wasn't created before, we create it now
        if (cacheObj == nullptr) {

            probToSol = new unordered_map<string, string>();
            cacheObj = new CacheMap();
            ifstream cacheFile(FILE_NAME);
            int seperateFlag = 1;
            string oneLine, data, prob, sol;

            // open the file
            if (!cacheFile.is_open()) {
                cacheFile.open(FILE_NAME, fstream::app | fstream::in);
            }

            // if failed openning the file
            if (!cacheFile.is_open()) {
                throw "Error: cannot open the cache file.";
            }

            // read the file line by line and add the problem and their solution to the map
            while (getline(cacheFile, oneLine)) {

                // if haven't reached $ we're still reading the problem
                if (oneLine != SEPERATOR) {
                    data += oneLine + "\n";
                } else if (seperateFlag) {
                    // reached $ so now we save the problem in prob
                    prob = data;
                    data = "";
                    seperateFlag = 0;
                } else {
                    // save the solution in sol
                    sol = data;
                    data = "";
                    seperateFlag++;

                    // add the problem and solution to the map
                    probToSol->insert(pair<string, string>(prob, sol));
                    //probToSol->insert({prob, sol});
                }
            }
            cacheFile.close();
        }
        return cacheObj;
    }

//    inline void setValue(string key, string val) {
//        probToSol->insert({key, val});
//    }

    // get the cache map
    inline unordered_map<string, string> *getProbToSol() {
        return probToSol;
    }

    // dtor
    ~CacheMap() {

        ofstream cacheFile;
        cacheFile.open(FILE_NAME);

        // saving the cache map to the cache file
        for (auto item : *this->probToSol) {
            int len = item.second.length() - 1;
            string prob = item.first;
            string sol = item.second;
            if (sol[len] != '\n') {
                cacheFile << prob << SEPERATOR_LINE << sol << LINE_SEPERATOR_LINE;
            } else {
                cacheFile << prob << SEPERATOR_LINE << sol << SEPERATOR_LINE;
            }
        }
        cacheFile.close();
    }
};


#endif //EX4_CACHEMAP_H
