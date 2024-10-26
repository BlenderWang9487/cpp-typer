cmake_minimum_required(VERSION 3.16)
project(Cpp_Typer LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)


add_library(cpp_typer INTERFACE)

# library
add_library(reflectcpp SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/reflect-cpp-0.14.1/src/reflectcpp.cpp
)
target_include_directories(reflectcpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/reflect-cpp-0.14.1/include)

target_include_directories(cpp_typer
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(cpp_typer INTERFACE reflectcpp)
target_include_directories(cpp_typer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libs)

# example binary
add_executable(example example.cpp)

target_link_libraries(example PRIVATE cpp_typer)

set_target_properties(example
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/bin"
)
