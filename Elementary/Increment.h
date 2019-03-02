//
// Created by rafae on 02/03/2019.
//

#ifndef STATEMACHINE_INCREMENT_H
#define STATEMACHINE_INCREMENT_H

#include "../StateMachine.h"
#include <type_traits>
#include <tuple>

using sm::StateMachine;
using std::is_arithmetic;
using std::tuple;

namespace sm {
    namespace elementary {
        template<typename T>
        class Increment: public StateMachine<T, T> {
// Ensure that T is an arithmetic type
            static_assert(
                    is_arithmetic<T>::value,
                    "Invalid instantiation. Class Increment requires an arithmetic type"
            );

        public:
            Increment(const T incr): StateMachine<T, T>({}), incr{incr} {}
            tuple<T, T> getNextValues(const T& state, const T& inp) const  override {
                return make_tuple(state, inp + incr);
            }

        private:
            const T incr;
        };
    }
}

#endif //STATEMACHINE_INCREMENT_H
