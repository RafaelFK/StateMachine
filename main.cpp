#include <iostream>
#include "Elementary/Accumulator.h"
#include "operators/Cascade.h"
#include "operators/switch.h"
#include "Elementary/Delay.h"
#include "Elementary/PureFunction.h"
#include "Negative.h"
#include "Positive.h"
#include "Elementary/Increment.h"
#include "Utils/optional.h"
#include <string>

using std::cout;
using std::endl;

using sm::operators::Cascade;
using sm::operators::Switch;
using sm::operators::make_cascade;
using sm::operators::make_switch;

using sm::elementary::Delay;
using sm::elementary::Accumulator;
using sm::elementary::Increment;
using sm::elementary::PureFunction;

using nonstd::optional;
using nonstd::nullopt;

int main() {
    Delay<int> d1 {1};
    Delay<int> d2 {10};

    auto c = make_cascade(d1, d2);

    cout << c.step(33) << endl;
    cout << c.step(44) << endl;
    cout << c.step(55) << endl;

    Accumulator a {1};

    cout << a.step(2) << endl;
    cout << a.step(5) << endl;
    cout << a.step(9) << endl;

    PureFunction<int, int> positive {[](int) -> int{ return 1; }};
    PureFunction<int, int> negative {[](int) -> int{ return -1; }};

    // The plus sign  triggers a conversion from lambda expression to function pointer
    auto s = make_switch(+[](int inp) -> bool { return inp >= 0; }, positive, negative);

    cout << s.step(1) << endl;
    cout << s.step(3) << endl;
    cout << s.step(-1) << endl;
    cout << s.step(2) << endl;
    cout << s.step(-10) << endl;
    /*
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
*/
    return 0;
}