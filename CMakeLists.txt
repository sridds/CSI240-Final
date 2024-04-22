cmake_minimum_required(VERSION 3.27)
project(final)

set(CMAKE_CXX_STANDARD 17)

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
        userinfo.txt
        deli.txt
        dairy.txt
        produce.txt
        frozen.txt
)
