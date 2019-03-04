//
// Created by rafae on 05/09/2018.
//

#ifndef STATEMACHINE_ACCUMULATOR_H
#define STATEMACHINE_ACCUMULATOR_H

#include <tuple>
#include <type_traits>
#include "../StateMachine.h"

using sm::StateMachine;
using sm::StateOutputTuple;

namespace sm {
    namespace elementary {
        template<typename T>
        class Accumulator: public StateMachine<T, T> {
        /*static_assert(
             is_arithmetic<T>::value,
             "Invalid instantiation. Class Accumulator requires an arithmetic type"
        );*/
        public:
            Accumulator(T initialState): StateMachine<T, T>(initialState) {};

            StateOutputTuple<T, T> getNextValues(const T &state, const T &inp) const override {
                return { state + inp, state };
            };
        };
    }
}

#endif //STATEMACHINE_ACCUMULATOR_H
