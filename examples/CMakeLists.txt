cmake_minimum_required(VERSION 3.16)

add_executable(FmLog_bench FmLog_bench.cpp)
target_link_libraries(FmLog_bench fmutil)