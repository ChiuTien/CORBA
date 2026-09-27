cmake_minimum_required(VERSION 3.30.5)

project(CPP-SERVEUR)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(OMNIORB4_LIB NAMES omniORB4 REQUIRED)
find_library(OMNITHREAD_LIB NAMES omnithread REQUIRED)
find_library(OMNIDYNAMIC4_LIB NAMES omniDynamic4 REQUIRED)
find_library(MYSQL_CPPCONN_LIB NAMES mysqlcppconn mysqlcppconn8 REQUIRED)

set(HEADERS
    ../generated/Ecole.hh
    include/EtudiantDao.h
    include/DatabaserManager.h)

set(SOURCES
    ../generated/EcoleSK.cc
    src/EtudiantDao.cpp
    src/DatabaseManager.cpp
    main.cpp)

add_executable(exec ${SOURCES})

target_link_libraries(exec PRIVATE
${OMNIORB4_LIB}
${OMNITHREAD_LIB}
${OMNIDYNAMIC4_LIB}
${MYSQL_CPPCONN_LIB})