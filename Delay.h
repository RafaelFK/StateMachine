//
// Created by rafae on 05/09/2018.
//

#ifndef STATEMACHINE_DELAY_H
#define STATEMACHINE_DELAY_H

#include "StateMachine.h"
#include <tuple>
#include <iostream>

using std::tuple;
using std::make_tuple;
using std::tie;
using std::cout;
using std::endl;

using sm::StateMachine;

class Delay: public StateMachine<int, int, int> {
public:
    Delay(int initialState): StateMachine(initialState) {};
    tuple<int, int> getNextValues(const int &state, const int &inp) const override {
        return make_tuple(inp, state);
    };
    void step(const int &inp) override {
        int nextState, out;
        tie(nextState, out) = getNextValues(_state, inp);
        _state = nextState;

        cout << "OUT: " << out << endl;
    }
};
#endif //STATEMACHINE_DELAY_H
