cmake_minimum_required(VERSION 3.30.5)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(CPP-CLIENT)

find_library(OMNIORB4_LIB NAMES omniORB4)
find_library(OMNITHREAD_LIB NAMES omnithread)

set(HEADERS
    ./../generated/Ecole.hh)

set(SOURCES
    ./../generated/EcoleSK.cc
    main.cpp)

add_executable(client ${HEADES} ${SOURCES})

target_link_libraries(client ${OMNIORB4_LIB} ${OMNITHREAD_LIB} )
