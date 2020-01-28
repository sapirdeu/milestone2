#ifndef EX4_MATRIXSEARCHABLE_H
#define EX4_MATRIXSEARCHABLE_H

#include "Searchable.h"

#define BLOCK -1
#define COMMA ","
#define NEWLINE "\n"

class MatrixSearchable : public Searchable<pair<int, int>> {
private:

    vector<State<pair<int, int>> *> matrix;
    State<pair<int, int>> *init;
    State<pair<int, int>> *goal;

public:

    MatrixSearchable(vector<string> &newMatrix, string &newInit, string &newGoal) {
        buildMatrix(newMatrix);
        buildState(newInit, 0);
        buildState(newGoal, 1);
    }

    // the method receives a state (either init or goal) and initialize the suitable member.
    // when mode is 0 we initialize the init, when the mode is 1 we initialize the goal.
    void buildState(string &state, int mode) {
        int len = state.length();
        string i, j;
        size_t find = state.find(COMMA);

        if (!(string::npos == find)) {
            i = state.substr(0, find);
            j = state.substr(find + 1, len - find);
            State<pair<int, int>> *node = findStateByIndex(pair<int, int>(stoi(i), stoi(j)));

            if (node == nullptr) {
                __throw_logic_error("Error: invalid input.");
            } else {
                if (mode == 0) {
                    this->init = node;
                } else if (mode == 1) {
                    this->goal = node;
                }
            }
        }
    }

    // the method builds the matrix.
    void buildMatrix(vector<string> &newMatrix) {
        int row = 0, col = 0;
        int index;
        int val;

        // initialize the matrix
        for (string line: newMatrix) {
            // pushing state by state into the matrix
            while (!(string::npos == line.find(COMMA))) {
                // creating the state and pushing it into the matrix
                State<pair<int, int>> *currState = new State<pair<int, int>>(pair<int, int>(row, col));
                string strVal = line.substr(0, line.find(COMMA));
                val = stoi(strVal);
                currState->setValue(val);

                this->matrix.push_back(currState);

                index = line.find((COMMA));
                int from = index + 1;
                int to = line.length() - index;
                line = line.substr(from, to);

                // progressing col to the next column
                col++;
            }

            // pushing the last state of the current line into the matrix (finishes with \n and not ,
            State<pair<int, int>> *state = new State<pair<int, int>>(pair<int, int>(row, col));
            val = stoi(line);
            state->setValue(val);

            this->matrix.push_back(state);

            // initialize column
            col = 0;
            // progressing row to the next line
            row++;
        }
    }

    State<pair<int, int>> *getGoalState() {
        return this->goal;
    }

    State<pair<int, int>> *getInitialState() {
        return this->init;
    }

    // the method receives a pair of int,int representing the index of a state
    // the method returns the state in this index
    State<pair<int, int>> *findStateByIndex(pair<int, int> index) {
        for (State<pair<int, int>> *currState :this->matrix) {
            if (index == currState->getIndex()) {
                return currState;
            }
        }
        return nullptr;
    }

    // the method returns a vector of the successors of state
    vector<State<pair<int, int>> *> getAllPossibleStates(State<pair<int, int>> *state) {
        vector<State<pair<int, int>> *> successors;

        for (State<pair<int, int>> *currState : this->matrix) {
            int currI = currState->getIndex().first;
            int currJ = currState->getIndex().second;

            int stateI = state->getIndex().first;
            int stateJ = state->getIndex().second;

            // if the value is -1 its blocked so continue to the next state
            if (currState->getValue() == BLOCK) {
                continue;
            } // if currState is a successor of state add it to the vector.
            else if ((currI == stateI &&
                      currJ + 1 == stateJ) || (currJ == stateJ && currI + 1 == stateI) ||
                     (currI == stateI && currJ - 1 == stateJ) || (currI - 1 == stateI &&
                                                                  currJ == stateJ)) {
                successors.push_back(currState);
            }
        }
        return successors;
    }


    // the string format of the MatrixSearchable
    virtual string to_strings() {

        string output;
        int i = 0;
        // adding the matrix to the output string
        for (State<pair<int, int>> *currState:this->matrix) {
            int currI = currState->getIndex().first;
            int currJ = currState->getIndex().second;
            int currVal = (int) currState->getValue();
            if (i != currI) {
                output += NEWLINE + to_string(currVal);
                i++;
            } else {
                if (i != 0 || currJ != 0) {
                    output += +COMMA + to_string(currVal);
                } else {
                    output += to_string(currVal);
                }
            }
        }

        // adding the init and goal to the output string
        output += NEWLINE + to_string(this->init->getIndex().first) + COMMA +
                  to_string(this->init->getIndex().second) + NEWLINE +
                  to_string(this->goal->getIndex().first) + COMMA +
                  to_string(this->goal->getIndex().second) + NEWLINE;
        return output;
    }


    // dtor
    ~MatrixSearchable() {
        for (State<pair<int, int>> *currState :this->matrix) {
            delete currState;
        }
    }

};

#endif //EX4_MATRIXSEARCHABLE_H
