cmake_minimum_required(VERSION 3.5)
#project(Logger)

set(CMAKE_CXX_STANDARD 20)

# 添加自定义库搜索路径
link_directories(/usr/local/lib)
include_directories(/usr/local/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(LIB_PATH ${PROJECT_SOURCE_DIR}/lib)
set(HEAD_PATH ${PROJECT_SOURCE_DIR}/include)
set(EXEC_PATH ${PROJECT_SOURCE_DIR}/bin)

set(LOGGER_MANAGER_LIB logger_manager)
set(TEST test)

add_subdirectory(src)
add_subdirectory(test)

# 打包库文件
file(GLOB HEAD_FILES "${PROJECT_SOURCE_DIR}/include/*.h")
list(FILTER HEAD_FILES EXCLUDE REGEX "\\._.*$")
install(FILES
        ${HEAD_FILES}
        DESTINATION ${PROJECT_SOURCE_DIR}/package/logger/include
)
# 设置库文件安装路径
install(TARGETS ${LOGGER_MANAGER_LIB}
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/package/logger/lib
)