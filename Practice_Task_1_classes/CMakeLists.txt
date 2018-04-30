cmake_minimum_required(VERSION 3.8)
project(Practice_Task_1_classes)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Counter.cpp Counter.h CycleList.h CounterManager.cpp CounterManager.h)
add_executable(Practice_Task_1_classes ${SOURCE_FILES})