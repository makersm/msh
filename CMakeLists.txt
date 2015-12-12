cmake_minimum_required(VERSION 3.3)
project(msh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.c data/queue.h Reg.h data/group.h data/group.c data/queue.c Reg.c event.h inputmanager.h inputmanager.c eventmanager.c eventmanager.h executemanager.c executemanager.h util.c util.h data/blockingqueue.c data/blockingqueue.h)

add_executable(msh ${SOURCE_FILES})