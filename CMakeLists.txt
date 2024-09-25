cmake_minimum_required(VERSION 3.27)
project(advanced_programming_group_ziggurat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include/myproject)

add_library(core_lib
        src/Filter.cpp
        src/Image.cpp
        src/Projection.cpp
        src/Volume.cpp
        src/Slice.cpp
)
target_include_directories(core_lib PUBLIC include/myproject)

file(GLOB SRC_FILES src/*.cpp)

add_executable(advanced_programming_group_ziggurat
        ${SRC_FILES}
        include/myproject/Image.h
        include/myproject/Slice.h
        include/myproject/Volume.h
        include/myproject/Filter.h
        include/myproject/Projection.h
)

add_subdirectory(tests)

target_link_libraries(advanced_programming_group_ziggurat PRIVATE core_lib)