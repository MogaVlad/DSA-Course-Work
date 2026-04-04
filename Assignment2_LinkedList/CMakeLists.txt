cmake_minimum_required(VERSION 4.1)
project(Assignment2_LinkedList)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment2_LinkedList
        src/App.cpp
        src/PriorityQueue.cpp
        src/ShortTest.cpp
        src/ExtendedTest.cpp
        include/PriorityQueue.h
        include/ShortTest.h
        include/ExtendedTest.h)
