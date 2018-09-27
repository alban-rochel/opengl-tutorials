cmake_minimum_required (VERSION 2.6)

project (opengl)

include(FindPkgConfig)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW REQUIRED glfw3)

set(CMAKE_CXX_STANDARD 11)

#add_subdirectory(common)
#add_subdirectory(01_fenetre)
#add_subdirectory(02_triangle)
#add_subdirectory(03_matrices)
#add_subdirectory(04_cube)
#add_subdirectory(05_texture)
#add_subdirectory(06_keyboard)
#add_subdirectory(07_obj)
add_subdirectory(learn)
