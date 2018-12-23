//
// Created by rafae on 06/10/2018.
//

#ifndef STATEMACHINE_PARALLEL_H
#define STATEMACHINE_PARALLEL_H

#include "../StateMachine.h"
#include <iostream>
#include <tuple>
#include <functional>
#include <type_traits>

using std::tuple;
using std::make_tuple;
using std::tie;
using std::cout;
using std::endl;
using std::function;
using std::is_same;

using sm::StateMachine;

namespace sm {
    namespace operators {
        template<class T_I1, class T_S1, class T_O1, class T_I2, class T_S2, class T_O2>
        class Parallel2: public StateMachine<tuple<T_I1, T_I2>, tuple<T_S1, T_S2>, tuple<T_O1, T_O2>> {
        public:
            using T_SM1 = StateMachine<T_I1, T_S1, T_O1>;
            using T_SM2 = StateMachine<T_I2, T_S2, T_O2>;

            using T_I = tuple<T_I1, T_I2>;
            using T_S = tuple<T_S1, T_S2>;
            using T_O = tuple<T_O1, T_O2>;

            Parallel2(const T_SM1 &sm1, const T_SM2 &sm2):
                    StateMachine<T_I, T_S, T_O>(make_tuple(sm1.getState(), sm2.getState())),
                    _sm1{sm1},
                    _sm2{sm2}
            {};

            tuple<T_S, T_O>
            getNextValues(const T_S &state, const T_I &inp) const override {
                T_I1 m1Inp;
                T_I2 m2Inp;
                T_S1 m1State, m1NewState;
                T_S2 m2State, m2NewState;
                T_O1 m1Out;
                T_O2 m2Out;

                tie(m1State, m2State) = state;
                tie(m1Inp, m2Inp) = inp;

                tie(m1NewState, m1Out) = _sm1.getNextValues(m1State, m1Inp);
                tie(m2NewState, m2Out) = _sm2.getNextValues(m2State, m2Inp);

                return make_tuple(
                    make_tuple(m1NewState, m2NewState),
                    make_tuple(m1Out, m2Out)
                );
            };

            void step(const T_I &inp) override {
                T_S nextState;
                T_O out;
                tie(nextState, out) = getNextValues(getState(), inp);
                setState(nextState);
            }

        private:
            const T_SM1 &_sm1;
            const T_SM2 &_sm2;
        };

        template<class T_SM1, class T_SM2>
        auto make_parallel2(const T_SM1 &sm1, const T_SM2 &sm2) {
            return Parallel2<
                T_SM1::input_type,
                T_SM1::state_type,
                T_SM1::output_type,
                T_SM2::input_type,
                T_SM2::state_type,
                T_SM2::output_type> {
                sm1,
                sm2
            };
        };

        template<class T_I, class T_S1, class T_S2, class T_O1, class T_O2>
        class Parallel: public Parallel2<T_I, T_S1, T_O1, T_I, T_S2, T_O2> {
        public:
            using T_SM1 = StateMachine<T_I, T_S1, T_O1>;
            using T_SM2 = StateMachine<T_I, T_S2, T_O2>;

            Parallel(const T_SM1 &sm1, const T_SM2 &sm2):
                Parallel2<T_I, T_S1, T_O1, T_I, T_S2, T_O2> (
                    sm1, sm2
                ) {};
        };

        template<class T_SM1, class T_SM2>
        auto make_parallel(const T_SM1 &sm1, const T_SM2 &sm2) {
            static_assert(
                T_SM1::input_type != T_SM2::input_type,
                "Parallel: State machines should have the same input type!"
            );
            return Parallel<
                T_SM1::input_type,
                T_SM1::state_type,
                T_SM2::state_type,
                T_SM1::output_type,
                T_SM2::output_type> {
                sm1, sm2;
            };
        };
    }
}
#endif //STATEMACHINE_PARALLEL_H
