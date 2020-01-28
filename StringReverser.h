#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H

#include <iostream>
#include <bits/stdc++.h>
#include "Solver.h"

using namespace std;

class StringReverser : public Solver<std::string, std::string> {

public:

    // ctor
    StringReverser() {}

    // solves the problem- returns the reversed string
    virtual string solve(string problem) {
        reverse(problem.begin(), problem.end());
        return problem;
    }
};

#endif //EX4_STRINGREVERSER_H
