# ./src/core/CMakeLists.txt
 
cmake_minimum_required(VERSION 2.8)

# Defining the projet.
project(core)
 
# Creating the file list to be compiled.
file(GLOB core_source_file ./global/* ./hardware/*)

# Creation the Target.
enable_language(ASM_YASM)
add_library(SparkCore SHARED ${core_source_file})
