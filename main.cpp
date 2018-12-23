#include <iostream>
#include "Accumulator.h"
#include "operators/Cascade.h"
#include "operators/switch.h"
#include "Delay.h"
#include "Negative.h"
#include "Positive.h"
#include "Utils/optional.h"
#include <string>

using sm::operators::Cascade;
using sm::operators::make_cascade;

using sm::operators::make_switch;


using nonstd::optional;
using nonstd::nullopt;

int main() {
    Accumulator a {1};

    a.step(2);
    a.step(5);
    a.step(9);

    Delay d1 {1};
    Delay d2 {10};

    auto c = make_cascade(d1, d2);

    c.step(33);
    c.step(44);
    c.step(55);

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

    return 0;
}