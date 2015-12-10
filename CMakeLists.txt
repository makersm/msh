cmake_minimum_required(VERSION 3.3)
project(shell)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.c queue.h Reg.h group.h group.c queue.c Reg.c event.h inputmanager.h inputmanager.c eventmanager.c eventmanager.h executemanager.c executemanager.h)

add_executable(shell ${SOURCE_FILES})