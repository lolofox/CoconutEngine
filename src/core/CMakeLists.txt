# ./src/core/CMakeLists.txt
 
cmake_minimum_required(VERSION 2.8)

# Defining the projet.
project(core)
 
# Creating the file list to be compiled.
file(GLOB core_source_file ./*)

# Creation the Target.
add_library(SparkCore SHARED ${SparkCore_source_file})
