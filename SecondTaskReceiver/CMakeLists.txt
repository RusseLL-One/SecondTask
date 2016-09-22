cmake_minimum_required(VERSION 3.5)
project(SecondTaskReceiver)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -lpthread")

set(SOURCE_FILES main.c queue.c queue.h ReceiveMessage.c ReceiveMessage.h socketStruct.h queueStruct.h MessageReverse.c MessageReverse.h MessageUpper.c MessageUpper.h MessageAddSpaces.c MessageAddSpaces.h MessageAddDashes.c MessageAddDashes.h SendMessage.c SendMessage.h)
find_package(Threads)
add_executable(SecondTaskReceiver ${SOURCE_FILES})
target_link_libraries(SecondTaskReceiver ${CMAKE_THREAD_LIBS_INIT})