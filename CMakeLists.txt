cmake_minimum_required(VERSION 3.8)
project(heaps)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES binomial.h IHeap.h leftist.h heaplist.h skew.h fool.h unit_test.cpp)
add_executable(heaps ${SOURCE_FILES})
target_link_libraries(heaps /Users/edgarshmavonyan/Documents/ClionProjects/heaps/lib/googletest-master/googletest/include/gtest/ gtest_main)
#target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARY})