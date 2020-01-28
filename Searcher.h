#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include "ISearcher.h"
#include "Solver.h"
#include <queue>
#include "State.h"
#include "PriorityHeap.h"

template <class Solution, class T>
class Searcher : public ISearcher<Solution,T> {
private:
    PriorityHeap<T> priorityHeap;
    int evaluateNodes=0;
protected:
    virtual State<T>* popOpenList() {
        evaluateNodes++;
        State<T>* n=priorityHeap.top();
        priorityHeap.pop();
        return n;

    }
    virtual void addToOpen(State<T>* node) {
        this->priorityHeap.push(node);
    }
    virtual bool contains( State<T>* node) {
        return this->priorityHeap.contains(node);
    }
public:
    Searcher() {
        evaluateNodes=0;
    }

    virtual int getPriorityQueueSize() {
        return this->priorityHeap.size();
    }

    int getNumberOfNodesEvaluated() { //not virtual in porpuse
        return this->evaluateNodes;
    }

    virtual void updateCostOfState(State<T>* nodeToSetValueTo, double cost) {
        priorityHeap.updateCostOfState(nodeToSetValueTo, cost);
    }

    virtual Solution search(Searchable<T>* isearchable) = 0;

    virtual void restart (){
        this->evaluateNodes=0;
        while (this->priorityHeap.size()> 0) {
            this->priorityHeap.pop();
        }
    }

};


#endif //EX4_SEARCHER_H
