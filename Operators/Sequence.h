//
// Created by rafae on 06/03/2019.
//

#ifndef STATEMACHINE_SEQUENCE_H
#define STATEMACHINE_SEQUENCE_H

#include "../StateMachine.h"

using sm::StateMachine;
using sm::StateOutputTuple;

namespace sm {
    namespace operators {


        template<typename T_I, typename T_S1, typename T_S2, typename T_O>
        class Sequence: public StateMachine<> {

        };
    }
}

#endif //STATEMACHINE_SEQUENCE_H
