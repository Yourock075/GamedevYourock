cmake_minimum_required (VERSION 3.9)

project (Engine)

include_directories(include)


add_library(${PROJECT_NAME} SHARED game-engine.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/game-engine.h")

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME} libSDL2d.so)


install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION DESTINATION lib
	PUBLIC_HEADER DESTINATION include)

