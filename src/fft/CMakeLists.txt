#################
# Required CMakeVersion
#################

cmake_minimum_required(VERSION 2.8.12)

#################
# Project
#################

project(fft)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/)

set(LIBS "")

#################
# Find FFTW
#################

find_package(FFTW)

if(FFTW_FOUND)

    include_directories(${FFTW_INCLUDES})
    set(LIBS "${FFTW_LIBRARIES}${LIBS}")

endif()




################
#Find HDF5 components
###############

find_package(HDF5 COMPONENTS HL)
include_directories(${HDF5_INCLUDE_DIRS})
set(LIBS ${LIBS} ${HDF5_LIBRARIES})


#################
# Build & Links
#################

file(GLOB_RECURSE SRC_FILES "*.c")

add_executable(fft ${SRC_FILES})

target_link_libraries(fft ${LIBS})

if(UNIX)
	target_link_libraries(fft m)
endif()
