//
// Created by rafae on 05/09/2018.
//

#ifndef STATEMACHINE_SWITCH_H
#define STATEMACHINE_SWITCH_H

#include "../StateMachine.h"
#include <iostream>
#include <tuple>
#include <functional>

using std::tuple;
using std::make_tuple;
using std::tie;
using std::cout;
using std::endl;
using std::function;

using sm::StateMachine;

namespace sm {
    namespace operators {
        template<class T_I, class T_S1, class T_S2, class T_O>
        class Switch: public StateMachine<T_I, tuple<T_S1, T_S2>, T_O> {
        public:
            using T_SM1 = StateMachine<T_I, T_S1, T_O>;
            using T_SM2 = StateMachine<T_I, T_S2, T_O>;
            using T_S = tuple<T_S1, T_S2>;

            Switch(function<bool(const T_I&)> cond, T_SM1 &sm1, T_SM2 &sm2):
                StateMachine<T_I, T_S, T_O>(make_tuple(sm1.getInitialState(), sm2.getInitialState())),
                _sm1{sm1},
                _sm2{sm2},
                _cond{cond} {}

            tuple<T_S, T_O> getNextValues(const T_S &state, const T_I &inp) const override {
                T_S1 m1State, m1NextState;
                T_S2 m2State, m2NextState;
                T_O m1Out, m2Out;

                tie(m1State, m2State) = state;

                if(_cond(inp)) {
                    tie(m1NextState, m1Out) = _sm1.getNextValues(m1State, inp);
                    return make_tuple(make_tuple(m1NextState, m2State), m1Out);
                } else {
                    tie(m2NextState, m2Out) = _sm2.getNextValues(m2State, inp);
                    return make_tuple(make_tuple(m1State, m2NextState), m2Out);
                }
            };

        private:
            const T_SM1 &_sm1;
            const T_SM2 &_sm2;
            const function<bool(const T_I&)> _cond;
        };

        template<class T_C, class T_SM1, class T_SM2>
        auto make_switch(T_C cond, T_SM1 &sm1, T_SM2 &sm2) {
            return Switch <
                typename T_SM1::input_type,
                typename T_SM1::state_type,
                typename T_SM2::state_type,
                typename T_SM2::output_type> {
                    cond, sm1, sm2};
        };
    }
}

#endif //STATEMACHINE_SWITCH_H
