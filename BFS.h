#ifndef EX4_BFS_H
#define EX4_BFS_H

#include<iostream>
#include <list>
#include <queue>
#include <set>
#include <vector>
#include <unordered_set>
#include "ISearcher.h"
#include "Searcher.h"
#include "BackTrace.h"

using namespace std;

template <class T>
class BFS : public ISearcher<string,T> {
private:
    BackTrace<T> bt;
    int nodesEvaluatedNum = 0;

public:

    virtual int getNumberOfNodesEvaluated() {
        return this->nodesEvaluatedNum;
    }

    //the function search is running the algorithm of BFS
    string search(Searchable<T> *matrix) {
        queue<State<T> *> statesQ;
        // this vector keep the states that we evaluated
        vector<State<T> *> seenStates;

        // keep the initial State and the goal State
        State<T>* init = matrix->getInitialState();
        State<T>* goal = matrix->getGoalState();

        statesQ.push(init);
        seenStates.push_back(init);
        double newCost;
        // keep the current state
        State<T> *currState;
        // keep the states that can be reached from the current state
        vector<State<T>*> successors;
        // while statesQ isn't empty
        while (statesQ.empty() == 0) {
            currState = statesQ.front();

            // if we reach to the goal state then we print the path anf finish
            if (currState == goal) {
                return this->bt.backTrace(currState,matrix, this->getNumberOfNodesEvaluated());
            }
            this->nodesEvaluatedNum++;

            // successors  keep the neighbors of currState
            successors = matrix->getAllPossibleStates(currState);
            statesQ.pop();

            // pass through all the successors of currState
            for (State<T> *successor: successors) {
                if (isSeenState(successor,seenStates) == 0) {
                    newCost = currState->getCost() + successor->getValue();
                    successor->setCost(newCost);
                    successor->setCameFrom(currState);
                    seenStates.push_back(successor);
                    statesQ.push(successor);
                }
            }
        }
        return "";
    }

    // the function check if we already see "state"
    int isSeenState(State<T> *state, vector<State<T> *> seenStates){
        int flag = 0;
        for (auto currState : seenStates) {
            if (state==currState) {
                flag = 1;
                return flag;
            }
        }
        return flag;
    }
};

#endif //EX4_BFS_H
