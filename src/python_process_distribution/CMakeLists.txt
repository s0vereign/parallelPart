#################
# Required CMakeVersion
#################

cmake_minimum_required(VERSION 2.8.12)

#################
# Project
#################

project(process_distribution)

###############
# Files
###############
set(FILES)
file(GLOB FILES "(*.c | *.py)")
file(GLOB COMPILE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

#################
# Find Python
#################

find_package(PythonLibs)
find_package(PythonInterp)

#PYTHON_EXECUTABLE

################
#Find HDF5 components
###############

find_package(HDF5 COMPONENTS HL)
#include_directories(${HDF5_INCLUDE_DIRS})
#set(LIBS ${LIBS} ${HDF5_LIBRARIES})

##########
#Find OpenMP
#########
find_package(OpenMP)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

##########
# Configure building python-script:
#############

set(LINK_LIST)
foreach(I IN LISTS HDF5_HL_LIBRARY_NAMES_INIT OpenMP_CXX_FLAGS) 
	string(REGEX MATCH "^-" OUTPUT "${I}")
	if(OUTPUT) # leading "-" so no -l is nessecary
		set(LINK_LIST "${LINK_LIST},'${I}'")
	else()
		set(LINK_LIST "${LINK_LIST},'-l${I}'")
	endif()
endforeach()
string(REGEX REPLACE "^[ ]*," "" LINK_LIST "${LINK_LIST}")

set(COMPILE_LIST)
foreach(I IN LISTS OpenMP_CXX_FLAGS)
	set(COMPILE_LIST "${COMPILE_LIST}, '${I}'")
endforeach()
string(REGEX REPLACE "^[ ]*," "" COMPILE_LIST "${COMPILE_LIST}")

set(COMPILE_FILE_LIST)
foreach(I IN LISTS COMPILE_FILES)
	set(COMPILE_FILE_LIST "${COMPILE_FILE_LIST}, '${I}'")
endforeach()
string(REGEX REPLACE "^[ ]*," "" COMPILE_FILE_LIST "${COMPILE_FILE_LIST}")

configure_file("setup.py.cfg" "setup.py")

###########
# Build (via python skript)
###########

add_custom_target(process_distribution ALL 
	find . -name build -exec rm -r {} + #clean
	COMMAND ${PYTHON_EXECUTABLE} setup.py build DEPENDS ${FILES} #build
	COMMAND find ${CMAKE_CURRENT_BINARY_DIR} -name *.so -exec cp {} `dirname "${CMAKE_CURRENT_BINARY_DIR}"`   ""  "\;" #copy upwards
	)
