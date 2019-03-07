//
// Created by rafae on 06/10/2018.
//

#ifndef STATEMACHINE_PARALLEL_H
#define STATEMACHINE_PARALLEL_H

#include "../StateMachine.h"

using sm::StateMachine;
using sm::StateOutputTuple;

namespace sm {
    namespace operators {
        template<typename T_I1, typename T_I2>
        class ParallelInputTuple {
        public:
            ParallelInputTuple(T_I1 i1, T_I2 i2): sm1Input{i1}, sm2Input{i2} {}

            T_I1 sm1Input;
            T_I2 sm2Input;
        };

        template <typename T_S1, typename T_S2>
        class ParallelStateTuple {
        public:
            ParallelStateTuple(T_S1 s1, T_S2 s2): sm1State{s1}, sm2State{s2} {}

            T_S1 sm1State;
            T_S2 sm2State;
        };

        template  <typename T_O1, typename T_O2>
        class ParallelOutputTuple {
        public:
            ParallelOutputTuple(T_O1 o1, T_O2 o2): sm1Out{o1}, sm2Out{o2} {}

            T_O1 sm1Out;
            T_O2 sm2Out;
        };

        template<class T_I1, class T_S1, class T_O1, class T_I2, class T_S2, class T_O2>
        class Parallel2:
                public StateMachine<
                        ParallelInputTuple<T_I1, T_I2>,
                        ParallelStateTuple<T_S1, T_S2>,
                        ParallelOutputTuple<T_O1, T_O2>
                > {
        public:
            using T_SM1 = StateMachine<T_I1, T_S1, T_O1>;
            using T_SM2 = StateMachine<T_I2, T_S2, T_O2>;

            using T_I = ParallelInputTuple<T_I1, T_I2>;
            using T_S = ParallelStateTuple<T_S1, T_S2>;
            using T_O = ParallelOutputTuple<T_O1, T_O2>;

            Parallel2(const T_SM1 sm1, const T_SM2 sm2):
                    StateMachine<T_I, T_S, T_O>({sm1.getInitialState(), sm2.getInitialState()}),
                    _sm1{sm1},
                    _sm2{sm2}
            {};

            StateOutputTuple<T_S, T_O>
            getNextValues(const T_S &state, const T_I &inp) const override {
                auto sm1Next = _sm1.getNextValues(state.sm1State, inp.sm1Input);
                auto sm2Next = _sm2.getNextValues(state.sm2State, inp.sm2Input);

                return {
                    { sm1Next.s, sm2Next.s },
                    { sm1Next.o, sm2Next.o }
                };
            };

        private:
            const T_SM1 &_sm1;
            const T_SM2 &_sm2;
        };

        template<class T_SM1, class T_SM2>
        auto make_parallel2(const T_SM1 sm1, const T_SM2 sm2) {
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
        class Parallel:
                public StateMachine<
                        T_I,
                        ParallelStateTuple<T_S1, T_S2>,
                        ParallelOutputTuple<T_O1, T_O2>
                > {
        public:
            using T_SM1 = StateMachine<T_I, T_S1, T_O1>;
            using T_SM2 = StateMachine<T_I, T_S2, T_O2>;

            using T_S = ParallelStateTuple<T_S1, T_S2>;
            using T_O = ParallelOutputTuple<T_O1, T_O2>;

            Parallel(const T_SM1 sm1, const T_SM2 sm2):
                StateMachine<T_I, T_S, T_O> (
                    {sm1.getInitialState(), sm2.getInitialState()}
                ),
                _sm1{sm1},
                _sm2{sm2}
                {};

            StateOutputTuple getNextValues(const T_S &state, const T_I& inp) const override {
                auto sm1Next = _sm1.getNextValues(state.sm1State, inp);
                auto sm2Next = _sm2.getNextValues(state.sm2State, inp);

                return {
                    { sm1Next.s, sm2Next.s },
                    { sm1Next.o, sm2Next.o }
                };
            }

        private:
            const T_SM1 _sm1;
            const T_SM2 _sm2;
        };

        template<class T_SM1, class T_SM2>
        auto make_parallel(const T_SM1 sm1, const T_SM2 sm2) {
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
                sm1, sm2
            };
        };
    }
}
#endif //STATEMACHINE_PARALLEL_H
