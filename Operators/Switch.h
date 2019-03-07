//
// Created by rafae on 05/09/2018.
//

#ifndef STATEMACHINE_SWITCH_H
#define STATEMACHINE_SWITCH_H

#include "../StateMachine.h"

using sm::StateMachine;
using sm::StateOutputTuple;

namespace sm {
    namespace operators {
        // Container for storing the states of the constituent machines
        template<typename T_S1, typename T_S2>
        class SwitchState {
        public:
            SwitchState(T_S1 s1, T_S2 s2): m1State{s1}, m2State{s2} {}
            T_S1 m1State;
            T_S2 m2State;
        };

        template<typename T_I, typename T_S1, typename T_S2, typename T_O>
        class Switch: public StateMachine<T_I, SwitchState<T_S1, T_S2>, T_O> {
        public:
            using T_SM1 = StateMachine<T_I, T_S1, T_O>;
            using T_SM2 = StateMachine<T_I, T_S2, T_O>;
            using T_S = SwitchState<T_S1, T_S2>;
            using cond_t = bool(*)(T_I);

            Switch(cond_t cond, const T_SM1& sm1, const T_SM2& sm2):
                StateMachine<T_I, T_S, T_O>({sm1.getInitialState(), sm2.getInitialState()}),
                _sm1{sm1},
                _sm2{sm2},
                _cond{cond} {}

            StateOutputTuple<T_S, T_O> getNextValues(const T_S &state, const T_I &inp) const override {
                if(_cond(inp)) {
                    auto sm1Next = _sm1.getNextValues(state.m1State, inp);
                    return {{sm1Next.s, state.m2State}, sm1Next.o};
                } else {
                    auto sm2Next = _sm2.getNextValues(state.m2State, inp);
                    return {{state.m1State, sm2Next.s}, sm2Next.o};
                }
            };

        private:
            const T_SM1& _sm1;
            const T_SM2& _sm2;
            cond_t _cond;
        };

         template<typename T_I, typename T_SM1, typename T_SM2>
//        template<
//            template<typename T_I, typename T_S1, typename T_O> typename T_SM1,
//            template<typename T_I, typename T_S2, typename T_O> typename T_SM2
//        >
        auto make_switch(bool(*cond)(T_I), const T_SM1& sm1, const T_SM2& sm2) {
            /*static_assert(
                    typeid(T_SM1::input_type) != typeid(T_SM2::input_type),
                    "Switch: State machines should have the same input!"
            );
            /*static_assert(
                    typename T_SM1::output_type != typename T_SM2::output_type,
                    "Switch: State machines should have the same output!"
            );
            static_assert(
                    typename T_SM1::input_type != T_I,
                    "Switch: Predicate should take same type as state machines!"
            );*/
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
