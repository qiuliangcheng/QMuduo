cmake_minimum_required(VERSION 2.5)
project(muduo)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -fPIC -ggdb -std=c++14 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -fPIC")
include_directories(./include)
include_directories(/usr/local/include)
# 参与编译的源文件
aux_source_directory(./src LIB_SRC)
add_library(qlc SHARED ${LIB_SRC})
find_library(YAMLCPP yaml-cpp)
find_library(PTHREAD pthread)
set(LIB_QLC 
    qlc
    dl 
    ${YAMLCPP} 
    ${PTHREAD}
)
# add_executable(iptest test/iptest.cpp)
# target_link_libraries(iptest qlc ${LIB_QLC})

# add_executable(Timestamp_test test/Timestamp_test.cpp)
# target_link_libraries(Timestamp_test qlc ${LIB_QLC})

add_executable(muduo_test test/muduo_test.cpp)
target_link_libraries(muduo_test qlc ${LIB_QLC})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

