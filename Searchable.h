#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H

#include <vector>
#include "State.h"

using namespace std;

template<class T>
class Searchable {
public:

    virtual State<T> *getInitialState() = 0;

    virtual State<T> *getGoalState() = 0;

    virtual vector<State<T> *> getAllPossibleStates(State<T> *s) = 0;

    virtual string to_strings() = 0;

    virtual ~Searchable() {}

};


#endif //EX4_SEARCHABLE_H
