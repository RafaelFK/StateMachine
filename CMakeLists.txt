cmake_minimum_required(VERSION 3.10)
project(StateMachine)

set(CMAKE_CXX_STANDARD 17)

add_executable(StateMachine main.cpp StateMachine.h Elementary/Accumulator.h Elementary/Delay.h Operators/Cascade.h Operators/Switch.h Operators/Parallel.h Operators/Feedback.h Utils/optional.h Elementary/Increment.h Elementary/PureFunction.h Utils/Pair.h)