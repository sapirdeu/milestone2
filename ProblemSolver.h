#ifndef EX4_PROBLEMSOLVER_H
#define EX4_PROBLEMSOLVER_H

#include "ISearcher.h"
#include "Solver.h"
#include "Searchable.h"

template<class Solution, class T>
class ProblemSolver : public Solver<Searchable<T> *, Solution> {
private:
    ISearcher<Solution, T> *searcher;
public:

    // ctor
    ProblemSolver(ISearcher<Solution, T> *newS) {
        this->searcher = newS;
    }

    // receives a problem and solves it.
    virtual Solution solve(Searchable<T> *problem) {
        Solution sol = searcher->search(problem);
        return (sol);
    }
};


#endif //EX4_PROBLEMSOLVER_H
