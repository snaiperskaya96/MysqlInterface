#https://github.com/MJPA/SimpleJSON
cmake_minimum_required(VERSION 3.0)
project(SimpleJSON)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES JSON.cpp JSON.h JSONValue.cpp JSONValue.h)
add_library(SimpleJSON ${SOURCE_FILES})