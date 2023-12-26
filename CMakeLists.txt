cmake_minimum_required (VERSION 3.5)

project (PlanetPoint)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14 -pthread")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*.cpp")

add_executable (PlanetPoint ${source_files})
target_include_directories(PlanetPoint PUBLIC /usr/include/SFML)
target_link_libraries(PlanetPoint sfml-system sfml-window sfml-graphics)
