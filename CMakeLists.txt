cmake_minimum_required(VERSION 3.1)

project(Dodgee)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS  "-Wall -g")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)

file(GLOB_RECURSE DOGEESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(Dodgee ${DOGEESOURCE})

target_link_libraries(Dodgee SDL2 SDL2_image SDL2_ttf SDL2_mixer)

# Copy assets folder into build folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)
