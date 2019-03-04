//
// Created by rafae on 06/10/2018.
//

#ifndef STATEMACHINE_POSITIVE_H
#define STATEMACHINE_POSITIVE_H

#include "StateMachine.h"
#include <tuple>
#include <iostream>

using sm::StateMachine;
using  sm::StateOutputTuple;

class Positive: public StateMachine<int, int> {
public:
    Positive(): StateMachine(0) {};
    StateOutputTuple<int, int> getNextValues(const int &state, const int &inp) const override {
        return { inp, inp };
    };
};

#endif //STATEMACHINE_POSITIVE_H
