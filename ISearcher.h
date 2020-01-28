#ifndef EX4_ISEARCHER_H
#define EX4_ISEARCHER_H

#include "Searchable.h"

template <class Solution, class T>

class ISearcher {
public:

    virtual Solution search(Searchable<T> *) = 0;

    virtual int getNumberOfNodesEvaluated() = 0;

};

#endif //EX4_ISEARCHER_H
