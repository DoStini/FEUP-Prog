cmake_minimum_required(VERSION 3.15)
project(Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project main.cpp gameMenu.cpp game.cpp game.h gameMenu.h main.h fileManager.cpp fileManager.h)