#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include <list>
#include <unordered_set>
#include <math.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "Searchable.h"
#include "ISearcher.h"
#include "Searcher.h"
#include "BackTrace.h"


using namespace std;

template <class T>
class Astar : public Searcher<string,T> {
private:
    BackTrace<T> bt;

public:

    // huristic function
    double huristic(State<pair<int, int>>* node1, State<pair<int, int>>* node2) {
        return abs(node2->getIndex().second- node1->getIndex().second) +
               abs(node2->getIndex().first- node1->getIndex().first);
    }

    // the function search is running the algorithm of A*
    string search(Searchable<T>* matrix) {
        this->restart();
        // keep the initial State and the goal State
        State<T>* init = matrix->getInitialState();
        State<T>* goal = matrix->getGoalState();
        // calcualte g+h and change the cost od the state
        double g = init->getCost();
        double h = huristic(init,goal);
        init->setCost(g+h);
        this->addToOpen(init);
        unordered_set<State<T>*> closedList;

        // while the priority queue is not empty
        while(this->getPriorityQueueSize()>0) {
            // pop the state with the lowest f (f=g+h) from the openList
            State<T>* currState = this->popOpenList();
            h = huristic(currState,goal);
            currState->setCost(currState->getCost()-h);
            closedList.insert(currState);

            // if the current state that we pop from the openList is the goal
            // stat, then we can print the path and finish
            if(currState == goal) {
                return this->bt.backTrace(currState,matrix, this->getNumberOfNodesEvaluated());
            }

            // keep all the successors of currState in a vector
            vector<State<T>*> successors = matrix->getAllPossibleStates(currState);
            // for each successor of currState
            for(State<T>* successor: successors) {
                g = successor->getValue() + currState->getCost();
                h = huristic(successor,goal);
                // if the successor is neither in the closedList nor
                // in the openList
                if((closedList.count(successor)==0) && (!this->contains(successor))) {
                    // calculate the cost of the current successor amd it's
                    // father and add the successor to the openList
                    successor->setCost(g+h);
                    successor->setCameFrom(currState);
                    this->addToOpen(successor);
                } else if(closedList.count(successor)==0 &&
                          (successor->getCameFrom()->getCost() >
                           currState->getCost())) {
                    // if the current successor isn't in the closedList but
                    // in the openList and we found a better cost (through
                    // currState), so we update the cost and the father
                    successor->setCost(g+h);
                    successor->setCameFrom(currState);
                }
            }
        }
        return "";
    }
};

#endif //EX4_ASTAR_H
