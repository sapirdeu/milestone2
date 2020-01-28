#ifndef EX4_BESTFIRSTSEARCH_H
#define EX4_BESTFIRSTSEARCH_H


#include <unordered_set>
#include <vector>
#include "ISearcher.h"
#include "Searcher.h"
#include "BackTrace.h"

template <class T>
class BestFirstSearch : public Searcher<string,T> {
private:
    BackTrace<T> bt;
public:

    //the function search is running the algorithm of BestFirstSearch
    string search(Searchable<T>* matrix) {
        this->restart();
        // keep the initial State and the goal State
        State<T>* init = matrix->getInitialState();
        State<T>* goal = matrix->getGoalState();
        this->addToOpen(init);
        unordered_set<State<T>*> closedList;

        State<T>* currState;
        double newCost;
        while(this->getPriorityQueueSize()>0) {
            currState = this->popOpenList();
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
                // if the successor is neither in the closedList nor
                // in the openList
                newCost = currState->getCost() + successor->getValue();
                if( (closedList.count(successor)==0) && (!this->contains(successor))) {
                    successor->setCost(newCost);
                    successor->setCameFrom(currState);
                    this->addToOpen(successor);
                } else if(closedList.count(successor)==0 && (successor->getCameFrom()->getCost() > currState->getCost())) {
                    // if the current successor isn't in the closedList but
                    // in the openList and we found a better cost (through
                    // currState), so we update the cost and the father
                    successor->setCost(newCost);
                    successor->setCameFrom(currState);
                }
            }
        }
        return "";
    }
};


#endif //EX4_BESTFIRSTSEARCH_H
