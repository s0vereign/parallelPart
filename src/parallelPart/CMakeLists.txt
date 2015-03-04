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

if( OPENMP_FOUND OR
    ( CMAKE_CXX_COMPILER_ID AND OpenMP_CXX_FLAGS )
)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    #neccessary for MinGW (see http://stackoverflow.com/questions/23554716/using-openmp-on-windows-with-mingw-cannot-find-lpthread)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${OpenMP_SHARED_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

else()
    if(OMP_USE_OPENMP)
        message(WARNING "Your Compiler does NOT support OpenMP, so parallelism is not possible!")
    else()
        message(STATUS "Compile without OpenMP - either disabled, not supported or both.")
    endif()
endif()

##########
#Find OpenMPI
##########
find_package(MPI)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  ${MPI_COMPILE_FLAGS}")
include_directories(${MPI_INCLUDE_PATH})



#################
# Build & Links
#################

file(GLOB_RECURSE SRC_FILES "*.cpp")

add_executable(parallelparts ${SRC_FILES})

target_link_libraries(parallelparts ${MPI_LIBRARIES})

if(UNIX)
	target_link_libraries(parallelparts m)
endif()
