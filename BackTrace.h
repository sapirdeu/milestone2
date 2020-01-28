#ifndef EX4_BACKTRACE_H
#define EX4_BACKTRACE_H

#include <vector>
#include <list>
#include <iostream>
#include "State.h"
#include "Searchable.h"

using namespace std;

template <class T>
class BackTrace{
public:
    // the function print the path from the init to the goal states
    string backTrace(State<T> *goal, Searchable<T> *matrix, int statesNum) {
        cout<<"Num of states evaluated: "<<statesNum<<endl;
        State<T> *init = matrix->getInitialState();
        string path = "";

        while (!(*goal==*init)) {
            pair<int,int> name = goal->getIndex();
            pair<int,int> parentName = goal->getCameFrom()->getIndex();

            int parentI = parentName.first;
            int parentJ = parentName.second;
            int childI = name.first;
            int childJ = name.second;

            if (childI > parentI) {
                path = "Down (" + to_string(int(goal->getCost()+ init->getValue())) + "), " +path;
            } else if (childI < parentI) {
                path = "Up (" + to_string(int(goal->getCost()+ init->getValue())) + "), "+path;
            } else if (childJ > parentJ) {
                path = "Right (" + to_string(int(goal->getCost()+ init->getValue())) + "), "+ path;
            } else if (childJ < parentJ) {
                path = "Left (" + to_string(int(goal->getCost()+ init->getValue())) + "), "+path;
            }
            goal = goal->getCameFrom();
        }

        cout<< endl << matrix->getGoalState()->getCost()+ init->getValue()<< endl;

        return path.substr(0, path.size()-2);
    }
};


#endif //EX4_BACKTRACE_H
