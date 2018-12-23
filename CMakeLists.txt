cmake_minimum_required(VERSION 3.10)
project(StateMachine)

set(CMAKE_CXX_STANDARD 14)

add_executable(StateMachine main.cpp StateMachine.h Accumulator.h Delay.h Operators/Cascade.h Operators/Switch.h Positive.h Negative.h Operators/Parallel.h Operators/Feedback.h Utils/optional.h)