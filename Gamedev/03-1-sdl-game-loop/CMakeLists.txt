cmake_minimum_required(VERSION 3.9)

project(03-1-sdl-loop)
find_package(SDL2)
add_executable(${PROJECT_NAME} game-loop.cpp)
find_library(${SDL2} libSDL2d.so)

target_link_libraries(${PROJECT_NAME} libSDL2d.so)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION &{CMAKE_CURRENT_LIST_DIR}/usr/local/bin
        LIBRARY DESTINATION &{CMAKE_CURRENT_LIST_DIR}/usr/local/bin
        ARCHIVE DESTINATION &{CMAKE_CURRENT_LIST_DIR}/usr/local/bin)
