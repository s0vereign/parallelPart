#################
# Required CMakeVersion
#################

cmake_minimum_required(VERSION 2.8.12)

#################
# Project
#################

project(parallelParts)

#################
# Build & Links
#################

file(GLOB_RECURSE SRC_FILES "*.c")

add_executable(parallelparts ${SRC_FILES})

target_link_libraries(parallelparts)
