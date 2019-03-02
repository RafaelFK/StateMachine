#include <iostream>
#include "Elementary/Accumulator.h"
#include "operators/Cascade.h"
#include "operators/switch.h"
#include "Elementary/Delay.h"
#include "Negative.h"
#include "Positive.h"
#include "Elementary/Increment.h"
#include "Utils/optional.h"
#include <string>

using sm::operators::Cascade;
using sm::operators::make_cascade;
using sm::operators::make_switch;

using sm::elementary::Delay;
using sm::elementary::Accumulator;
using sm::elementary::Increment;

using nonstd::optional;
using nonstd::nullopt;

int main() {
    Accumulator<int> a {1};

    cout << a.step(2) << endl;
    cout << a.step(5) << endl;
    cout << a.step(9) << endl;

    Delay<int> d1 {1};
    Delay<int> d2 {10};

    auto c = make_cascade(d1, d2);

    cout << c.step(33) << endl;
    cout << c.step(44) << endl;
    cout << c.step(55) << endl;

    Positive p;
    Negative n;
    auto s = make_switch([](int inp) -> bool { return inp >= 0; }, p, n);

    s.step(1);
    s.step(3);
    s.step(-1);
    s.step(2);
    s.step(-10);

    std::cout << "Hello, World!" << std::endl;

    optional<std::string> o {"Hello"};

    if(o) std::cout << *o << std::endl;
    else std:: cout << "No value" << std::endl;

    o = nullopt;

    if(o) std::cout << *o << std::endl;
    else std::cout << "No value" << std:: endl;

    Increment<int> i {3};

    auto c2 = make_cascade(d1, i);

    std::array<int, 4> inps {3, 5, 7, 9};
    auto outs = c2.transduce(inps);

    return 0;
}