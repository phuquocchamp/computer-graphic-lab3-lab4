cmake_minimum_required(VERSION 3.10)

# Set the CMP0072 policy
cmake_policy(SET CMP0072 NEW)

# Project name
project(lab3-lab4)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
add_executable(app src/main.cpp)

# Link OpenGL and GLUT libraries
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries(app OpenGL::GL GLUT::GLUT GLU)
