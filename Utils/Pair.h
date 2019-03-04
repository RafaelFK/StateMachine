//
// Created by rafae on 03/03/2019.
//

#ifndef STATEMACHINE_PAIR_H
#define STATEMACHINE_PAIR_H

namespace util {
    template<typename T_1, typename T_2>
    class Pair {
    public:
        Pair(T_1 a, T_2 b): a{a}, b{b} {}

    private:
        T_1 a;
        T_2 b;
    };
}
#endif //STATEMACHINE_PAIR_H
