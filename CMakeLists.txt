cmake_minimum_required(VERSION 3.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}/cmake")

project(Dodgee)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS  "-Wall -g")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR}
                    ${SDL2_MIXER_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)

file(GLOB_RECURSE DOGEESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(Dodgee ${DOGEESOURCE})

target_link_libraries(Dodgee ${SDL2_LIBRARY}
                             ${SDL2_IMAGE_LIBRARIES}
                             ${SDL2_TTF_LIBRARIES}
                             ${SDL2_MIXER_LIBRARIES})


# Copy assets folder into build folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)
