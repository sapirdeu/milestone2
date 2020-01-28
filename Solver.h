#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

template <class Problem,class Solution>
class Solver {
public:

    // receives a problem and returns the solution to the problem
    virtual Solution solve(Problem) = 0;
};

#endif //EX4_SOLVER_H
