cmake_minimum_required(VERSION 3.2)
add_library(nick
    lib.cpp
    )
set_target_properties(nick PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
target_link_libraries(nick)
