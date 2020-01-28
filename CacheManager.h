#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

template<class Problem, class Solution>
class CacheManager {
public:

    // the method returns true if the problem exists in the cache map, otherwise false.
    virtual bool isSolExists(Problem) = 0;

    // the method receives a problem and returns its solution from the map.
    virtual Solution getSol(Problem) = 0;

    // the method saves a problem and its solution in the cache map.
    virtual void saveSol(Problem, Solution) = 0;

};

#endif //EX4_CACHEMANAGER_H
