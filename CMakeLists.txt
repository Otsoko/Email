cmake_minimum_required(VERSION 3.10)
project(libemail)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_FILES
        src/email.cpp)

add_library(${PROJECT_NAME} SHARED ${PROJECT_FILES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
