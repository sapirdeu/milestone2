#ifndef EX4_PRIORITYHEAP_H
#define EX4_PRIORITYHEAP_H

#include <queue>
#include <iostream>
#include "State.h"

template<class Iter, class T>

// the method receives begin point and end point and value to find and returns
// the location of the value is exists otherwise returns the end.
Iter toFind(Iter begin, Iter end, const T &value) {
    while (begin != end) {
        if (*begin == value) {
            return begin;
        }
        begin++;
    }
    return end;
}

// the method returns true of x<y, otherwise false.
template<class T>
struct bigger : binary_function<T, T, bool> {
    bool operator()(const T &x, const T &y) const {
        if (x->getCost() > y->getCost()) {
            return true;
        }
        return false;
    }
};

// the class overrides the priority queue in order to implement priority heap.
template<typename T>
class PriorityHeap : public priority_queue<State<T> *, vector<State<T> *>, bigger<State<T> *>> {
public:


    // the method returns true if state exists in the collection otherwise false.
    bool contains(State<T> *state) const {
        auto it = toFind(this->c.begin(), this->c.end(), state);
        return (it != this->c.end());
    }

    // the method receives a state and new cost and update the cost
    void updateCostOfState(State<T> *toUpdate, double newCost) {
        State<T> *state;
        vector<State<T> *> statesToPush;

        // while there are still states in the heap
        while (this->size() > 0) {
            state = this->top();

            // if hasn't reached the wanted state- pop the top from the heap.
            if (!(*toUpdate == *state)) {
                statesToPush.push_back(state);
                this->pop();
            } else {
                // else, we reached to the wanted state- we update it, and push
                // the states we popped earlier back to the heap.
                state->setCost(newCost);
                for (State<T> *toPush : statesToPush) {
                    this->push(toPush);
                }
                break;
            }
        }
    }

};


#endif //EX4_PRIORITYHEAP_H
