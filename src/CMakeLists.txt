cmake_minimum_required(VERSION 3.5)
project(LOGGER_MANAGER_LIB)

include_directories(${HEAD_PATH})
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})

file(GLOB SOURCE_FILES "${PROJECT_SOURCE_DIR}/*.cpp")

list(FILTER SOURCE_FILES EXCLUDE REGEX "\\._.*$")

add_library(${LOGGER_MANAGER_LIB} SHARED ${SOURCE_FILES})