//
// Created by rafae on 06/03/2019.
//

#ifndef STATEMACHINE_REPEAT_H
#define STATEMACHINE_REPEAT_H

#include "../StateMachine.h"

using sm::StateMachine;
using sm::StateOutputTuple;

namespace sm {
    namespace operators {

        template<typename T>
        class RepeatState {
        public:
            RepeatState(const unsigned int n, const T s): count{n}, state{s} {}

            unsigned int count = 0;
            T state;
        };

        template<typename T_I, typename T_S, typename T_O>
        class Repeat: public StateMachine<T_I, RepeatState<T_S>, T_O> {
        public:
            using SM_T = StateMachine<T_I, T_S, T_O>;
            using T_RS = RepeatState<T_S>;

            Repeat(const SM_T& sm, unsigned int n) :
                    StateMachine<T_I, T_RS, T_O>{ {0, sm.getInitialState()} }, _sm{sm}, _n{n} {}

            T_RS advanceIfDone(unsigned int counter, T_S state) const {
                while(_sm.done(state) && !done({counter, state})) {
                    counter++;
                    state = _sm.getInitialState();
                }

                return { counter, state };
            };

            StateOutputTuple<T_RS, T_O>
            getNextValues(const T_RS& state, const T_I& inp) const override {
                auto next = _sm.getNextValues(state.state, inp);

                return {
                    advanceIfDone(state.count, next.s),
                    next.o
                };
            };

            bool done(const T_RS& state) const override {
                return state.count == _n;
            };

        private:
            const SM_T& _sm;
            const unsigned int _n;
        };
    }
}

#endif //STATEMACHINE_REPEAT_H
