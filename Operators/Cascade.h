//
// Created by rafae on 05/09/2018.
//

#ifndef STATEMACHINE_CASCADE_H
#define STATEMACHINE_CASCADE_H

#include "../StateMachine.h"

using sm::StateMachine;
using sm::StateOutputTuple;

namespace sm {
    namespace operators {
        // Container for storing the states of the constituent machines
        template<typename T_S1, typename T_S2>
        class CascateState {
        public:
            CascateState(T_S1 s1, T_S2 s2): m1State{s1}, m2State{s2} {}
            T_S1 m1State;
            T_S2 m2State;
        };

        template<typename T_I1, typename T_S1, typename T_O1, typename T_I2, typename T_S2, typename T_O2>
        class Cascade : public StateMachine<T_I1, struct cascadeState<>, T_O2> {
        public:
            using M1_T = StateMachine<T_I1, T_S1, T_O1>;
            using M2_T = StateMachine<T_I2, T_S2, T_O2>;
            using S_T = CascateState<T_S1, T_S2>;

            Cascade(M1_T &m1, M2_T &m2) : StateMachine <T_I1, S_T, T_O2>(
                    {m1.getInitialState(), m2.getInitialState()}
            ), _m1 {m1}, _m2 {m2} {}

            StateOutputTuple<S_T, T_O2>
            getNextValues(const S_T &state, const T_I1 &inp, S_T& nextState) const override {
                T_S1 m1State = state.m1State;
                T_S2 m2State = state.m2State;

                auto m1Next = _m1.getNextValues(m1State, inp);
                auto m2Next = _m2.getNextValues(m2State, m1Next.o);

                return {
                        {m1Next.s, m2Next.s},
                        m2Next.o
                };
            }

        private:
            M1_T &_m1;
            M2_T &_m2;
        };

        template<class T_SM1, class T_SM2>
        auto make_cascade(T_SM1 &sm1, T_SM2 &sm2) {
            return Cascade <
                typename T_SM1::input_type,
                typename T_SM1::state_type,
                typename T_SM1::output_type,
                typename T_SM2::input_type,
                typename T_SM2::state_type,
                typename T_SM2::output_type> {
                        sm1, sm2};
        };
    }
}

#endif //STATEMACHINE_CASCADE_H
