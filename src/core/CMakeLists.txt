# ./src/core/CMakeLists.txt
 
cmake_minimum_required(VERSION 2.8)
 
project(core)
 
file(GLOB core_source_file ./*)
 
add_library(SparkCore SHARED ${SparkCore_source_file})
