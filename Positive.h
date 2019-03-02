//
// Created by rafae on 06/10/2018.
//

#ifndef STATEMACHINE_POSITIVE_H
#define STATEMACHINE_POSITIVE_H

#include "StateMachine.h"
#include <tuple>
#include <iostream>

using std::tuple;
using std::make_tuple;
using std::tie;
using std::cout;
using std::endl;

using sm::StateMachine;

class Positive: public StateMachine<int, int> {
public:
    Positive(): StateMachine(0) {};
    tuple<int, int> getNextValues(const int &state, const int &inp) const override {
        cout << "Positive: " << inp << endl;
        return make_tuple(inp, inp);
    };
};

#endif //STATEMACHINE_POSITIVE_H
