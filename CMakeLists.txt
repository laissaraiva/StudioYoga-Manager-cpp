cmake_minimum_required(VERSION 4.0)

project(StudioYogaManager)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)


file(GLOB_RECURSE SOURCES "src/*.cpp")


add_executable(StudioManager
        main.cpp
        ${SOURCES}
)