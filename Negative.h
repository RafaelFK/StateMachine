//
// Created by rafae on 06/10/2018.
//

#ifndef STATEMACHINE_NEGATIVE_H
#define STATEMACHINE_NEGATIVE_H

#include "StateMachine.h"
#include <tuple>
#include <iostream>


using sm::StateMachine;
using sm::StateOutputTuple;

class Negative: public StateMachine<int, int> {
public:
    Negative(): StateMachine(0) {};
    StateOutputTuple<int, int> getNextValues(const int &state, const int &inp) const override {
        return { inp, inp };
    };
};

#endif //STATEMACHINE_NEGATIVE_H
