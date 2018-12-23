//
// Created by rafae on 05/09/2018.
//

#ifndef STATEMACHINE_STATEMACHINE_H
#define STATEMACHINE_STATEMACHINE_H

#include <tuple>

using std::tuple;
using std::make_tuple;
using std::tie;

namespace sm {
    template<class T_INP, class T_STATE, class T_OUT = T_STATE>
    class StateMachine {
    public:
        StateMachine(T_STATE initialState) : _state{initialState} {}

        virtual tuple<T_STATE, T_OUT>
        getNextValues(const T_STATE &state, const T_INP &inp) const = 0;

        virtual void step(const T_INP &inp) = 0;

        T_STATE getState() const { return _state; }
        void setState(T_STATE state) { _state = state; }

        typedef T_INP input_type;
        typedef T_STATE state_type;
        typedef T_OUT output_type;
    protected:
        T_STATE _state;
    };
}

#endif //STATEMACHINE_STATEMACHINE_H
