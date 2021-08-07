cmake_minimum_required(VERSION 3.16)

set(SOURCE_FILES
        LogFile.h LogFile.cpp
        LogBufferQueue.h LogBufferQueue.cpp
        AsyncLogger.h AsyncLogger.cpp
        StdLogger.h StdLogger.cpp
        LogLine.cpp TimeStamp.cpp SpinLock.h
        Log.cpp BaseLogger.h)

add_library(fmlog SHARED ${SOURCE_FILES})
target_link_libraries(fmlog pthread)

install(TARGETS fmlog LIBRARY DESTINATION lib)

add_subdirectory(tests)