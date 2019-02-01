cmake_minimum_required (VERSION 3.13.2)
project (Hello)
set(CMAKE_BUILD_TYPE Release)
include_directories(include)
file(GLOB SOURCES "src/hello.cpp")
add_library(Hello STATIC ${SOURCES})
install(TARGETS Hello DESTINATION /usr/lib)

