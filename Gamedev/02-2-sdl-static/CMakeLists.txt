cmake_minimum_required(VERSION 3.9)

project(02-1-sdl-static)
add_executable(${PROJECT_NAME} version.cpp)

find_library(SDL2-dynamic libSDL2d.a)
#target_link_libraries(SDL-dynamic libSDL2d.sa)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION &{CMAKE_CURRENT_LIST_DIR}/usr/local/bin
        LIBRARY DESTINATION &{CMAKE_CURRENT_LIST_DIR}/usr/local/bin
        ARCHIVE DESTINATION &{CMAKE_CURRENT_LIST_DIR}/usr/local/bin)