cmake_minimum_required(VERSION 3.6.0)
project(IpoF_vs VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(classes)
add_executable(main main.cpp)
target_link_libraries(main PUBLIC cls)