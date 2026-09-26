cmake_minimum_required(VERSION 3.30.5)

project(CORBA)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(OMNIORB4_LIB NAMES omniORB4 REQUIRED)
find_library(OMNITHREAD_LIB NAMES omnithread REQUIRED)
find_library(OMNIDYNAMIC4_LIB NAMES omniDynamic4 REQUIRED)

set(HEADERS
    generated/Ecole.hh
    include/Etudiant_i.h)

set(SOURCES
    generated/EcoleSK.cc
    src/Etudiant_i.cpp
    main.cpp)

add_executable(exec ${SOURCES})

target_link_libraries(exec PRIVATE
${OMNIORB4_LIB}
${OMNITHREAD_LIB}
${OMNIDYNAMIC4_LIB})