//
// Created by rafae on 02/03/2019.
//

#ifndef STATEMACHINE_PUREFUNCTION_H
#define STATEMACHINE_PUREFUNCTION_H

#include <cstddef>
#include <functional>
#include <tuple>
#include "../StateMachine.h"

using sm::StateMachine;
using sm::StateOutputTuple;

namespace sm {
    namespace elementary {
        template<typename I, typename O>
        class PureFunction : public StateMachine<I, nullptr_t, O> {
        public:
            using F_T = O(*)(I);

            PureFunction(F_T f) :
                StateMachine<I, nullptr_t, O>(nullptr),
                f {f} {}

            StateOutputTuple<nullptr_t, O> getNextValues(const nullptr_t& state, const I& inp) const override {
                return {nullptr, f(inp)};
            }

        private:
            F_T f;
        };
    }
}
#endif //STATEMACHINE_PUREFUNCTION_H
