cmake_minimum_required (VERSION 2.6)

project (opengl)

include(FindPkgConfig)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW REQUIRED glfw3)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(01_fenetre)
add_subdirectory(02_triangle)
