cmake_minimum_required(VERSION 3.3)
project(msh)
link_libraries(pthread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set(SOURCE_FILES
        main.c data/queue.h Reg.h data/group.h event.h inputhandler.h eventmanager.h executemanager.h util.h data/blockingqueue.h data/group.c data/queue.c Reg.c inputhandler.c eventmanager.c executemanager.c util.c data/blockingqueue.c )

add_executable(msh ${SOURCE_FILES} )