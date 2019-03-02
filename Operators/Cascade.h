//
// Created by rafae on 05/09/2018.
//

#ifndef STATEMACHINE_CASCADE_H
#define STATEMACHINE_CASCADE_H

#include "../StateMachine.h"
#include <iostream>
#include <tuple>

using std::tuple;
using std::make_tuple;
using std::tie;
using std::cout;
using std::endl;
using sm::StateMachine;

namespace sm {
    namespace operators {
        template<typename T_I1, typename T_S1, typename T_O1, typename T_I2, typename T_S2, typename T_O2>
        class Cascade : public StateMachine<T_I1, tuple<T_S1, T_S2>, T_O2> {
        public:
            using M1_T = StateMachine<T_I1, T_S1, T_O1>;
            using M2_T = StateMachine<T_I2, T_S2, T_O2>;
            using S_T = tuple<T_S1, T_S2>;

            Cascade(M1_T &m1, M2_T &m2) : StateMachine <T_I1, S_T, T_O2>(
                    make_tuple(m1.getInitialState(), m2.getInitialState())
            ), _m1 {m1}, _m2 {m2} {}

            tuple <S_T, T_O2>
            getNextValues(const S_T &state, const T_I1 &inp) const override {
                T_S1 m1State, m1NewState;
                T_S2 m2State, m2NewState;
                T_O1 m1Out;
                T_O2 m2Out;

                tie(m1State, m2State) = state;

                tie(m1NewState, m1Out) = _m1.getNextValues(m1State, inp);
                tie(m2NewState, m2Out) = _m2.getNextValues(m2State, m1Out);

                return make_tuple(
                    make_tuple(m1NewState, m2NewState),
                    m2Out
                );
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
