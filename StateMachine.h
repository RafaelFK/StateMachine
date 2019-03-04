//
// Created by rafae on 05/09/2018.
//

#ifndef STATEMACHINE_STATEMACHINE_H
#define STATEMACHINE_STATEMACHINE_H



namespace sm {
    // Custom tuple used by getNextValues to return the next state and output
    // from a state transition
    template<typename T_STATE, typename T_OUT>
    class StateOutputTuple {
    public:
        StateOutputTuple(T_STATE state, T_OUT out): s{state}, o{out} {}
        T_STATE s;
        T_OUT o;
    };

    template<typename T_INP, typename T_STATE, typename T_OUT = T_STATE>
    class StateMachine {
    public:
        // TODO: Look up constexpr constructor
        StateMachine(T_STATE initialState) :
            _initialState{initialState}, _state{initialState} {}

        virtual StateOutputTuple<T_STATE, T_OUT>
        getNextValues(const T_STATE &state, const T_INP &inp) const = 0;

        T_OUT step(const T_INP &inp) {
            auto next = getNextValues(_state, inp);

            setState(next.s);

            return next.o;
        }

        /*template<size_t N>
        array<T_OUT, N> transduce(const array<T_INP, N>& inps) {
            array<T_OUT, N> outs; int i = 0;

            for(const T_INP& inp : inps) {
                outs[i++] = step(inp);
            }

            return outs;
        }*/

        bool done(const T_STATE& state) const {
            return false;
        }

        T_STATE getInitialState() const { return _initialState; }
        void setState(T_STATE state) { _state = state; }

        using input_type = T_INP;
        using state_type = T_STATE;
        using output_type = T_OUT;
    protected:
        const T_STATE _initialState;
        T_STATE _state;
    };
}

#endif //STATEMACHINE_STATEMACHINE_H
