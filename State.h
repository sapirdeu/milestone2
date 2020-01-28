#ifndef EX4_STATE_H
#define EX4_STATE_H

#include <iostream>

using namespace std;

template<class T>
class State {

private:

    T index; // the index of the state as a pair of int: i,j
    double cost = 0; // cost so far
    double value = 0; // the value in the matrix
    State<T> *cameFrom = nullptr;

public:
    // ctors
    State<T>();

    State(T newIndex) {
        this->index = newIndex;
    }

    T getIndex() const {
        return this->index;
    }

    double getValue() {
        return this->value;
    }

    void setValue(double newVal) {
        this->value = newVal;
    }

    double getCost() {
        return this->cost;
    }

    void setCost(double newCost) {
        this->cost = newCost;
    }

    State<T> *getCameFrom() {
        return this->cameFrom;
    }

    void setCameFrom(State<T> *newCameFrom) {
        this->cameFrom = newCameFrom;
    }

// operators overloading
    ostream &operator<<(ostream &os) {
        os << this->index << this->cost;
    }

    friend ostream &operator<<(ostream &os, State<T> inf) {
        return inf << (os);
    }

    bool operator<(State<T> second) {
        return (this->cost < second.cost);
    }

    bool operator==(State<T> second) const {
        return (this->index == second.index);
    }

    bool operator>(State<T> second) {
        return (this->cost > second.cost);
    }

};

#endif //EX4_STATE_H
