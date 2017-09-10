cmake_minimum_required(VERSION 3.8)
project(Sequence)

set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES main.cpp Sequence.h ListSequence.h ArraySequence.h UnitTestForSequence.h)
add_executable(Sequence ${SOURCE_FILES})