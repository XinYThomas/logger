cmake_minimum_required(VERSION 3.5)
project(TEST)

set(CMAKE_CXX_STANDARD 20)

# 添加自定义库搜索路径
include_directories(${HEAD_PATH})

link_directories(${LIB_PATH})
link_libraries(${LOGGER_MANAGER_LIB})
set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH})

add_executable(test_spdlog test_spd.cpp)

