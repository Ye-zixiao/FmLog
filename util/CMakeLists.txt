cmake_minimum_required(VERSION 3.16)

set(SOURCE_FILES
        AppendFile.h AppendFile.cpp
        LogFile.h LogFile.cpp
        LogBufferQueue.h LogBufferQueue.cpp
        AsyncLogger.h AsyncLogger.cpp
        StdLogger.h StdLogger.cpp
        LogLine.h LogLine.cpp
        TimeStamp.h TimeStamp.cpp
        SystemClock.h SpinLock.h Log.cpp BaseLogger.h)

add_library(fmutil SHARED ${SOURCE_FILES})
target_link_libraries(fmutil pthread)

add_subdirectory(test)