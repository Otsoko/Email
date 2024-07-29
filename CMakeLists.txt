cmake_minimum_required(VERSION 3.20)

project(email
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -pedantic")

add_library(email
    STATIC
    lib/email.cc
)

add_executable(app
    app/app.cc
)

target_include_directories(app
    PUBLIC lib
)

target_link_libraries(app
    PRIVATE email
)
