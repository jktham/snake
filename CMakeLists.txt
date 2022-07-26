cmake_minimum_required(VERSION 3.0.0)
project(snake)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE EXTERNAL_SOURCES external/src/*.cpp external/src/*.c)

add_executable(snake ${SOURCES} ${EXTERNAL_SOURCES})
target_include_directories(snake PRIVATE external/include)
target_link_directories(snake PRIVATE external/lib/GLFW)
target_link_libraries(snake PRIVATE libglfw3.a)
