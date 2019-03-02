//
// Created by rafae on 05/09/2018.
//

#ifndef STATEMACHINE_DELAY_H
#define STATEMACHINE_DELAY_H

#include "../StateMachine.h"
#include <tuple>
#include <iostream>

using std::tuple;
using std::make_tuple;
using std::tie;
using std::cout;
using std::endl;

using sm::StateMachine;

namespace sm{
    namespace elementary {
        template<typename T>
        class Delay: public StateMachine<T, T> {
        public:
            Delay(T initialState): StateMachine<T, T>(initialState) {};
            tuple<T, T> getNextValues(const T &state, const T &inp) const override {
                return make_tuple(inp, state);
            };
        };
    }
}

#endif //STATEMACHINE_DELAY_H
