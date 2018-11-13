cmake_minimum_required(VERSION 3.12)
project(Assigment_1_)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Assigment_1_
    include/Action.h
    include/Customer.h
    include/Dish.h
    include/Restaurant.h
    include/Table.h
    src/Action.cpp
    src/Customer.cpp
    src/Dish.cpp
    src/main.cpp
    src/Restaurant.cpp
    src/Table.cpp
    src/test.cpp)
