//
// Created by rafae on 05/09/2018.
//

#ifndef STATEMACHINE_STATEMACHINE_H
#define STATEMACHINE_STATEMACHINE_H

#include <tuple>
#include <array>

using std::tuple;
using std::make_tuple;
using std::tie;
using std::array;

namespace sm {
    template<typename T_INP, typename T_STATE, typename T_OUT = T_STATE>
    class StateMachine {
    public:
        StateMachine(T_STATE initialState) :
            _initialState{initialState}, _state{initialState} {}

        virtual tuple<T_STATE, T_OUT>
        getNextValues(const T_STATE &state, const T_INP &inp) const = 0;

        T_OUT step(const T_INP &inp) {
            T_STATE nextState;
            T_OUT out;
            tie(nextState, out) = getNextValues(_state, inp);
            setState(nextState);

            return out;
        }

        template<size_t N>
        array<T_OUT, N> transduce(const array<T_INP, N>& inps) {
            array<T_OUT, N> outs; int i = 0;

            for(const T_INP& inp : inps) {
                outs[i++] = step(inp);
            }

            return outs;
        }

        bool done(const T_STATE& state) const {
            return false;
        }

        T_STATE getInitialState() const { return _initialState; }
        void setState(T_STATE state) { _state = state; }

        typedef T_INP input_type;
        typedef T_STATE state_type;
        typedef T_OUT output_type;
    protected:
        const T_STATE _initialState;
        T_STATE _state;
    };
}

#endif //STATEMACHINE_STATEMACHINE_H
