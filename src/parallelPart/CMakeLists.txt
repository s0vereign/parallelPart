#################
# Required CMakeVersion
#################

cmake_minimum_required(VERSION 2.8.12)

#################
# Project
#################

project(parallelParts)
set(CMAKE_CXX_FLAGS  "-std=c++11")
set(CMAKE_MODULE_PATH /src/parallelPart)



#################
# Find Boost
#################

find_package(Boost 1.49.0 REQUIRED COMPONENTS program_options REQUIRED)

if(Boost_FOUND)
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    set(LIBS ${LIBS} ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Could'nt find essential Boost-libraries. Sorry :(")
endif()

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


##############
#Find Adios Lib
##############
find_package(ADIOS 1.6.0)

	if(ADIOS_FOUND)
	    add_definitions(-DENABLE_ADIOS=1)
	    if(NOT (ADIOS_VERSION VERSION_LESS 1.7.0))
	        message(STATUS "Enable ADIOS data transforms")
	        add_definitions(-DADIOS_TRANSFORMS=1)
	    endif(NOT (ADIOS_VERSION VERSION_LESS 1.7.0))

	    include_directories(SYSTEM ${ADIOS_INCLUDE_DIRS})
	    set(LIBS ${LIBS} ${ADIOS_LIBRARIES})
	endif(ADIOS_FOUND)





#################
# Build & Links
#################

file(GLOB_RECURSE SRC_FILES "*.cpp")

message(${SRC_FILES})

add_executable(parallelparts ${SRC_FILES})

target_link_libraries(parallelparts ${OpenMP_CXX_FLAGS} ${MPI_LIBRARIES} )

if(UNIX)
	target_link_libraries(parallelparts m)
endif()
