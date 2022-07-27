cmake_minimum_required(VERSION 3.20)
project(lua_clhash C)

set(CMAKE_C_STANDARD 11)
include_directories(F:/conda/Library/include ./dep/include)
link_directories("F:\\conda\\Library\\lib" F:/conda/Library/bin)


set(SOURCES ./dep/src/clhash.c)

add_library(clhash SHARED src/lclhash.c ${SOURCES})
target_link_libraries(clhash lua)

set_target_properties(clhash PROPERTIES OUTPUT_NAME clhash)
