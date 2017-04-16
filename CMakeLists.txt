cmake_minimum_required(VERSION 3.7)
project(Engine)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Channel.cpp Channel.h Logger.cpp Logger.h Message.cpp Message.h MessageBus.cpp MessageBus.h System.cpp System.h Console.cpp Console.h Systems.h Input.cpp Input.h)
add_executable(Engine ${SOURCE_FILES})