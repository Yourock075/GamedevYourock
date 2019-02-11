cmake_minimum_required(VERSION 3.9)

project(03-1-sdl-engine)

#find library(eng libEngine.so)
#message (${eng})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} libEngine.so)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION &{CMAKE_CURRENT_LIST_DIR}/usr/local/bin
        LIBRARY DESTINATION &{CMAKE_CURRENT_LIST_DIR}/usr/local/lib
        ARCHIVE DESTINATION &{CMAKE_CURRENT_LIST_DIR}/usr/local/lib)
