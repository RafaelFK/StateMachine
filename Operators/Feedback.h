//
// Created by rafae on 04/11/2018.
//

#ifndef STATEMACHINE_FEEDBACK_H
#define STATEMACHINE_FEEDBACK_H

#include "../StateMachine.h"
#include <iostream>
#include <tuple>
#include <functional>
#include <type_traits>
#include "../Utils/optional.h"

using std::tuple;
using std::make_tuple;
using std::tie;
using std::cout;
using std::endl;
using std::function;
using std::is_same;

using sm::StateMachine;

using nonstd::optional;
using nonstd::nullopt;

namespace sm {
    namespace operators {
        template<class T_I, class T_S>
        class Feedback: public StateMachine<optional<T_I>, T_S, T_I> {
        public:
            using T_O = T_I;
            using T_SM = StateMachine<T_I, T_S, T_O>;

            Feedback(const T_SM &sm): StateMachine<T_I, T_S, T_O>(sm.getInitialState()), _sm{sm} {};


        private:
            T_SM const &_sm;
        };
    }
}

#endif //STATEMACHINE_FEEDBACK_H
