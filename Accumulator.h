//
// Created by rafae on 05/09/2018.
//

#ifndef STATEMACHINE_ACCUMULATOR_H
#define STATEMACHINE_ACCUMULATOR_H

#include <tuple>
#include <iostream>
#include "StateMachine.h"

using std::tuple;
using std::make_tuple;
using std::tie;
using std::cout;
using std::endl;

using sm::StateMachine;

class Accumulator: public StateMachine<int, int> {
public:
    Accumulator(int initialState): StateMachine(initialState) {};

    tuple<int, int> getNextValues(const int &state, const int &inp) const override {
        return make_tuple(state + inp, state);
    };

    void step(const int &inp) override {
        int nextState, out;
        tie(nextState, out) = getNextValues(_state, inp);
        _state = nextState;

        cout << "OUT: " << out << endl;
    }
};

#endif //STATEMACHINE_ACCUMULATOR_H
