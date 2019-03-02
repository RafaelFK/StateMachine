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
using std::function;
using std::tuple;
using std::make_tuple;

namespace sm {
    namespace elementary {
        template<typename I, typename O>
        class PureFunction : public StateMachine<I, nullptr_t, O> {
        public:
            PureFunction(function<O(const I&)> f) :
                StateMachine<I, nullptr_t, O>(nullptr),
                f {f} {}

            tuple<nullptr_t, O> getNextValues(nullptr_t state, const I& inp) const override {
                return make_tuple(nullptr, f(inp));
            }

        private:
            function<O(const I&)> f;
        };
    }
}
#endif //STATEMACHINE_PUREFUNCTION_H
