//
// Created by rafae on 06/10/2018.
//

#ifndef STATEMACHINE_NEGATIVE_H
#define STATEMACHINE_NEGATIVE_H

#include "StateMachine.h"
#include <tuple>
#include <iostream>

using std::tuple;
using std::make_tuple;
using std::tie;
using std::cout;
using std::endl;

using sm::StateMachine;

class Negative: public StateMachine<int, int> {
public:
    Negative(): StateMachine(0) {};
    tuple<int, int> getNextValues(const int &state, const int &inp) const override {
        cout << "Negative: " << inp << endl;
        return make_tuple(inp, inp);
    };
};

#endif //STATEMACHINE_NEGATIVE_H
