cmake_minimum_required(VERSION 3.26)
project(final)

set(CMAKE_CXX_STANDARD 17)

file(GLOB FILES "*.txt")
file(COPY ${FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(final main.cpp
        exceptions.h
        exceptions.cpp
        food.cpp
        food.h
        mainfunctions.cpp
        mainfunctions.h
        store.cpp
        store.h
        user.cpp
        user.h
)
