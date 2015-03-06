#################
# Required CMakeVersion
#################

cmake_minimum_required(VERSION 2.8.12)

#################
# Project
#################

project(parallelParts)
set(CMAKE_CXX_FLAGS "-std=c++11")


##########
#Find OpenMP
#########
find_package(OpenMP)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")


#################
# Build & Links
#################

file(GLOB_RECURSE SRC_FILES "*.cpp")

add_executable(parallelparts ${SRC_FILES})

target_link_libraries(parallelparts)

if(UNIX)
	target_link_libraries(parallelparts m)
endif()
