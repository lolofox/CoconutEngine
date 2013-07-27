# ./CMakeLists.txt
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/buildengine/cmake")

if(NOT CMAKE_BUILD_TYPE)
	# default to release build.
	set(CMAKE_BUILD_TYPE Release CACHE STRING
		"Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel."
		FORCE)
endif()

if(NOT COCONUT_SHARED_BUILD)
	set(COCONUT_SHARED_BUILD ON CACHE BOOL
		"Choose the build type : shared / static"
		FORCE)
endif()

if(NOT COCONUT_NO_STL)
	set(COCONUT_NO_STL ON CACHE BOOL
		"Choose if we want to use STL containers"
		FORCE)
endif()
		
# If we're compiling under a 64-bits environment, we used to tell it to the compilers.
if("${CMAKE_SIZEOF_VOID_P}" MATCHES 8)
	set(X86_64 1)
	add_definitions(-DX86_64=1)
endif()

if("${COCONUT_NO_STL}" MATCHES ON)
	add_definitions(-DCOCONUT_NO_STL)
endif()

# We need yasm compiler to compile the assembly part of the engine.
find_package(Yasm)
if(YASM_FOUND)
	if(YASM_VERSION_STRING VERSION_LESS "1.2.0")
		message(STATUS "Yasm version ${YASM_VERSION_STRING} is too old. 1.2.0 or later required.")
	else()
		message(STATUS "Found Yasm ${YASM_VERSION_STRING} to build assembly.")
	endif()
endif(YASM_FOUND)

# Setting output directories.
set(EXECUTABLE_OUTPUT_DIRECTORY ../../bin/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_DIRECTORY ../../bin/${CMAKE_BUILD_TYPE})

# Settings C++ compiler flags.
set(CMAKE_CXX_FLAGS "-std=c++0x -march=core2 -mfpmath=sse -Wall -Wextra -pedantic -Wconversion -Wdouble-promotion -Wold-style-cast -Weffc++")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Os -s")
set(CMAKE_CXX-FLAGS_DEBUG "-g2")

if("${COCONUT_SHARED_BUILD}" MATCHES ON)
	add_definitions(-DCOCONUT_SHARED)
endif()

add_subdirectory(src/core)
