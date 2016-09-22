cmake_minimum_required(VERSION 3.5)
project(SecondTaskSender)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -lpthread -lprotobuf-c")

set(SOURCE_FILES main.c structures.h ReceiveMessage.c ReceiveMessage.h)

find_package(Threads)

add_executable(SecondTaskSender ${SOURCE_FILES})
target_link_libraries(SecondTaskSender ${CMAKE_THREAD_LIBS_INIT})